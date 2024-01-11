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

#include "string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct key_string {
  char* data;
};

key_stringp create_string_key(char* data) {
  key_stringp node = (key_stringp)malloc(sizeof(struct key_string));
  assert(node != NULL);

  // +1 to count the null character \0
  char* data_copy = (char*)malloc(sizeof(char) * strlen(data) + 1);
  assert(data_copy != NULL);

  node->data = strdup(data);

  return node;
}

int delete_string_key(void* struct1) {
  key_stringp struct1_casted = (key_stringp)struct1;

  assert(struct1_casted != NULL);
  assert(struct1_casted->data != NULL);

  free(struct1_casted->data);
  free(struct1_casted);

  return 0;
}

void string_printer(const char* term_color, const void* struct1) {
  printf("%s%s", term_color, ((key_stringp)struct1)->data);
}

int string_comparator(const void* struct1, const void* struct2) {
  key_stringp struct1_casted = (key_stringp)struct1;
  assert(struct1_casted != NULL);
  assert(struct1_casted->data != NULL);

  key_stringp struct2_casted = (key_stringp)struct2;
  assert(struct2_casted != NULL);
  assert(struct2_casted->data != NULL);

  int cmp = strcmp(struct1_casted->data, struct2_casted->data);

  if (cmp > 0) {
    return 1;
  } else if (cmp < 0) {
    return -1;
  } else {
    return 0;
  }
}
