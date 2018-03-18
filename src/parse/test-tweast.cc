/**
 ** Test the tweast.
 **/

#include <iostream>
#include <ast/decs-list.hh>
#include <ast/libast.hh>
#include <ast/name-ty.hh>
#include <ast/seq-exp.hh>
#include <ast/simple-var.hh>
#include <misc/contract.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/location.hh>
#include <parse/tweast.hh>

const char* program_name = "test-tweast";

int
main()
{
  try
    {
      parse::Tweast in;
      parse::location l;
      ast::Exp* exp = new ast::SeqExp(l, new ast::exps_type);
      ast::Var* var = new ast::SimpleVar(l, "a");
      ast::NameTy* namety = new ast::NameTy(l, "int");
      ast::DecsList* decs = new ast::DecsList(l);

      in << decs
         << " function f(a :" << namety << ") : " << namety
         << " = (" << exp << "; " << var << ")";

      assertion(decs == in.take<ast::DecsList>(0));
      assertion(namety == in.take<ast::NameTy>(1));
      assertion(namety == in.take<ast::NameTy>(2));
      assertion(exp == in.take<ast::Exp>(3));
      assertion(var == in.take<ast::Var>(4));

      delete exp;
      delete var;
      delete namety;
      delete decs;
    }
  catch (misc::error& e)
    {
      std::cerr << e;
      exit(e.status_get_value());
    }

  try
    {
      // Test Tweasts within a Tweast.
      parse::Tweast* op1 = new parse::Tweast;
      parse::Tweast* op2 = new parse::Tweast;
      parse::Tweast* op3 = new parse::Tweast;
      parse::Tweast op;

      *op1 << "1 + 2";
      *op2 << "3 * 4";
      *op3 << op1 << " - " << op2;
      op << "42 / (" << op3 << ")";

      ast::Exp* tree = parse::parse(op);
      std::cout << *tree << '\n';
      delete tree;
    }
  catch (misc::error& e)
    {
      std::cerr << e;
      exit(e.status_get_value());
    }
}
