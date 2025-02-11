/*
Copyright 2015 National University of Singapore 
Execute:  clang -emit-llvm -c addition.c -o addition.o

or

cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g addition.c
llvm-gcc -S --emit-llvm addition.c
opt -analyze -dot-cfg addition.o
klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs addition.o
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest
ktest-tool --write-ints klee-last/test000003.ktest

*/
#include <klee/klee.h>
#include <assert.h>

int add(int p1, int p2, int x) { 
  klee_assume(x <= 0);

  if (p1 > 8)
    x = x; 
  else
    x = x + 1;
  if (p2 > 8)
    x = x;
  else
    x = x + 2;
  
  assert(x <= 3);

  return x;
} 

int main() {
  int p1,p2, x;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&x, sizeof(x), "x");
  return add(p1, p2, x);
} 
