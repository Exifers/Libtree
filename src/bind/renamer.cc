/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{

  using namespace ast;

  Renamer::Renamer()
    : super_type(), new_names_()
  {}

  void Renamer::rename(ast::Dec& e)
  {
    std::string name = e.name_get().get() + "_";
    int number = 0;
    bool new_name = false;
    while (!new_name)
    {
      new_name = true;
      for (auto it = new_names_.begin(); it != new_names_.end(); it++)
      {
        if ((it->second).get() == (name + std::to_string(number)))
        {
          new_name = false;
          number++;
          continue;
        }
      }
    }
    misc::symbol sym{name + std::to_string(number)};
    new_names_[&e] = sym;
    e.name_set(sym);
  }

  void Renamer::operator()(ast::VarDec& e)
  {
    rename(e);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::FunctionDec& e)
  {
    rename(e);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::TypeDec& e)
  {
    rename(e);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::SimpleVar& e)
  {
    e.name_set(new_names_[e.def_get()]);
  }

  void Renamer::operator()(ast::CallExp& e)
  {
    e.name_set(new_names_[e.def_get()]);
    super_type::operator()(e);
  }

  void Renamer::operator()(ast::NameTy& e)
  {
    e.name_set(new_names_[e.def_get()]);
  }
} // namespace bind
