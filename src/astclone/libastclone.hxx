#pragma once

#include <ast/exp.hh>
#include <astclone/cloner.hh>
#include <astclone/libastclone.hh>

// Define exported clone functions.
namespace astclone
{

  template <typename T>
  T*
  clone(const T& tree)
  {
    Cloner clone;
    clone(tree);
    return dynamic_cast<T*>(clone.result_get());
  }

  template <typename A>
  void
  apply(applicable<A> f, std::unique_ptr<A>& t1)
  {
    A* t2 = f(*t1);
    t1.reset(t2);
  }

  template <typename A>
  void
  apply(applicable_with_bools<A> f, std::unique_ptr<A>& t1, bool cond_1, bool cond_2)
  {
    A* t2 = f(*t1, cond_1, cond_2);
    t1.reset(t2);
  }

  template <typename A, typename B>
  void
  apply(applicable_object<A, B> f, std::unique_ptr<A>& t1, B& t3)
  {
    A* t2 = f(*t1, t3);
    t1.reset(t2);
  }

} // namespace astclone
