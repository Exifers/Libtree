/**
 ** \file object/desugar-visitor.hh
 ** \brief Declaration of object::DesugarVisitor.
 */

#pragma once

#include <astclone/cloner.hh>
#include <object/libobject.hh>
#include <parse/tweast.hh>

namespace object
{

  /// \brief Desugar some object structures while duplicating an Ast.
  class DesugarVisitor : public astclone::Cloner
  {
  public:
    /// Superclass.
    using super_type = astclone::Cloner;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a DesugarVisitor.
    DesugarVisitor(const class_names_type& class_names);

    /// Destroy a DesugarVisitor.
    virtual ~DesugarVisitor() = default;

    /// Special version of the visit of a DecsList allowing the
    /// transformation of an ast::Decs to either a single ast::Decs or
    /// to an ast::DecsList.
    void operator()(const ast::DecsList& e) override;

    /// \name Desugar class declarations.
    /// \{

    /// Desugar class declarations.
    void operator()(const ast::TypeDecs& e) override;
    /// Handle the builtin Object.
    void operator()(const ast::FunctionDec& e) override;
    /// Desugar class names.
    void operator()(const ast::NameTy& e) override;

    /// \}

    /// \name Desugar class instantiations and object usage.
    /// \{

    /// Desugar polymorphic initializations.
    void operator()(const ast::VarDec& e) override;
    /// Desugar manifest objects.
    void operator()(const ast::ObjectExp& e) override;
    /// Desugar polymorphic branching.
    void operator()(const ast::IfExp& e) override;
    /// Desugar polymorphic assignments.
    void operator()(const ast::AssignExp& e) override;
    /// Desugar polymorphic insertion.
    void operator()(const ast::ArrayExp& e) override;
    void operator()(const ast::RecordExp& e) override;
    /// Add object casts around arguments when needed.
    void operator()(const ast::CallExp& e) override;

    /// \}

    /// \name Desugar accesses to class members.
    /// \{

    /// Desugar accesses to attributes.
    void operator()(const ast::FieldVar& e) override;
    /// Desugar calls to methods.
    void operator()(const ast::MethodCallExp& e) override;

    /// \}

    /// \brief Desugar actuals arguments in routine calls.
    ///
    /// \param actuals      the actual arguments of the initial AST
    /// \param formals      the formal arguments of the routine
    /// \return             the desugared actual arguments
    ast::exps_type* recurse_args(const ast::exps_type& actuals,
                                 const type::Record& formals);

    /// A list of classes (e.g., useful to represent a set of subclasses).
    using classes_type = std::vector<const type::Class*>;

  private:
    /// \name Code generation.
    /// \{

    using pair_class_method
      = std::pair<const type::Class*, const type::Method*>;
    using dispatch_list_type
      = std::set<pair_class_method>;

    /// \brief Desugar the constructor of the current class
    ///
    /// \param functions  the tweast containing the constructor being desugared
    /// \param cls        the class whose constructor is being desugared
    /// \param class_name the desugared version of the class name
    void desugar_constructor(parse::Tweast& functions,
                             const type::Class* cls,
                             const misc::symbol& class_name);

    /// \brief Desugar the current method.
    ///
    /// \param functions the tweast containing the method being desugared
    /// \param method    the methods being desugared
    /// \param class_name the desugared version of the class name
    void desugar_method(parse::Tweast& functions,
                        const type::Method* method,
                        const misc::symbol& class_name);

    /// \brief Dispatch the method between the different classes.
    ///
    /// \param functions      the tweast containing the dispatch
    /// \param e              the block of type being processed
    /// \param cls            the cls being desugared
    /// \param method         the method being dispatched
    /// \param class_name     the desugared version of the class name
    /// \param sub_dispatches the processed classes/methods for dispatch
    void dispatch_function(parse::Tweast& functions,
                           const ast::TypeDecs& e,
                           const type::Class* cls,
                           const type::Method* method,
                           const misc::symbol& class_name,
                           dispatch_list_type& sub_dispatches);

    /// \brief Handle a class declaration.
    ///
    /// This is a declaration of a class: remove it and replace it with
    ///
    /// (1) a class type label (integer constant),
    /// (2) new data structures:
    ///     - an actual structure holding the data of the class,
    ///     - a variant able to store any concrete type for this
    ///       class;
    /// (3) new functions:
    ///     - a constructor,
    ///     - conversion routines used in polymorphic assignments (upcasts),
    ///     - conversion routines used in dynamic dispatch (downcasts),
    ///     - (desugared) methods,
    ///     - dispatch functions.
    ///
    /// We must take care of the order in which these declarations
    /// are injected, since (1), (2) and (3) are declaration of
    /// different kinds (variable, type and function respectively).
    /// Mixing them would break the block of type declarations
    /// (TypeDecs, or ``chunk'' of TypeDec's) being currently
    /// visited.  Thus we collect all class definitions from E,
    /// replace them by new data structures ((2)) and inject the
    /// rest of the new material *after* the TypeDecs ((1) and
    /// (3)).
    void handle_class(const ast::TypeDecs& e,
                      const type::Class* cls,
                      parse::Tweast& functions,
                      dispatch_list_type& sub_dispatches);

    /// \brief Return the name of a type.
    ///
    /// \param type         either a builtin type or a type::Named
    /// \result             the name of the type
    std::string type_symbol(const type::Type* type);

    /// Return the name of the upcast function between types \a from
    /// and \a to.
    std::string upcast_fun_name(const type::Class* from,
                                const type::Class* to);
    /// Return the name of the downcast function between types \a from
    /// and \a to.
    std::string downcast_fun_name(const type::Class* from,
                                  const type::Class* to);

    /// Return the name of the dispatch function for \a method,
    /// defined in class \a owner.
    std::string dispatch_fun_name(const type::Class* owner,
                                  const type::Method* method);

    /// Check if the type \a source_type of \a source_exp matches
    /// \a target_type, and generate a type conversion wrapper if
    /// needed.
    void adapt_type(ast::Exp*& source_exp, const type::Class* source_type,
                    const type::Class* target_type);

    /// The type of a list of initializations for the field of a variant.
    using field_inits_type = misc::map<const type::Class*, std::string>;

    /// \brief Generate a variant expression.
    ///
    /// \param static_type  the type of the class whose variant is built
    /// \param exact_type   the exact type of the data stored in the variant
    /// \param inits        the initalization value of the variant (must be
    ///                     of type \a dynamic_type).
    /// \return             the generated variant expression
    ast::Exp* variant_exp(const type::Class* static_type,
                          const std::string& exact_type,
                          const field_inits_type& inits);

    /// Syntactic sugar for the previous routine.
    ast::Exp* variant_exp(const type::Class* static_type,
                          const type::Class* dynamic_type,
                          const field_inits_type& inits);

    /// \brief Populate a variant fields.
    ///
    /// \param class_type   the type of the class used to populate the variant
    /// \param input        the tweast containing the variant being built
    void fill_variant_fields(const type::Class* class_type,
                             parse::Tweast* input);

    /// \brief Generate code for a variant type on a TWEAST.
    ///
    /// Contrary to object::DesugarVisitor::variant_exp, we
    /// cannot directly generate an expression, since the client
    /// TWEAST won't accept an ast::Ty* as a metavariable.
    ///
    /// \param class_type   the type of the class whose variant is built
    /// \return             the TWEAST on which the code is generated
    parse::Tweast* variant_ty(const type::Class* class_type);

    /// \brief Populate an initialization list.
    ///
    /// \param class_type   the type of the class used to populate the list
    /// \param inits        the initialization list
    void fill_init_list(const type::Class* class_type,
                        field_inits_type& inits);

    /// \brief Generate a conversion routine.
    ///
    /// \param name         the type of the generated function
    /// \param source       the type of the converted value
    /// \param target       the target type of the conversion
    /// \param exact_type   the exact type of the returned variant
    /// \return             the TWEAST on which the code is generated
    parse::Tweast* cast_function(const std::string& name,
                                 const type::Class* source,
                                 const type::Class* target,
                                 const type::Class* exact_type);

    /// Syntactic sugar for object::DesugarVisitor::cast_function,
    /// used to generate an upcast function.
    parse::Tweast* upcast_function(const type::Class* source,
                                   const type::Class* target);

    /// Syntactic sugar for object::DesugarVisitor::cast_function,
    /// used to generate a downcast function.
    parse::Tweast* downcast_function(const type::Class* source,
                                     const type::Class* target);


    /// \brief Generate an expression looking like a switch
    /// expression, to dispatch a method call. Do not generate code
    /// for classes outside decs. If this function is used to create a sub
    /// dispatch function, recursive call should be true, in order to call
    /// the previous dispatch function if nothing matches.
    ///
    /// \param class_type        the static type of the class owning the method
    /// \param method            the called method
    /// \param decs              the current chunk
    /// \param dispatch_method   the recursively called dispatch method
    /// \return                  the generated expression
    ast::Exp* dispatch_switch(const type::Class* class_type,
                              const type::Method* method,
                              const ast::TypeDecs* decs,
                              const type::Method* dispatch_method = nullptr);

    /// \brief Generate a (static) call to a desugared method.
    ///
    /// \note The dynamic dispatch must have been performed before
    /// using this generator.
    ///
    /// \param class_name   the class where the method resides
    /// \param method_name  the name of the method
    /// \param target       the name of the target (object)
    /// \param formals      the actual arguments (other than the target)
    /// \return             the TWEAST on which the code is generated
    parse::Tweast* method_call(const misc::symbol& class_name,
                               const misc::symbol& method_name,
                               const std::string& target,
                               const ast::VarDecs::Ds& formals);

    /// \}

  private:
    /// The names of the classes defined in the program.
    class_names_type class_names_;

    /// TWEAST of desugared types.
    parse::Tweast types_;
    /// TWEAST of class ids.
    parse::Tweast class_ids_;

    /// Map / counter giving the correct current dispatch extensions for a method
    misc::map<const type::Method*, unsigned int> dispatch_map_;
  };

} // namespace object
