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

#ifndef key
#define key

//! generic

typedef struct key_t *key_tp;

int create_key(void *data);
void print_data(key_tp struct1, void (*printer)(const void *));
int are_equal(key_tp struct1,
              key_tp struct2,
              int (*equalizer)(const void *, const void *));
int is_greater(key_tp struct1,
               key_tp struct2,
               int (*comparator)(const void *, const void *));
int is_smaller(key_tp struct1,
               key_tp struct2,
               int (*comparator)(const void *, const void *));
int assign(key_tp struct1,
           key_tp struct2,
           int (*assignment)(const void *, const void *));

//! int

typedef struct key_int *key_intp;

key_intp create_int_node(int data);
void int_printer(const void *struct1);
int int_equalizer(const void *struct1, const void *struct2);
int int_comparator(const void *struct1, const void *struct2);
int int_assignment(const void *struct1, const void *struct2);

#endif