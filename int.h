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

#ifndef INT
#define INT

typedef struct key_int *key_intp;

/*
Description: Creates a struct with its data denoted by function's parameter.

Parameters:
  - data (int): The data of the struct.

Return values:
    - key_intp: The pointer to the struct created.

Asserts:
    - malloc returns successfully.
*/
key_intp create_int_node(int data);

/*
Description: Prints the data of the struct with the terminal color that
the first parameter of the function indicates.

Parameters:
  - term_color (const char *): The terminal color.
  - struct1 (const void *): The struct to be printed.
*/
void int_printer(const char *term_color, const void *struct1);

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
int int_equalizer(const void *struct1, const void *struct2);

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
int int_comparator_greater(const void *struct1, const void *struct2);

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
int int_comparator_smaller(const void *struct1, const void *struct2);

#endif