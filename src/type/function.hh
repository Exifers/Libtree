/**
 ** \file type/function.hh
 ** \brief The class Function.
 */
#pragma once

#include <type/fwd.hh>
#include <type/record.hh>
#include <type/type.hh>

namespace type
{

  /** \brief Function types.
   **
   ** Encapsulate the signature of a function, i.e. the type structures
   ** of both function's arguments and its result.  */
  class Function : public Type
  {
  public:
    /** \brief Construct a Function.
     **
     ** \param formals type structures of formal arguments.
     ** \param result type structure of what function returns. */
    Function(const Record* formals, const Type& result);

    /** \brief Destructor.
     **/
    virtual ~Function();

    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return the type structures of the function's arguments.
    const Record& formals_get() const;
    /// Return the type structure of the function's result.
    const Type& result_get() const;
    /** \} */

#warning // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Function).

  protected:
    /// Formals' types.
    const Record* formals_;

    /// Result's type.
    const Type& result_;
  };

} // namespace type

#include <type/function.hxx>
