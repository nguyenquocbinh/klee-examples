/* 
 * Simple regular expression matching.
 *
 * From:
 *   The Practice of Programming
 *   Brian W. Kernighan, Rob Pike
 *
 * This code with KLEE harness is obtained from the following
 * page of the KLEE tutorial on December 2015:
 *   http://klee.github.io/resources/Regexp.c.html
 *
 * We disabled recursive calls so that the search space is
 * small, and we made symbolic the initial string. In addition
 * we also removed the loop in the match function.
 */ 

#include <klee/klee.h>

static int matchhere(char *re, char *text) {
  if (re[0] == '\0')
    return 0;
  if (re[1] == '*')
    /* return matchstar(re[0], re+2, text); */
    return 0;
  if (re[0] == '$' && re[1]=='\0')
    return *text == '\0';
  if (*text!='\0' && (re[0]=='.' || re[0]==*text))
    /* return matchhere(re+1, text+1); */
    return 0;
  return 0;
}

int match(char *re, char *text) {
  if (re[0] == '^')
    return matchhere(re+1, text);
  return 0;
}

/*
 * Harness for testing with KLEE.
 */

// The size of the buffer to test with.
#define SIZE 7

int main() {
  // The input regular expression.
  char re[SIZE];
  char str[6];

  // Make the inputs symbolic. 
  klee_make_symbolic(re, sizeof re, "re");
  klee_make_symbolic(str, sizeof str, "str");

  // Try to match against a constant string "hello".
  str[5] = 0;

  match(re, str);

  return 0;
}

