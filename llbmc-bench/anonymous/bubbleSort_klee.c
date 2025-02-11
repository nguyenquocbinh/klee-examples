/*
cd ~/nus/kleetest/llbmc-bench/anonymous
clang -emit-llvm -c bubbleSort_klee.c -o bubbleSort_klee.bc
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/tracerx/klee/Release+Asserts/bin/klee bubbleSort_klee.bc   
*/
#include <klee/klee.h>
#include <stdlib.h>
#include <assert.h>

#include <assert.h>
#include <stdio.h>

void bubbleSort(int *a, int N)
{
    int j, i;
    for (j = 0; j < N - 1; j++) {
        for (i = 0; i < N - j - 1; i++) {
            if (a[i] > a[i + 1]) {
                int t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
            }
        }
    }

    for (j = 0; j < N - 1; j++) {
       assert(a[j] <= a[j + 1]);
    }
}

int main()
{	
    int N = 3;
    int i;
    int *a = malloc(N * sizeof(int));
    for (i = 0; i < N; i++) {
        int s;
        klee_make_symbolic(&s, sizeof(s), "s");
        a[i] = s;
    }
    bubbleSort(a, N);
    free(a);
    return 0;
}
