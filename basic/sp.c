/*
 * Copyright 2015 National University of Singapore 
 *
 * cd
 * cd nus/kleetest
 * llvm-gcc --emit-llvm -c -g sp.c
 * llvm-gcc -S --emit-llvm sp.c
 * opt -analyze -dot-cfg sp.o
 * klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs sp.o
 * ktest-tool --write-ints klee-last/test00000?.ktest
 */
#include <klee/klee.h>
#include <assert.h>

void proc(int x, int y) {
  int z = 5;

  // These assumes are to prevent underflow
  klee_assume (x >= -1);
  klee_assume (y >= -1);

  if (x > 0) {
    x = 2;
  } else {
    x += 2;
  }

  if (y > 0) {
    y = 2;
    x++;
  } else {
    y += 2;
    x++;
  }

  assert(x + y <= z);
}

int main() {
  int x, y;

  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");

  proc(x, y);
  return 0;
} 
