/**
 ** \file parse/tweast.cc
 ** \brief Implementation of parse::Tweast.
 */

#include <sstream>


#include <parse/tweast.hh>

namespace parse
{

  unsigned Tweast::count_ = 0;

  Tweast::Tweast()
    : Tweast("")
  {}

  Tweast::Tweast(const std::string& str)
    : MetavarMap<ast::Exp>::MetavarMap("exp")
    , MetavarMap<ast::Var>::MetavarMap("lvalue")
    , MetavarMap<ast::NameTy>::MetavarMap("namety")
    , MetavarMap<ast::DecsList>::MetavarMap("decs")
    , input_(str)
  {}


  std::string
  Tweast::input_get() const
  {
    return input_.str();
  }

  std::ostream&
  Tweast::dump(std::ostream& ostr) const
  {
    return ostr
      << "Exp map:"
      << misc::incendl << MetavarMap<ast::Exp>::map_ << misc::decendl
      << "Var map:"
      << misc::incendl << MetavarMap<ast::Var>::map_ << misc::decendl
      << "NameTy map:"
      << misc::incendl << MetavarMap<ast::NameTy>::map_ << misc::decendl
      << "DecsList map:"
      << misc::incendl << MetavarMap<ast::DecsList>::map_ << misc::decendl
      << "Input string:"
      << misc::incendl << input_.str() << misc::decendl;
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Tweast& in)
  {
    return in.dump(ostr);
  }

} // namespace parse
