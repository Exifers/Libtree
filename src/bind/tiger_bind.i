// -*- C++ -*-

%module tiger_bind

%include "std_string.i"

%import "ast/tiger_ast.i"

%{
  #include <bind/libbind.hh>
%}

%include "bind/libbind.hh"
