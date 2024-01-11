#include "string.h"
#include <stdio.h>

int main() {
  char str1[6] = "hello";
  char str2[6] = "world";
  char str3[6] = "hello";

  // Create Key
  key_stringp string_key1 = create_string_key(str1);
  key_stringp string_key2 = create_string_key(str2);
  key_stringp string_key3 = create_string_key(str3);

  // Printer
  printf("\nPrinter:\n--------\n");
  string_printer("string_key1: ", (void*)string_key1);
  printf("\n");
  string_printer("string_key2: ", (void*)string_key2);
  printf("\n");
  string_printer("string_key3: ", (void*)string_key3);
  printf("\n");

  // Comparator
  printf("\nComparator:\n-----------\n");
  string_printer("", (void*)string_key1);
  printf(" cmp ");
  string_printer("", (void*)string_key2);
  printf(" = %d\n", string_comparator((void*)string_key1, (void*)string_key2));

  string_printer("", (void*)string_key2);
  printf(" cmp ");
  string_printer("", (void*)string_key1);
  printf(" = %d\n", string_comparator((void*)string_key2, (void*)string_key1));

  string_printer("", (void*)string_key1);
  printf(" cmp ");
  string_printer("", (void*)string_key3);
  printf(" = %d\n", string_comparator((void*)string_key1, (void*)string_key3));

  // Delete
  printf("\nDelete:\n-------\n");
  if (!delete_string_key((void*)string_key1)) {
    printf("string_key1 was deleted successfully\n");
  }

  if (!delete_string_key((void*)string_key2)) {
    printf("string_key2 was deleted successfully\n");
  }

  if (!delete_string_key((void*)string_key3)) {
    printf("string_key3 was deleted successfully\n");
  }

  return 0;
}