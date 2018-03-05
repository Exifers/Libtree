// -*- C++ -*-

%module tiger_escapes

%include "std_string.i"

%import "ast/tiger_ast.i"

%{
  #include <escapes/libescapes.hh>
%}

%include "escapes/libescapes.hh"
