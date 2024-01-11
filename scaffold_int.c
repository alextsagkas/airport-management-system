#include "int.h"
#include <stdio.h>

int main() {
  key_intp int_key1 = create_int_key(1);
  key_intp int_key2 = create_int_key(2);
  key_intp int_key3 = create_int_key(3);
  // Printer
  printf("\nPrinter:\n--------\n");
  int_printer("int_key1: ", (void*)int_key1);
  printf("\n");
  int_printer("int_key2: ", (void*)int_key2);
  printf("\n");
  int_printer("int_key3: ", (void*)int_key3);
  printf("\n");

  // Comparator
  printf("\nComparator:\n-----------\n");
  int_printer("", (void*)int_key1);
  printf(" cmp ");
  int_printer("", (void*)int_key2);
  printf(" = %d\n", int_comparator((void*)int_key1, (void*)int_key2));

  int_printer("", (void*)int_key2);
  printf(" cmp ");
  int_printer("", (void*)int_key1);
  printf(" = %d\n", int_comparator((void*)int_key2, (void*)int_key1));

  int_printer("", (void*)int_key1);
  printf(" cmp ");
  int_printer("", (void*)int_key3);
  printf(" = %d\n", int_comparator((void*)int_key1, (void*)int_key3));

  // Delete
  printf("\nDelete:\n-------\n");
  if (!delete_int_key((void*)int_key1)) {
    printf("int_key1 was deleted successfully\n");
  }

  if (!delete_int_key((void*)int_key2)) {
    printf("int_key2 was deleted successfully\n");
  }

  if (!delete_int_key((void*)int_key3)) {
    printf("int_key3 was deleted successfully\n");
  }

  return 0;
}