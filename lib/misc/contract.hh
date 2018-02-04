/**
 ** \file  misc/contract.hh
 ** \brief Replacement for cassert.
 **/

#pragma once

// Use GCC magic bits to specify we cannot return from these functions

#ifndef __attribute__
# if !defined __GNUC__
#  define __attribute__(Spec) /* empty */
# endif
#endif

[[noreturn]] void __FailedCondition(const char* condType,
                       const char* condText,
                       const char* fileName,
                       int fileLine);

[[noreturn]] void __Terminate(const char*, int, const char*);

#define die(Reason)              __Terminate(__FILE__, __LINE__, Reason)
#define unreachable()            die("unreachable code reached")



#ifdef NDEBUG

# define assertion(Expr)         ((void) 0)
# define invariant(Expr)         ((void) 0)
# define precondition(Expr)      ((void) 0)
# define postcondition(Expr)     ((void) 0)

#else // NDEBUG

# define __TestCondition(CondType, Expr)                                \
  ((void) ((Expr) ? 0 : (__FailedCondition(#CondType, #Expr,            \
                                           __FILE__, __LINE__ ), 0)))

# define assertion(Expr)         __TestCondition(Assertion, Expr)
# define invariant(Expr)         __TestCondition(Invariant, Expr)
# define precondition(Expr)      __TestCondition(Precondition, Expr)
# define postcondition(Expr)     __TestCondition(Postcondition, Expr)

#endif // ! NDEBUG
