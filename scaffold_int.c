#include "int.h"
#include <stdio.h>

int main() {
  key_intp int_key1 = int_create_key(1);
  key_intp int_key2 = int_create_key(2);
  key_intp int_key3 = int_create_key(3);

  // Print
  printf("\nprint:\n--------\n");
  int_print("int_key1: ", (void*)int_key1);
  printf("\n");
  int_print("int_key2: ", (void*)int_key2);
  printf("\n");
  int_print("int_key3: ", (void*)int_key3);
  printf("\n");

  // Compare
  printf("\ncompare:\n-----------\n");
  int_print("", (void*)int_key1);
  printf(" cmp ");
  int_print("", (void*)int_key2);
  printf(" = %d\n", int_compare((void*)int_key1, (void*)int_key2));

  int_print("", (void*)int_key2);
  printf(" cmp ");
  int_print("", (void*)int_key1);
  printf(" = %d\n", int_compare((void*)int_key2, (void*)int_key1));

  int_print("", (void*)int_key1);
  printf(" cmp ");
  int_print("", (void*)int_key3);
  printf(" = %d\n", int_compare((void*)int_key1, (void*)int_key3));

  // Delete
  printf("\nDelete:\n-------\n");
  if (!int_delete_key((void*)int_key1)) {
    printf("int_key1 was deleted successfully\n");
  }

  if (!int_delete_key((void*)int_key2)) {
    printf("int_key2 was deleted successfully\n");
  }

  if (!int_delete_key((void*)int_key3)) {
    printf("int_key3 was deleted successfully\n");
  }

  return 0;
}
