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

#ifndef STRING
#define STRING

typedef struct key_string* key_stringp;

/*
Description: Creates a string struct with its data denoted by function's
parameter. The data is copied to the struct's data with strdup.

Parameters:
  - data (char*): The data of the struct.

Return values:
  - key_stringp: The pointer to the struct created.

Asserts:
  - malloc returns successfully.
*/
key_stringp create_string_key(char* data);

/*
Description: Deletes the struct denoted by function's parameter.

Parameters:
  - struct1 (void*): The struct to be deleted.

Return values:
  - 0: Success.

Asserts:
  - node != NULL.
  - node->data != NULL.
*/
int delete_string_key(void* struct1);

/*
Description: Prints the data of the struct with the terminal color that
the first parameter of the function indicates.

Parameters:
  - term_color (const char *): The terminal color.
  - struct1 (const void *): The struct to be printed.
*/
void string_printer(const char* term_color, const void* struct1);

/*
Description: Compares the first and second struct's data in alphabetical
order.

Parameters:
  - struct1 (const void *): The first struct.
  - struct2 (const void *): The second struct.

Return values:
  - 0: The data in the two structs are equal.
  - 1: The data in the first struct is greater than the data in the second
       struct.
  - -1: The data in the first struct is smaller than the data in the second
       struct.
*/
int string_comparator(const void* struct1, const void* struct2);

#endif