#include "../ebst_module/tebst.h"
#include <stdio.h>

int main() {

  // Create
  TBSTElement* ss1 = TEBST_create(0, 10);
  TBSTElement* ss2 = TEBST_create(1, 11);
  TBSTElement* ss3 = TEBST_create(0, 12);

  // Print
  printf("\nprint:\n--------\n");
  TEBST_print("ss1: ", (void*)ss1);
  printf("\n");
  TEBST_print("ss2: ", (void*)ss2);
  printf("\n");
  TEBST_print("ss3: ", (void*)ss3);
  printf("\n");

  // Compare
  printf("\ncompare:\n------------\n");
  TEBST_print("", (void*)ss1);
  printf(" cmp ");
  TEBST_print("", (void*)ss2);
  printf(" = %d\n", TEBST_compare((void*)ss1, (void*)ss2));

  TEBST_print("", (void*)ss1);
  printf(" cmp ");
  TEBST_print("", (void*)ss3);
  printf(" = %d\n", TEBST_compare((void*)ss1, (void*)ss3));

  TEBST_print("", (void*)ss2);
  printf(" cmp ");
  TEBST_print("", (void*)ss3);
  printf(" = %d\n", TEBST_compare((void*)ss2, (void*)ss3));

  // Delete
  printf("\nDelete:\n-------\n");
  if (!TEBST_delete((void*)ss1)) {
    printf("ss1 was deleted successfully\n");
  }

  if (!TEBST_delete((void*)ss2)) {
    printf("ss2 was deleted successfully\n");
  }

  if (!TEBST_delete((void*)ss3)) {
    printf("ss3 was deleted successfully\n");
  }

  return 0;
}