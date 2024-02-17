#include "../index/TSDDA.h"
#include <stdio.h>

int main() {

  // Create
  TStoixeiouDDA* ss1 = TSDDA_create(0, 10);
  TStoixeiouDDA* ss2 = TSDDA_create(1, 11);
  TStoixeiouDDA* ss3 = TSDDA_create(0, 12);

  // Print
  printf("\nprint:\n--------\n");
  TSDDA_print("ss1: ", (void*)ss1);
  printf("\n");
  TSDDA_print("ss2: ", (void*)ss2);
  printf("\n");
  TSDDA_print("ss3: ", (void*)ss3);
  printf("\n");

  // Compare
  printf("\ncompare:\n------------\n");
  TSDDA_print("", (void*)ss1);
  printf(" cmp ");
  TSDDA_print("", (void*)ss2);
  printf(" = %d\n", TSDDA_compare((void*)ss1, (void*)ss2));

  TSDDA_print("", (void*)ss1);
  printf(" cmp ");
  TSDDA_print("", (void*)ss3);
  printf(" = %d\n", TSDDA_compare((void*)ss1, (void*)ss3));

  TSDDA_print("", (void*)ss2);
  printf(" cmp ");
  TSDDA_print("", (void*)ss3);
  printf(" = %d\n", TSDDA_compare((void*)ss2, (void*)ss3));

  // Delete
  printf("\nDelete:\n-------\n");
  if (!TSDDA_delete((void*)ss1)) {
    printf("ss1 was deleted successfully\n");
  }

  if (!TSDDA_delete((void*)ss2)) {
    printf("ss2 was deleted successfully\n");
  }

  if (!TSDDA_delete((void*)ss3)) {
    printf("ss3 was deleted successfully\n");
  }

  return 0;
}