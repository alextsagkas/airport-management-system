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

/*
Description: Creates a struct with its data denoted by function's parameter.

Parameters:
  - data (void *): The data of the struct.

Return values:
  - key_tp: The pointer to the struct created.

Asserts:
  - malloc returns successfully.
*/
key_tp create_key(void *data) {
  key_tp struct1 = (key_tp)malloc(sizeof(struct key_t));
  assert(struct1 != NULL);

  struct1->data = data;

  return struct1;
}

/*
Description: Prints the data of the struct.

Parameters:
  - struct1 (key_tp): The struct to be printed.
  - printer (void (*)(const void *)): The pointer to the function that prints
    the data of the struct.
*/
void print_data(key_tp struct1, void (*printer)(const void *)) {
  (*printer)((void *)struct1->data);
}
/*
Description: Asserts that data in struct1 and struct2 structs are equal.

Parameters:
  - struct1 (key_tp): The first struct.
  - struct2 (key_tp): The second struct.
  - equalizer (int (*)(const void *, const void *)): The pointer to the
    function that compares the data of the two structs.

Return values:
    - 1: The data in the two structs are equal.
    - 0: The data in the two structs are not equal.
*/
int are_equal(key_tp struct1,
              key_tp struct2,
              int (*equalizer)(const void *, const void *)) {
  return (*equalizer)((void *)struct1->data, (void *)struct2->data);
}

/*
Description: Asserts that data in struct1 is greater than data in struct2.

Parameters:
  - struct1 (key_tp): The first struct.
  - struct2 (key_tp): The second struct.
  - comparator (int (*)(const void *, const void *)): The pointer to the
    function that compares the data of the two structs.

Return values:
    - 1: The data in the first struct is greater than the data in the second
         struct.
    - 0: The data in the first struct is not greater than the data in the
         second struct.
*/
int is_greater(key_tp struct1,
               key_tp struct2,
               int (*comparator)(const void *, const void *)) {
  return (*comparator)((void *)struct1->data, (void *)struct2->data);
}

/*
Description: Asserts that data in struct1 is smaller than data in struct2.

Parameters:
  - struct1 (key_tp): The first struct.
  - struct2 (key_tp): The second struct.
  - comparator (int (*)(const void *, const void *)): The pointer to the
    function that compares the data of the two structs.

Return values:
    - 1: The data in the first struct is smaller than the data in the second
         struct.
    - 0: The data in the first struct is not smaller than the data in the
         second struct.
*/
int is_smaller(key_tp struct1,
               key_tp struct2,
               int (*comparator)(const void *, const void *)) {
  return !(*comparator)((void *)struct1->data, (void *)struct2->data);
}

/*
Description: Asserts that the two structs have the same data inside.

Parameters:
  - struct1 (key_tp): The first struct.
  - struct2 (key_tp): The second struct.
  - assignment (void (*)(const void *, const void *)): The pointer to the
    function that assigns the data of the second struct to the data of the
    first struct.

Return values:
    - 0: Success.
    - 1: Failure.
*/
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

/*
Description: Creates a struct with its data denoted by function's parameter.

Parameters:
  - data (int): The data of the struct.

Return values:
    - key_intp: The pointer to the struct created.

Asserts:
    - malloc returns successfully.
*/
key_intp create_int_node(int data) {
  key_intp node = (key_intp)malloc(sizeof(struct key_int));
  assert(node != NULL);

  node->data = data;

  return node;
}

/*
Description: Prints the data of the struct.

Parameters:
  - struct1 (const void *): The struct to be printed.
*/
void int_printer(const void *struct1) {
  printf("%d", ((key_intp)struct1)->data);
}

/*
Description: Asserts that data in struct1 and struct2 structs are equal.

Parameters:
  - struct1 (const void *): The first struct.
  - struct2 (const void *): The second struct.

Return values:
    - 1: The data in the two structs are equal.
    - 0: The data in the two structs are not equal.

Asserts:
    - struct1 != NULL.
    - struct2 != NULL.
*/
int int_equalizer(const void *struct1, const void *struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  if (((key_intp)struct1)->data == ((key_intp)struct2)->data) {
    return 1;
  } else {
    return 0;
  }
}

/*
Description: Asserts that data in struct1 is greater than data in struct2.

Parameters:
  - struct1 (const void *): The first struct.
  - struct2 (const void *): The second struct.

Return values:
    - 1: The data in the first struct is greater than the data in the second
         struct.
    - 0: The data in the first struct is not greater than the data in the
         second struct.

Asserts:
    - struct1 != NULL.
    - struct2 != NULL.
*/
int int_comparator(const void *struct1, const void *struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  if (((key_intp)struct1)->data > ((key_intp)struct2)->data) {
    return 1;
  } else {
    return 0;
  }
}

/*
Description: Asserts that data in struct1 is smaller than data in struct2.

Parameters:
  - struct1 (const void *): The first struct.
  - struct2 (const void *): The second struct.

Return values:
    - 1: The data in the first struct is smaller than the data in the second
         struct.
    - 0: The data in the first struct is not smaller than the data in the
         second struct.

Asserts:
    - struct1 != NULL.
    - struct2 != NULL.
*/
int int_assignment(const void *struct1, const void *struct2) {
  assert(struct1 != NULL);
  assert(struct2 != NULL);

  ((key_intp)struct1)->data = ((key_intp)struct2)->data;

  return 0;
}