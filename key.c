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

#include "key.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct key_t *key_tp;

struct key_t {
  void *data;
};

key_tp create_key(void *data) {
  key_tp struct1 = (key_tp)malloc(sizeof(struct key_t));
  assert(struct1 != NULL);

  struct1->data = data;

  return struct1;
}

void print_data(char *term_color,
                key_tp struct1,
                void (*printer)(const char *, const void *)) {
  (*printer)(term_color, (void *)struct1->data);
}

int are_equal(key_tp struct1,
              key_tp struct2,
              int (*equalizer)(const void *, const void *)) {
  return (*equalizer)((void *)struct1->data, (void *)struct2->data);
}

int is_greater(key_tp struct1,
               key_tp struct2,
               int (*comparator_greater)(const void *, const void *)) {
  return (*comparator_greater)((void *)struct1->data, (void *)struct2->data);
}

int is_smaller(key_tp struct1,
               key_tp struct2,
               int (*comparator_smaller)(const void *, const void *)) {
  return (*comparator_smaller)((void *)struct1->data, (void *)struct2->data);
}
