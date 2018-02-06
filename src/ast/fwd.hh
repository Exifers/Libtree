/**
 ** \file ast/fwd.hh
 ** \brief Forward declarations of all AST classes
 ** (needed by the visitors).
 */

#pragma once

#include <vector>
#include <list>
#include <misc/fwd.hh>
#include <misc/vector.hh>


namespace ast
{

  class ArrayExp;
  class ArrayTy;
  class AssignExp;
  class Ast;
  class BreakExp;
  class CallExp;
  class CastExp;
  class CastVar;
  class ClassTy;
  class Dec;
  class DecsList;
  class Exp;
  class Field;
  class FieldInit;
  class FieldVar;
  class ForExp;
  class FunctionDec;
  class IfExp;
  class IntExp;
  class LetExp;
  class MethodCallExp;
  class MethodDec;
  class NameTy;
  class NilExp;
  class ObjectExp;
  class OpExp;
  class RecordExp;
  class RecordTy;
  class SeqExp;
  class SimpleVar;
  class StringExp;
  class SubscriptVar;
  class Ty;
  class TypeDec;
  class Var;
  class VarDec;
  class WhileExp;


  // From visitor.hh
  template <template <typename> class Const>
  class GenVisitor;
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  using Visitor = GenVisitor<misc::id_traits>;

  // Collections of nodes.
  using exps_type = std::vector<Exp*>;
  using fieldinits_type = std::vector<FieldInit*>;
  using fields_type = std::vector<Field*>;

  // From decs.hh.
  class Decs;

  // From decs-list.hh.
  class DecsList;

  // From anydecs.hh.
  template <typename T>
  class AnyDecs;
  using FunctionDecs = AnyDecs<FunctionDec>;
  using MethodDecs = AnyDecs<MethodDec>;
  using TypeDecs = AnyDecs<TypeDec>;
  using VarDecs = AnyDecs<VarDec>;


} // namespace ast
