#ifndef __TSDDA__
#define __TSDDA__

#include <stdio.h>

typedef int keyType; /* integer key for airport */

typedef struct KeyIndex {
  keyType key;
  int arrayIndex;
} TStoixeiouDDA;

/*
Description: Creates a struct with its data denoted by function's parameter.

Parameters:
  - key (keyType): The key of the struct.
  - arrayIndex (int): The array index of the struct.

Return values:
  - keyIndex*: The pointer to the struct created.

Asserts:
  - malloc returns successfully.
*/
TStoixeiouDDA* TSDDA_create(keyType key, int arrayIndex);

/*
Description: Deletes the struct denoted by function's parameter.

Parameters:
  - node (void*): The struct to be deleted.

Return values:
  - 0: Success.

Asserts:
  - node != NULL.
*/
int TSDDA_delete(void* node);

/*
Description: Prints the data of the struct with the terminal color that
the first parameter of the function indicates.

Parameters:
  - term_color (const char *): The terminal color.
  - struct1 (const void *): The struct to be printed.
*/
void TSDDA_print(const char* term_color, const void* struct1);

/*
Description: Prints the data of the struct to the file denoted by the
function's parameter. The form of the printed output is: airportID;arrayIndex;

Parameters:
  - out (FILE*): The file to be printed.
  - struct1 (const void*): The struct to be printed.

Asserts:
  - out != NULL.
*/
void TSDDA_fprint(FILE* out, const void* struct1);

/*
Description: Compares the first and second struct's data. The comparison is
based on the key field of the structs. The return values follow the rules:
  - -1: The key in the first struct is smaller than the key in the second
        struct.
  - 0: The key in the two structs are equal.
  - 1: The key in the first struct is greater than the key in the second
       struct.

Parameters:
  - s1 (const void*): The first struct.
  - s2 (const void*): The second struct.

Return values:
  - -1: The key in the first struct is smaller than the key in the second
        struct.
  - 0: The key in the two structs are equal.
  - 1: The key in the first struct is greater than the key in the second
       struct.
*/
int TSDDA_compare(const void* s1, const void* s2);

#endif