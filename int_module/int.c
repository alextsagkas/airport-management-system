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

#include "int.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct key_int {
  int data;
};

key_intp int_create_key(int data) {
  key_intp node = (key_intp)malloc(sizeof(struct key_int));
  assert(node != NULL);

  node->data = data;

  return node;
}

int int_delete_key(void* node) {
  assert(node != NULL);

  free(node);
  node = NULL;

  return 0;
}

void int_print(const char* term_color, const void* struct1) {
  printf("%s%d", term_color, ((key_intp)struct1)->data);
}

int int_compare(const void* struct1, const void* struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  if (((key_intp)struct1)->data == ((key_intp)struct2)->data) {
    return 0;
  } else if (((key_intp)struct1)->data > ((key_intp)struct2)->data) {
    return 1;
  } else {
    return -1;
  }
}
