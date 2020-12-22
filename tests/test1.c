/* file minunit_example.c */

#include <stdio.h>
#include "minunit.h"
#include "configparse"

int tests_run = 0;

static char* test_add1() {
  mu_assert("error, add1(1) != 1", add1(1) == 2);
  return 0;
}

static char* all_tests() {
  mu_run_test(test_add1);
  return 0;
}

int main(int argc, char** argv) {
  char* result = all_tests();
  if (result != 0) printf("%s\n", result);
  else printf("ALL TESTS PASSED\n");

  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
