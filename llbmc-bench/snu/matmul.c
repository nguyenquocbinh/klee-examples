/*
clang -g -emit-llvm -c matmul.c -o matmul.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee matmul.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: matmul.c                                                       */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Matrix multiplication for 5x5 integer matrices.                   */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/


#define SIZE 5

int a[SIZE+1][SIZE+1] = { {0,0,0,0,0,0},
			  {0,0,9,4,7,9},
			  {0,12,14,15,16,11},
			  {0,2,3,4,5,6},
			  {0,4,3,2,1,2},
			  {0,2,7,6,4,9} };
int b[SIZE+1][SIZE+1] = { {0,0,0,0,0,0},
			  {0,0,9,4,7,9},
			  {0,12,14,15,16,11},
			  {0,2,3,4,5,6},
			  {0,4,3,2,1,2},
			  {0,2,7,6,4,9} };
int c[SIZE+1][SIZE+1];

void matmul(a,b,c)
  int a[SIZE+1][SIZE+1], b[SIZE+1][SIZE+1], c[SIZE+1][SIZE+1];
{
  int i,j,k;

IL0:  for(i=1;i<=SIZE;i++)
  IL1: for(j=1;j<=SIZE;j++)
      c[i][j] = 0;

CL0:  for(i=1;i<=SIZE;i++)
 CL1:   for(j=1;j<=SIZE;j++)
  CL2:   for(k=1;k<=SIZE;k++)
	c[i][j] += a[i][k] * b[k][j];

}

int main()
{
    matmul(a,b,c);
    return 0;
}
	 

