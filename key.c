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

//! generic

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

int assign(key_tp struct1,
           key_tp struct2,
           int (*assignment)(const void *, const void *)) {
  return (*assignment)((void *)struct1->data, (void *)struct2->data);
}

//! int

typedef struct key_int *key_intp;

struct key_int {
  int data;
};

key_intp create_int_node(int data) {
  key_intp node = (key_intp)malloc(sizeof(struct key_int));
  assert(node != NULL);

  node->data = data;

  return node;
}

void int_printer(const char *term_color, const void *struct1) {
  printf("%s%d", term_color, ((key_intp)struct1)->data);
}

int int_equalizer(const void *struct1, const void *struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  if (((key_intp)struct1)->data == ((key_intp)struct2)->data) {
    return 1;
  } else {
    return 0;
  }
}

int int_comparator_greater(const void *struct1, const void *struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  if (((key_intp)struct1)->data > ((key_intp)struct2)->data) {
    return 1;
  } else {
    return 0;
  }
}

int int_comparator_smaller(const void *struct1, const void *struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  if (((key_intp)struct1)->data < ((key_intp)struct2)->data) {
    return 1;
  } else {
    return 0;
  }
}

int int_assignment(const void *struct1, const void *struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  ((key_intp)struct1)->data = ((key_intp)struct2)->data;

  return 0;
}