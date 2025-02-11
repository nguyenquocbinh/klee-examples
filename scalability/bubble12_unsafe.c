/*
 * Bubble sort
 * 
 * From
 * http://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
 *
 * This is an example whose analysis by naive path
 * exploration is expensive. Note that the paper
 * "Sorting nine inputs requires twenty-five comparisons"
 * by Codish et al. http://arxiv.org/abs/1405.5754
 * suggests that in standard sorting algorithm there can 
 * possibly be plenty of superfluous comparisons.
 *
 * This is a version with 12 elements and with a bug
 * introduced to re-swap the last two elements.
 */
#include <klee/klee.h>
#include <assert.h>

#define ARRAY_SIZE 12

int main() {
  int a[ARRAY_SIZE];
  int n, c, d, swap;
 
  klee_make_symbolic(a, ARRAY_SIZE * sizeof(int), "a");

  for (c = 0 ; c < ( ARRAY_SIZE - 1 ); c++)
  {
    for (d = 0 ; d < ARRAY_SIZE - c - 1; d++)
    {
      if (a[d] > a[d+1]) /* For decreasing order use < */
      {
        swap       = a[d];
        a[d]   = a[d+1];
        a[d+1] = swap;
      }
    }
  }

  int tmp = a[10];
  a[10] = a[11];
  a[11] = tmp;

  assert (a[0] <= a[1] &&
	  a[1] <= a[2] &&
	  a[2] <= a[3] &&
	  a[3] <= a[4] &&
	  a[4] <= a[5] &&
	  a[6] <= a[7] &&
	  a[7] <= a[8] &&
	  a[8] <= a[9] &&
	  a[9] <= a[10] &&
	  a[10] <= a[11]);
}
