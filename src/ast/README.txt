* README

Tiger Abstract Syntax Tree nodes with their principal members.
Incomplete classes are tagged with a `*'.
Completed classes are tagged with a '-'.
Classes containing a pointer to a definition are tagged with '+'.

/Ast/               (Location location)
  /Dec/             (symbol name)
    FunctionDec     (VarDecs formals, NameTy result, Exp body)
      MethodDec     ()
    TypeDec         (Ty ty)
    VarDec          (NameTy type_name, Exp init)

  /Exp/             ()
    /Var/           ()
      CastVar       (Var var, Ty ty)
-     FieldVar      // with pointer to the previous one on lvalue
 +    SimpleVar     (symbol name)
      SubscriptVar  (Var var, Exp index)

-   ArrayExp
-   AssignExp
-   BreakExp
-+  CallExp
*+    MethodCallExp
    CastExp         (Exp exp, Ty ty)
    ForExp          (VarDec vardec, Exp hi, Exp body)
-   IfExp
    IntExp          (int value)
-   LetExp
    NilExp          ()
-   ObjectExp
    OpExp           (Exp left, Oper oper, Exp right)
-   RecordExp
-   SeqExp
-   StringExp
    WhileExp        (Exp test, Exp body)

  /Ty/              ()
    ArrayTy         (NameTy base_type)
    ClassTy         (NameTy super, DecsList decs)
 +  NameTy          (symbol name)
-   RecordTy        // list of tyfields, ie list of Field
  /Decs/
    AnyDecs

  DecsList          (decs_type decs)

  Field             (symbol name, NameTy type_name) // ie tyField

  FieldInit         (symbol name, Exp init) // ie record creation field

Some of these classes also inherit from other classes.

/Escapable/
  VarDec            (NameTy type_name, Exp init)

/Typable/
  /Dec/             (symbol name)
  /Exp/             ()
  /Ty/              ()

/TypeConstructor/
  /Ty/              ()
  FunctionDec       (VarDecs formals, NameTy result, Exp body)
  NilExp            ()
  TypeDec           (Ty ty)

