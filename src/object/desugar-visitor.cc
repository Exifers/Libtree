/**
 ** \file object/desugar-visitor.cc
 ** \brief Implementation of object::DesugarVisitor.
 */

#include <sstream>

#include <ast/all.hh>
#include <misc/set.hh>
#include <misc/symbol.hh>
#include <object/desugar-visitor.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>
#include <type/class.hh>
#include <type/function.hh>
#include <type/record.hh>

namespace object
{

  DesugarVisitor::DesugarVisitor(const class_names_type& names)
    : class_names_(names)
  {}

  /*---------------------------.
  | Handling names and types.  |
  `---------------------------*/

  namespace
  {

    // Desugar prefixes.

    // Prefix of every class id (label).
    const char* class_id_prefix = "_id_";
    // Prefix of every record holding the contents of a desugared class.
    const char* class_contents_prefix = "_contents_";
    // Prefix of every variant storing the possible dynamic type for
    // a given static type.
    const char* class_variant_prefix = "_variant_";
    // Prefix of the fields in the variant.
    const char* variant_field_prefix = "field_";
    // Prefix of constructors.
    const char* class_ctor_prefix = "_new_";
    // Prefix of methods.
    const char* method_prefix = "_method_";


    // Useful routines.

    // Try to get the class type of \a t.  If \a t is not a class
    // type, return a null pointer.
    const type::Class*
    class_type_query(const ast::Typable& t)
    {
  // FIXME: Some code was deleted here.
    }

    // Like class_type_query, but ensure the type is actually a class.
    const type::Class*
    class_type_get(const ast::Typable& t)
    {
      const type::Class* class_type = class_type_query(t);
      postcondition(class_type);
      return class_type;
    }

  }


  /*------------------.
  | Code generation.  |
  `------------------*/

  std::string
  DesugarVisitor::type_symbol(const type::Type* type)
  {
  // FIXME: Some code was deleted here (Check int, then string, then class name).
  }

  std::string
  DesugarVisitor::upcast_fun_name(const type::Class* from,
                                  const type::Class* to)
  {
    std::stringstream s;
    s << "_upcast_" << class_names_(from) << "_to_" << class_names_(to);
    return s.str();
  }

  std::string
  DesugarVisitor::downcast_fun_name(const type::Class* from,
                                    const type::Class* to)
  {
    std::stringstream s;
    s << "_downcast_" << class_names_(from) << "_to_" << class_names_(to);
    return s.str();
  }

  std::string
  DesugarVisitor::dispatch_fun_name(const type::Class* owner,
                                    const type::Method* method)
  {
    std::stringstream s;
    // If an extension is found, add it to the dispatch suffix.
    if (dispatch_map_.find(method) != dispatch_map_.end())
      s << "_dispatch_" << dispatch_map_[method] << "_"
        << class_names_(owner) << "_" << method->name_get();
    else
      s << "_dispatch_"  << class_names_(owner) << "_" << method->name_get();

    return s.str();
  }


  void
  DesugarVisitor::adapt_type(ast::Exp*& source_exp,
                             const type::Class* source_type,
                             const type::Class* target_type)
  {
    // If the source type is different from the target type, (up)cast
    // the source expression to the latter.
    if (source_type && target_type && source_type != target_type)
      source_exp = parse::parse(parse::Tweast()
                                << upcast_fun_name(source_type, target_type)
                                << " (" << source_exp << ")");
  }

  ast::Exp*
  DesugarVisitor::variant_exp(const type::Class* static_type,
                              const std::string& exact_type,
                              const field_inits_type& inits)
  {
    parse::Tweast input;
    misc::symbol static_type_name = class_names_(static_type);
    input <<
          " " << class_variant_prefix << static_type_name <<
          " {"
          "   exact_type = " << exact_type;
    /* For each field of the variant, store the corresponding
       initialization value if one was given, otherwise set the field
       to `nil'.  */
    // Fields of the static type.
    for (const type::Class* c = static_type; c; c = c->super_get())
      // Don't generate slots for classes with no data.
      if (c->has_data())
        {
          input << ",\n"
                << variant_field_prefix << class_names_(c) << " = ";
          // These fields must have a value (we don't need to put an
          // assertion here, misc::map::operator() already handles this.
          std::string init = inits.operator()(c);
          input << init;
        }
    // Potential fields of the dynamic type (from subclasses of the
    // static type).
    for (const type::Class* subclass : static_type->subclasses_get())
      // Don't generate slots for classes with no data.
      if (subclass->has_data())
        {
          input << ",\n"
                << variant_field_prefix << class_names_(subclass) << " = ";
          // These fields might be nil.
          field_inits_type::const_iterator i = inits.find(subclass);
          if (i != inits.end())
            input << i->second;
          else
            input << "nil";
        }
    input << " }\n";
    return parse::parse(input);
  }

  // Syntactic sugar.
  ast::Exp*
  DesugarVisitor::variant_exp(const type::Class* static_type,
                              const type::Class* dynamic_type,
                              const field_inits_type& inits)
  {
    std::string exact_type =
      class_id_prefix + class_names_(dynamic_type).get();
    return variant_exp(static_type, exact_type, inits);
  }

  void
  DesugarVisitor::fill_variant_fields(const type::Class* class_type,
                                      parse::Tweast* input)
  {
    // Don't generate slots for classes with no data.
    if (class_type->has_data())
      {
        misc::symbol class_name = class_names_(class_type);
        *input << ",\n"
               << "   " << variant_field_prefix << class_name << " : "
               << "   " << class_contents_prefix << class_name;
      }
  }

  // Desugar a class type as a variant (record) type.
  parse::Tweast*
  DesugarVisitor::variant_ty(const type::Class* class_type)
  {
    auto input = new parse::Tweast;
    *input << " {"
           << "   exact_type : int";
    // Actual data slots.
    /* First, populate the variant with mandatory fields (always non
       nil) starting with the type of the visited class, then super
       classes.  */
    for (const type::Class* c = class_type; c; c = c->super_get())
      fill_variant_fields(c, input);
    /* Then add all subclasses types.  These might be nil, according to
       the exact type of the object.  */
    for (const type::Class* subclass : class_type->subclasses_get())
      fill_variant_fields(subclass, input);
    *input << " }\n";
    return input;
  }

  void
  DesugarVisitor::fill_init_list(const type::Class* class_type,
                                 field_inits_type& inits)
  {
    // Populate the initialization list with classes
    // owning actual data only.
    if (class_type->has_data())
      {
        std::string field_name = class_names_(class_type);
        misc::put(inits, class_type,
                  std::string("source.")
                  + variant_field_prefix + field_name);
      }
  }

  parse::Tweast*
  DesugarVisitor::cast_function(const std::string& name,
                                const type::Class* source,
                                const type::Class* target,
                                const type::Class* exact_type)
  {
    auto input = new parse::Tweast;
    *input <<
           " function " << name <<
           "   (source : " << class_variant_prefix
           << class_names_(source) << ") :"
           "   " << class_variant_prefix << class_names_(target) << " = ";

    // Copy all fields from the source.
    field_inits_type inits;
    // First, fields from the class and its super classes...
    for (const type::Class* c = source; c; c = c->super_get())
      fill_init_list(c, inits);
    // ...then, fields from the subclasses.
    for (const type::Class* c : source->subclasses_get())
      fill_init_list(c, inits);
    *input << variant_exp(target, exact_type, inits) << "\n";
    return input;
  }

  parse::Tweast*
  DesugarVisitor::upcast_function(const type::Class* source,
                                  const type::Class* target)
  {
    return cast_function(upcast_fun_name(source, target),
                         source, target, source);
  }

  parse::Tweast*
  DesugarVisitor::downcast_function(const type::Class* source,
                                    const type::Class* target)
  {
    return cast_function(downcast_fun_name(source, target),
                         source, target, target);
  }

  ast::Exp*
  DesugarVisitor::dispatch_switch(const type::Class* class_type,
                                  const type::Method* method,
                                  const ast::TypeDecs* decs,
                                  const type::Method* dispatch_method)
  {
    parse::Tweast input;
    misc::symbol method_name = method->name_get();
    // If a recursive call is needed, dispatch_method will not be
    // nullptr. It means that during the dispatch function
    // declaration, formals of the mother method have been used
    // (because of the use of dispatch_map_, we cannot use child's
    // formals.
    const ast::MethodDec* def;
  // FIXME: Some code was deleted here (Initialize def).
    const ast::VarDecs::Ds& formals = def->formals_get().decs_get();

    // Create a case for each method redefinition.
    classes_type overridings;
    for (const type::Class* c : class_type->subclasses_get())
      if (std::any_of(begin(decs->decs_get()), end(decs->decs_get()),
                      [c](const ast::TypeDec* tmp)
                      { return class_type_query(*tmp) == c; }))
        overridings.emplace_back(c);

    if (overridings.empty())
      // No dispatch is needed; simply call the method.
      input << method_call(class_names_(class_type), method_name,
                           "self", formals);
    else
      {
        // Emit code for self.
        bool first = true;
        // Emit code for other types.
        for (auto c : overridings)
          {
            if (!first)
              input << " else ";
            input << " if self.exact_type = "
                  << class_id_prefix << class_names_(c) << " then ";
            // We search for the nearest implementation of our method.
            const type::Class* nearest_c = c;
            while (nearest_c && !(nearest_c->owned_meth_find(method_name)))
              nearest_c = nearest_c->super_get();
            input << method_call(class_names_(nearest_c), method_name,
                                 ((*class_type != *nearest_c)
                                  ? downcast_fun_name(class_type, nearest_c)
                                    + " (self)"
                                  : "self"),
                                 formals);
            first = false;
          }
        input << " else ";
        // If this is a sub dispatch function, call the last dispatch
        // method built so we don't need to write every single test
        // for exact_type.
        if (dispatch_method)
          {
            input << "_dispatch_";
            if ((dispatch_map_[method] - 1) != 1)
              input << (dispatch_map_[method] - 1) << "_";
            input << class_names_(class_type) << "_" << method->name_get()
                  << " (self";
            // Get the other arguments.
            for (const ast::VarDec* arg : formals)
              input << ", " << arg->name_get();
            input << ")";
          }
        else
          input << method_call(class_names_(class_type), method_name,
                               "self", formals);
      }
    input << '\n';
    return parse::parse(input);
  }

  parse::Tweast*
  DesugarVisitor::method_call(const misc::symbol& class_name,
                              const misc::symbol& method_name,
                              const std::string& target,
                              const ast::VarDecs::Ds& formals)
  {
    auto input = new parse::Tweast;
    *input << method_prefix << class_name << "_" << method_name << " (";
    // Pass the target.
  // FIXME: Some code was deleted here.
    // Pass other arguments.
  // FIXME: Some code was deleted here.
    *input << ")";
    return input;
  }

  /*------------------------.
  | Visiting declarations.  |
  `------------------------*/

  void
  DesugarVisitor::operator()(const ast::DecsList& e)
  {
    const ast::Location& location = e.location_get();
    // This is an inlined and specialized version of
    // astclone::Cloner::recurse_collection.  Maybe we could factor
    // it, but it's not easy to see whether we could benefit from
    // this.  (Maybe a variant would be appropriate.)
    ast::DecsList::decs_type contents;
    for (const ast::Decs* d : e.decs_get())
      {
        d->accept(*this);
        // The result can be either an ast::Decs* or an ast::DecsList*.
        auto decs = dynamic_cast<ast::Decs*>(result_);
        if (decs)
          contents.emplace_back(decs);
        else
          {
            auto decslist = dynamic_cast<ast::DecsList*>(result_);
            if (decslist)
              {
                contents.splice(contents.end(), decslist->decs_get());
                delete decslist;
              }
            else
              abort();
          }
      }
    result_ = new ast::DecsList(location, contents);
  }

  /*-----------------------------.
  | Desugar class declarations.  |
  `-----------------------------*/

  void
  DesugarVisitor::desugar_constructor(parse::Tweast& functions,
                                      const type::Class* cls,
                                      const misc::symbol& class_name)
  {
    functions <<
      " function " << class_ctor_prefix << class_name << "() : "
      " " << class_variant_prefix << class_name << " = "
      " let";
    // Initialize each mandatory field of the variant (i.e.,
    // the fields holding the attributes of the classes and
    // its super classes).
    for (const type::Class* c = cls; c; c = c->super_get())
      if (c->has_data())
        {
          functions
            << " var contents_" << class_names_(c) << " := "
            << " " << class_contents_prefix << class_names_(c)
            << " { ";

          for (auto a = c->attrs_get().begin();
               a != c->attrs_get().end(); a++)
            {
              if (a != c->attrs_get().begin())
                functions << ", ";
              const ast::VarDec* attr;
  // FIXME: Some code was deleted here (Initialize attr).
              misc::symbol attr_name = attr->name_get();
              // Partially clone the contents of the VarDec
              // (cloning the whole VarDec would leak memory).

              ast::Exp* attr_init = recurse(attr->init_get());
              // Cast the initialization value if needed.
              if (attr->init_get() && attr->type_name_get())
                adapt_type(attr_init,
                           class_type_query(*attr->init_get()),
                           class_type_query(*attr->type_name_get()));
              functions << attr_name << " = " << attr_init;
            }
          functions << " } ";
        }
    functions << " in ";
    // Create a list of initializations for each field of the
    // variant being constructed.
    field_inits_type inits;
    for (const type::Class* c = cls; c; c = c->super_get())
      if (c->has_data())
        {
  // FIXME: Some code was deleted here.
        }
    // Create the contents of the variant.
    functions << variant_exp(cls, cls, inits)
              << " end\n";
  }

  void
  DesugarVisitor::desugar_method(parse::Tweast& functions,
                                  const type::Method* method,
                                  const misc::symbol& class_name)
  {
    functions << " function " << method_prefix
              << class_name << "_" << method->name_get()
              << " (self : " << class_variant_prefix << class_name;
    // Get the other arguments.
    const ast::MethodDec* def;
  // FIXME: Some code was deleted here (Initiliaze def).
    for (const ast::VarDec* arg : def->formals_get().decs_get())
      functions << ", "
                << arg->name_get() << " : "
                << recurse(*arg->type_name_get());
    functions << ")";
    if (def->result_get())
      functions << " : " << recurse(def->result_get());
    ast::Exp* body = recurse(def->body_get());
    // Cast the return value of the function if needed.
    if (def->result_get())
      adapt_type(body,
                 class_type_query(*def->body_get()),
                 class_type_query(*def->result_get()));
    functions << " = " << body << "\n";
  }

  void
  DesugarVisitor::dispatch_function(parse::Tweast& functions,
                                    const ast::TypeDecs& e,
                                    const type::Class* cls,
                                    const type::Method* method,
                                    const misc::symbol& class_name,
                                    dispatch_list_type& sub_dispatches)
  {
    for (const type::Class* c = cls->super_get(); c; c = c->super_get())
      {
        // If this class is not defined in the current chunk, then
        // the subdispatch method is not needed yet (since it can
        // only be called after the declaration of the said class.
        if (std::any_of(e.decs_get().begin(), e.decs_get().end(),
                        [c](const ast::TypeDec* t) {
                          return class_type_query(*t) == c;
                        }))
          continue;

        // Determine if the class c implements our method. If not,
        // we do not need to write a sub dispatch method for it.
        auto meth_it
          = std::find_if(c->meths_get().begin(), c->meths_get().end(),
                         [method](const type::Method* meth) {
                           return meth->name_get() == method->name_get();
                         });

        if (meth_it == c->meths_get().end())
          continue;

        // Since we're looping inside a chunk, we do not rebuild an
        // already built sub dispatch method.
        auto disp_it = sub_dispatches.emplace(c, *meth_it);

        if (!disp_it.second)
          continue;

        // Increments the dispatch counter.
        if (dispatch_map_.find(*meth_it) == dispatch_map_.end())
          dispatch_map_[*meth_it] = 2;
        else
          dispatch_map_[*meth_it] = dispatch_map_[*meth_it] + 1;

        // We build the subdispatch method.
        functions << " function " << dispatch_fun_name(c, *meth_it)
                  << " (self : " << class_variant_prefix << class_names_(c);
        // Get the other arguments.
        const ast::MethodDec* def;
  // FIXME: Some code was deleted here (Initialize def).
        for (const ast::VarDec* arg : def->formals_get().decs_get())
          functions << ", "
                    << arg->name_get() << " : "
                    << recurse(*arg->type_name_get());
        functions << ")";
        if (def->result_get())
          functions << " : " << recurse(def->result_get());
        functions << " = " << dispatch_switch(c, *meth_it, &e, method);
      }

    functions << " function " << dispatch_fun_name(cls, method)
              << " (self : " << class_variant_prefix << class_name;
    // Get the other arguments.
    const ast::MethodDec* def;
  // FIXME: Some code was deleted here (Initialize def).
    for (const ast::VarDec* arg : def->formals_get().decs_get())
      functions << ", "
                << arg->name_get() << " : "
                << recurse(*arg->type_name_get());
    functions << ")";
    if (def->result_get() != nullptr)
      functions << " : " << recurse(def->result_get());
    functions << " = " << dispatch_switch(cls, method, &e);
  }

  void
  DesugarVisitor::handle_class(const ast::TypeDecs& e,
                               const type::Class* cls,
                               parse::Tweast& functions,
                               dispatch_list_type& sub_dispatches)
  {
    misc::symbol class_name = class_names_(cls);

    /*---------------------------.
    | Introduce a new class id.  |
    `---------------------------*/

    class_ids_ << " var " << class_id_prefix << class_name
               << " := " << cls->id_get() << "\n";

    /*----------------------------------------------------.
    | Create a record holding the actual class contents.  |
    `----------------------------------------------------*/

    if (cls->has_data())
      {
        types_
          << " type " << class_contents_prefix << class_name << " ="
          << " { ";
  // FIXME: Some code was deleted here (Populate the record with attributes (names and types)).
        types_ << " }\n";
      }

    /*--------------------------------------------------------------.
    | Create a variant able to store any dynamic type corresponding |
    | to this (static) class type.                                  |
    `--------------------------------------------------------------*/

    types_
      << " type " << class_variant_prefix << class_name << " ="
      << variant_ty(cls);

    /*-----------------------.
    | Create a constructor.  |
    `-----------------------*/

    desugar_constructor(functions, cls, class_name);

    /*-------------------------------------------------------------.
    | Create conversion routines from the class type to any of its |
    | super types.                                                 |
    `-------------------------------------------------------------*/

    for (const type::Class* super_type = cls->super_get();
         super_type; super_type = super_type->super_get())
      functions << upcast_function(cls, super_type);

    /*-------------------------------------------------------------.
    | Create conversion routines from the class type to any of its |
    | subtypes.                                                    |
    `-------------------------------------------------------------*/

    for (const type::Class* subclass : cls->subclasses_get())
      functions << downcast_function(cls, subclass);

    for (const type::Method* m : cls->meths_get())
      {
        desugar_method(functions, m, class_name);
        dispatch_function(functions, e, cls, m, class_name, sub_dispatches);
      }
  }

  /* All type-related code is emitted into the top-level decs-list, so
     that all classes are stored in the same typedecs, allowing them
     to see their subclasses and be able to build a variant for each
     of them.  */
  void
  DesugarVisitor::operator()(const ast::TypeDecs& e)
  {
    parse::Tweast functions;
    // Is used to know what class/method pair we already have seen for the
    // sub dispatch functions.
    dispatch_list_type sub_dispatches;
    for (const ast::TypeDec* t : e.decs_get())
      {
        const type::Class* cls = nullptr;
  // FIXME: Some code was deleted here (Get the ty's class type).

        if (cls)
            handle_class(e, cls, functions, sub_dispatches);
        else
          {
            /* FIXME: In the rest of the visitor, the
               simply-clone-this-node case is handled before the
               desugar-this-node case.  */
            // Otherwise, clone the type declaration.
            ast::TypeDec* typedec = recurse(*t);
            assertion(typedec);
            types_ << *typedec << '\n';
          }
      }

    ast::DecsList* funs_list = parse::parse(functions);
    result_ = funs_list;
  }

  /*------------------------------------------------.
  | Desugar class instantiations and object usage.  |
  `------------------------------------------------*/

  void
  DesugarVisitor::operator()(const ast::VarDec& e)
  {
    /* We don't desugar everything using concrete syntax here, because
       it would require a lot of additional manipulations, as we
       cannot easily produce a single VarDec from a parsing.  Also
       working from VarDecs (with an `s') doesn't help much either, as
       VarDec (with no `s') are also found in FunctionDec.  */

    // If this is not an object instantiation, delegate to the cloner.

    const type::Class* class_type = class_type_query(e);
    if (!class_type)
      return super_type::operator()(e);

    // Otherwise, handle the different cases.
    const ast::Location& location = e.location_get();
    ast::NameTy* type_name = nullptr;
    ast::Exp* init = nullptr;
    if (e.init_get())
      {
        // Object (variable) declaration.
        if (e.type_name_get())
          {
            type_name = recurse(e.type_name_get());
            init = recurse(e.init_get());
            // If the dynamic type is non-nil and different from the
            // static type, cast INIT to the latter.
  // FIXME: Some code was deleted here.
          }
        else
          // No manifest type: simply clone the declaration as-is.
          return super_type::operator()(e);
      }
    else
      // Formal declaration.
      type_name = recurse(e.type_name_get());

    const misc::symbol& name = e.name_get();

    result_ = new ast::VarDec(location, name,
                              type_name, init);
    postcondition(type_name || init);
  }


  // Desugar a class instantiation as a call to the desugared ctor routine.
  void
  DesugarVisitor::operator()(const ast::ObjectExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  DesugarVisitor::operator()(const ast::IfExp& e)
  {
  // FIXME: Some code was deleted here.
  }

  void
  DesugarVisitor::operator()(const ast::AssignExp& e)
  {
    // If this is not an object assignment, delegate to the cloner.
    const type::Class* lhs_class_type;
  // FIXME: Some code was deleted here.

    if (!lhs_class_type)
      return super_type::operator()(e);

    // Duplicate the subtrees of E.
    ast::Var* var = nullptr;
  // FIXME: Some code was deleted here (Recurse).

    ast::Exp* exp = nullptr;
  // FIXME: Some code was deleted here (Recurse).

    // If the RHS type is non-nil and different from the LHS type,
    // cast EXP to the latter.
  // FIXME: Some code was deleted here.
    ast::Exp* assignment =
      parse::parse(parse::Tweast() << var << " := " << exp);
    result_ = assignment;
  }


  ast::exps_type*
  DesugarVisitor::recurse_args(const ast::exps_type& actuals,
                               const type::Record& formals)
  {
    // For each argument, check the type of the actual argument
    // against the formal one.  If they are two different class types,
    // convert the actual argument to the expected type.
    auto args = new ast::exps_type;
    ast::exps_type::const_iterator i;
    type::Record::const_iterator j;
    for (i = actuals.begin(), j = formals.begin();
         i != actuals.end() && j != formals.end();
         ++i, ++j)
      {
        // Clone the argument.
        ast::Exp* arg = recurse(**i);

        // In the case of a class, handle the case of a (non-nil) actual
        // argument having a different type than the corresponding
        // formal.
        const type::Type* formal_type = &j->type_get().actual();
        auto formal_class_type = dynamic_cast<const type::Class*>(formal_type);
  // FIXME: Some code was deleted here.
        args->emplace_back(arg);
      }
    return args;
  }

  void
  DesugarVisitor::operator()(const ast::ArrayExp& e)
  {
    // We want to allow this:
    // let
    //   class A {}
    //   class B extends A {}
    //   type arrtype = array of A
    //   var arr := arrtype[10] of new B
    // in
    //   arr[0] := new B;
    //   arr[1] := new A
    // end
  // FIXME: Some code was deleted here.
  }

  void
  DesugarVisitor::operator()(const ast::RecordExp& e)
  {
    // We want to allow this:
    // let
    //   class A {}
    //   class B extends A {}
    //   type rectype = { a : A }
    //   var rec := rectype { a = new B }
    // in
    // end
  // FIXME: Some code was deleted here.
  }

  void
  DesugarVisitor::operator()(const ast::CallExp& e)
  {
    const type::Function* function_type;
  // FIXME: Some code was deleted here.

    const ast::Location& location = e.location_get();
  // FIXME: Some code was deleted here (Grab name).

  // FIXME: Some code was deleted here (Actual arguments).

    // (Types of) formal arguments.
    const type::Record& formals = function_type->formals_get();
    // Desugar the arguments and handle possible polymorphic assignments.
  // FIXME: Some code was deleted here.

  // FIXME: Some code was deleted here (Instantiate into result).
  }

  /*------------------------------------.
  | Desugar accesses to class members.  |
  `------------------------------------*/

  void
  DesugarVisitor::operator()(const ast::FieldVar& e)
  {
    // Check the type of the variable to see whether it is a class or
    // a record.
    const type::Class* class_type;
  // FIXME: Some code was deleted here.

    // If this is not a class, delegate to the cloner.
    if (!class_type)
      return super_type::operator()(e);

  // FIXME: Some code was deleted here (Grab name).

    // Otherwise, desugar this FieldVar as an access to an attribute.

    // Look for the attribute within the class and its base classes.
    const type::Class* owner = nullptr;
    for (const type::Class* c = class_type; c; c = c->super_get())
      {
  // FIXME: Some code was deleted here.
      }
    assertion(owner);

    ast::Var* var;
  // FIXME: Some code was deleted here (Recurse).

    ast::Exp* attr_var =
      parse::parse(parse::Tweast() <<
                   var <<
                   "." << variant_field_prefix << class_names_(owner) <<
                   "."
  // FIXME: Some code was deleted here.
                   );
    result_ = attr_var;
  }

  void
  DesugarVisitor::operator()(const ast::MethodCallExp& e)
  {
    const type::Method* method_type;
  // FIXME: Some code was deleted here (Initialize method_type).
    const type::Class* owner_type = method_type->owner_get();

    const ast::Location& location = e.location_get();
    std::string name = dispatch_fun_name(owner_type, method_type);

  // FIXME: Some code was deleted here (Fetch actual arguments).

    // (Types of) formal arguments.
    const type::Record& formals = method_type->formals_get();
    // Desugar the arguments and handle possible polymorphic assignements.
    ast::exps_type* args;
  // FIXME: Some code was deleted here (Initialize args).

    // Process the target of the method call, and convert it to the
    // expected type if needed.
    ast::Exp* object;
  // FIXME: Some code was deleted here (Recurse).

  // FIXME: Some code was deleted here (Adapt type).
    // Prepend the target to the actual arguments, as the desugared
    // method expects to find it as its first arguments.
    args->insert(args->begin(), object);

    // Turn the method call into a function call to the desugared method.
  // FIXME: Some code was deleted here (Instanciate into result).
  }

  /*--------------------------.
  | New types and functions.  |
  `--------------------------*/

  // Introduce a desugared builtin Object in the top-level function.
  void
  DesugarVisitor::operator()(const ast::FunctionDec& e)
  {
    bool is_main;
  // FIXME: Some code was deleted here (Setup is_main).
    if (is_main)
      {
        // Desugared data structures of the builtin Object.
        types_
            << "   type " << class_variant_prefix << "Object ="
            << variant_ty(&type::Class::object_instance());
        // Object's class id.
        class_ids_ <<
                   "   var  " << class_id_prefix << "Object := "
                   "        " << type::Class::object_instance().id_get();
      }

    // Process E.
    super_type::operator()(e);
    if (is_main)
      {
        // Object's ctor.
        parse::Tweast funs_tweast;
        funs_tweast <<
                    "   function " << class_ctor_prefix << "Object() :"
                    "     " << class_variant_prefix << "Object =";
        // Initialize the variant (a single field is filled, the one
        // corresponding to Object).
        field_inits_type object_init;
        misc::put(object_init, &type::Class::object_instance(),
                  std::string(class_contents_prefix) + "Object {}");
        // Create the variant.
        funs_tweast << variant_exp(&type::Class::object_instance(),
                                   &type::Class::object_instance(),
                                   object_init);

        // Parse the built TWEASTs.
        ast::DecsList* types = parse::parse(types_);
        ast::DecsList* class_ids = parse::parse(class_ids_);
        ast::DecsList* funs = parse::parse(funs_tweast);
        // Gather these declarations.
        types->splice_back(*class_ids);
        types->splice_back(*funs);
        // Add them to the top of the program.
        auto res = dynamic_cast<ast::FunctionDec*>(result_);
        parse::Tweast input;
        input << "let " << types << " in " << res->body_get() << " end";
        res->body_set(parse::parse(input));
      }

    // Cast the return value of the function if needed.
    if (e.body_get() && e.result_get())
      {
        const type::Class* body_type = class_type_query(*e.body_get());
        const type::Class* result_type = class_type_query(*e.result_get());
        if (body_type && result_type && body_type != result_type)
          {
            auto res = dynamic_cast<ast::FunctionDec*>(result_);
            parse::Tweast input;
            input << upcast_fun_name(body_type, result_type)
                  << " (" << res->body_get() << ")";
            res->body_set(parse::parse(input));
          }
      }
  }

  void
  DesugarVisitor::operator()(const ast::NameTy& e)
  {
    // Check if E is the name of a class; if not, just clone it.
    const type::Class* class_type = class_type_query(e);
    if (!class_type)
      return super_type::operator()(e);

    // Otherwise, desugar the name of E.
    const ast::Location& location = e.location_get();
    result_ = new ast::NameTy(location,
                              class_variant_prefix +
                              class_names_(class_type).get());
  }

} // namespace object
