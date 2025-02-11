/*
Copyright 2016 National University of Singapore

clang -emit-llvm -c -g addition_safe8.c -o addition_safe8.bc
time ~/git/original/klee/Release+Asserts/bin/klee -allow-external-sym-calls -only-output-states-covering-new -search=dfs addition_safe8.bc 2>log


*/
#include <klee/klee.h>
#include <assert.h>

int y;

int add(int p1, int p2, int p3, int x, int y) {
    klee_assume(x <= 0);
    klee_assume(y >= 0);
    klee_assume(y <= 35);

    if (p1 > 8){
      x = x + 1;
      x = x + y;
    }
    else
      x = x + 2;
    if (p2 > 8)
      x = x + 1;
    else {
      x = x + 2;
    }
    if (p3 > 8) {
      x = x + 1;
    } else {
      x = x + y;
    }

    assert(x <= (2*y + 6));
  
  return x;
}
int main() {
  int p1, p2, p3, x;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
  return add(p1, p2, p3, x, y);
}
