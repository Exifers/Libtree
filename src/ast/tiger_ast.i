// -*- C++ -*-

%module tiger_ast

%include "std_string.i"

%{
#  include <sstream>
#  include <fstream>

#  include <ast/visitor.hh>
#  include <ast/all.hh>
#  include <ast/libast.hh>
%}

// Ignore C++11 `override' attributes, not understood by SWIG 2.
#define override

%rename (super_visitor) std::unary_function<ast::Ast, void>;
class std::unary_function<ast::Ast, void>
{};

%include "ast/fwd.hh"

%include "ast/visitor.hh"

%include "ast/location.hh"

%include "ast/escapable.hh"

%include "ast/ast.hh"
%extend ast::Ast
{
  std::string
  __str__ () const
  {
    std::ostringstream o;
    o << *$self;
    return o.str ();
  }
}



// Exps.
%include "ast/exp.hh"
%include "ast/nil-exp.hh"
%include "ast/int-exp.hh"
%include "ast/string-exp.hh"
%include "ast/call-exp.hh"
%include "ast/op-exp.hh"
%include "ast/record-exp.hh"
%include "ast/seq-exp.hh"
%include "ast/assign-exp.hh"
%include "ast/if-exp.hh"
%include "ast/while-exp.hh"
%include "ast/for-exp.hh"
%include "ast/break-exp.hh"
%include "ast/let-exp.hh"
%include "ast/array-exp.hh"

// Vars.
%include "ast/var.hh"
%include "ast/simple-var.hh"
%include "ast/field-var.hh"
%include "ast/subscript-var.hh"

// Tys.
%include "ast/ty.hh"
%include "ast/name-ty.hh"
%include "ast/record-ty.hh"
%include "ast/array-ty.hh"
%include "ast/class-ty.hh"

// Decs.
%include "ast/dec.hh"
%include "ast/function-dec.hh"
%include "ast/method-dec.hh"
%include "ast/var-dec.hh"
%include "ast/type-dec.hh"
%include "ast/decs.hh"
%include "ast/decs-list.hh"
%include "ast/any-decs.hh"


%include "ast/libast.hh"
