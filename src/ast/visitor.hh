/**
 ** \file ast/visitor.hh
 ** \brief Definition of ast::Visitor.
 */

#pragma once

#include <functional>
#include <ast/fwd.hh>
#include <misc/select-const.hh>

namespace ast
{

  /** \brief Root class of all Ast visitors.
   **
   ** GenVisitor<CONSTIFY> is the root class of all Ast visitors. */
  template <template <typename> class Const>
  class GenVisitor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Convenient abbreviation.
    template <typename Type>
    using const_t = typename Const<Type>::type;

    /// Destroy a GenVisitor.
    virtual ~GenVisitor();
    /** \} */

    /// The entry point: visit \a e.
    virtual void operator()(const_t<Ast>& e);
    virtual void operator()(const_t<ArrayExp>&) = 0;
    virtual void operator()(const_t<ArrayTy>&) = 0;
    virtual void operator()(const_t<AssignExp>&) = 0;
    virtual void operator()(const_t<BreakExp>&) = 0;
    virtual void operator()(const_t<CallExp>&) = 0;
    virtual void operator()(const_t<CastExp>&) = 0;
    virtual void operator()(const_t<CastVar>&) = 0;
    virtual void operator()(const_t<ClassTy>&) = 0;
    virtual void operator()(const_t<DecsList>&) = 0;
    virtual void operator()(const_t<Field>&) = 0;
    virtual void operator()(const_t<FieldInit>&) = 0;
    virtual void operator()(const_t<FieldVar>&) = 0;
    virtual void operator()(const_t<ForExp>&) = 0;
    virtual void operator()(const_t<FunctionDec>&) = 0;
    virtual void operator()(const_t<IfExp>&) = 0;
    virtual void operator()(const_t<IntExp>&) = 0;
    virtual void operator()(const_t<LetExp>&) = 0;
    virtual void operator()(const_t<MethodCallExp>&) = 0;
    virtual void operator()(const_t<MethodDec>&) = 0;
    virtual void operator()(const_t<NameTy>&) = 0;
    virtual void operator()(const_t<NilExp>&) = 0;
    virtual void operator()(const_t<ObjectExp>&) = 0;
    virtual void operator()(const_t<OpExp>&) = 0;
    virtual void operator()(const_t<RecordExp>&) = 0;
    virtual void operator()(const_t<RecordTy>&) = 0;
    virtual void operator()(const_t<SeqExp>&) = 0;
    virtual void operator()(const_t<SimpleVar>&) = 0;
    virtual void operator()(const_t<StringExp>&) = 0;
    virtual void operator()(const_t<SubscriptVar>&) = 0;
    virtual void operator()(const_t<TypeDec>&) = 0;
    virtual void operator()(const_t<VarDec>&) = 0;
    virtual void operator()(const_t<WhileExp>&) = 0;

    virtual void operator()(const_t<FunctionDecs>&) = 0;
    virtual void operator()(const_t<MethodDecs>&) = 0;
    virtual void operator()(const_t<TypeDecs>&) = 0;
    virtual void operator()(const_t<VarDecs>&) = 0;

    /// Helper to visit nodes manipulated via a pointer.
    template <class E> void operator()(E* e);

  protected:
    /** A convenient shortcut for recurring code like this:

        \code
        if (e)
          e->accept(*this);
        \endcode

        However, the drawback of this approach is that it doesn't take
        care of the constness, and any \a const violation will be
        reported \em within the body of this method, not at its
        corresponding call site.

        We cannot use the misc/select_const.hh approach here, since
        the compiler cannot resolve a function overloaded or
        specialized on an associated type of a template.  E.g., writing
        \a accept like this:

        \code
        template <typename E>
        void accept(const_t<E>* e);
        \endcode

        won't work directly.  Of course, one can help the compiler,
        providing it with \a E

        \code
        accept<ast::NameTy>(e.result_get());
        \endcode

        but this is painful.  */
    template <typename E>
    void accept(E* e);
  };

# define VISITOR_VISIT_NODE_(Z, N, Array)                      \
    virtual void operator()(ast::BOOST_PP_ARRAY_ELEM(N, Array)& e);

# define VISITOR_VISIT_NODES(Nodes)                    \
  BOOST_PP_REPEAT(BOOST_PP_ARRAY_SIZE(Nodes),          \
                 VISITOR_VISIT_NODE_,                  \
                 Nodes)

  /// Shorthand for a const visitor.
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  /// Shorthand for a non const visitor.
  using Visitor = GenVisitor<misc::id_traits>;

} // namespace ast

#include <ast/visitor.hxx>
