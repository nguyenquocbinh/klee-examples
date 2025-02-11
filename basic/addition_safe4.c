/*
Copyright 2015 National University of Singapore

cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g addition_safe4.c
llvm-gcc -S --emit-llvm addition_safe4.c
opt -analyze -dot-cfg addition_safe4.o
klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs addition_safe4.o
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest
ktest-tool --write-ints klee-last/test000003.ktest

*/
#include <klee/klee.h>
#include <assert.h>

int y;

/*
 * This is an example to test if the dependency
 * of the assertion to z is computed correctly.
 */
int add(int p1, int p2, int p3, int x) {
  int z = 6;

  klee_assume(x <= 0);
  
  if (p1 > 8)
    x = x + 1;
  if (p2 > 8)
    x = x;
  else
    x = x + 2;
  if (p3 > 8)
    x = x + 3;

  assert(x <= z);
  return x;
}

int main() {
  int p1, p2, p3;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&y, sizeof(y), "y");
  return add(p1, p2, p3, y);
}
