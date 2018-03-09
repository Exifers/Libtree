/**
 ** \file parse/tweast.cc
 ** \brief Implementation of parse::Tweast.
 */

#include <sstream>

#include <boost/algorithm/string/replace.hpp>

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
    , MetavarMap<Tweast>::MetavarMap("tweast")
    , input_(str)
  {}

  void
  Tweast::flatten()
  {
    using tweasts_type = MetavarMap<Tweast>;
    using tweasts_map_type = tweasts_type::map_type;

    // Recursively flatten each Tweast metavariable.
    for (const tweasts_map_type::value_type& t : tweasts_type::map_)
      t.second->flatten();

    // Grab each non-Tweast metavariable of Tweast metavariables, and
    // renumber the metavariables.
    for (const tweasts_map_type::value_type& t : tweasts_type::map_)
      {
        unsigned tweast_index = t.first;
        Tweast& tweast = *t.second;

        // Tweast input.
        std::string tweast_input = tweast.input_get();
        // Move metavariables to THIS and rename them.
        move_metavars_<ast::Exp>(tweast, tweast_input);
        move_metavars_<ast::Var>(tweast, tweast_input);
        move_metavars_<ast::NameTy>(tweast, tweast_input);
        move_metavars_<ast::DecsList>(tweast, tweast_input);

        // Replace the tweast metavariable reference with its input string.
        std::string tweast_var = tweasts_type::show(tweast_index);
        std::string input = input_.str();
        boost::algorithm::replace_first(input,
                                        tweast_var, tweast_input);
        input_.str(input);
      }

    // Delete aggregated Tweasts, and remove their associated
    // metavariable from the map of Tweasts.
    for (const tweasts_map_type::value_type& t : tweasts_type::map_)
      delete t.second;
    tweasts_type::map_.clear();
  }

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
      << "Tweast map:"
      << misc::incendl << MetavarMap<Tweast>::map_ << misc::decendl
      << "Input string:"
      << misc::incendl << input_.str() << misc::decendl;
  }

  std::ostream&
  operator<<(std::ostream& ostr, const Tweast& in)
  {
    return in.dump(ostr);
  }

} // namespace parse
