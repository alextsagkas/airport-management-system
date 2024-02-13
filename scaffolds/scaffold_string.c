/*
author: Alexadros Tsagkaropoulos

References:

 - Introduction to Algorithms, Third Edition
 by Thomas H. Cormen, Charles E. Leiserson,
 Ronald L. Rivest and Clifford Stein.
 - Programming Language Principles and Programming Techniques notes
 from M.Sc. in Control and Computing taught by Ioannis Kotronis.
 - The Practice of Computer Programming, Second Edition
 by Brian W. Kernighan and Rob Pike.
*/

#include "../string_module/string.h"
#include <stdio.h>

int main() {
  char str1[6] = "hello";
  char str2[6] = "world";
  char str3[6] = "hello";

  // Create Key
  key_stringp string_key1 = string_create_key(str1);
  key_stringp string_key2 = string_create_key(str2);
  key_stringp string_key3 = string_create_key(str3);

  // Print
  printf("\nprint:\n--------\n");
  string_print("string_key1: ", (void*)string_key1);
  printf("\n");
  string_print("string_key2: ", (void*)string_key2);
  printf("\n");
  string_print("string_key3: ", (void*)string_key3);
  printf("\n");

  // Compare
  printf("\ncompare:\n-----------\n");
  string_print("", (void*)string_key1);
  printf(" cmp ");
  string_print("", (void*)string_key2);
  printf(" = %d\n", string_compare((void*)string_key1, (void*)string_key2));

  string_print("", (void*)string_key2);
  printf(" cmp ");
  string_print("", (void*)string_key1);
  printf(" = %d\n", string_compare((void*)string_key2, (void*)string_key1));

  string_print("", (void*)string_key1);
  printf(" cmp ");
  string_print("", (void*)string_key3);
  printf(" = %d\n", string_compare((void*)string_key1, (void*)string_key3));

  // Delete
  printf("\nDelete:\n-------\n");
  if (!string_delete_key((void*)string_key1)) {
    printf("string_key1 was deleted successfully\n");
  }

  if (!string_delete_key((void*)string_key2)) {
    printf("string_key2 was deleted successfully\n");
  }

  if (!string_delete_key((void*)string_key3)) {
    printf("string_key3 was deleted successfully\n");
  }

  return 0;
}
