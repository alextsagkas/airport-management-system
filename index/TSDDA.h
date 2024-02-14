#ifndef __TSDDA__
#define __TSDDA__

#include <stdio.h>

typedef int keyType; /* integer key for airport */

typedef struct KeyIndex {
  keyType key;
  int arrayIndex;
} TStoixeiouDDA;

/*
Description: This function initializes the value of the target struct with the
fields of the source struct.

Parameters:
  - target (TStoixeiouDDA*): The struct that will be initialized.
  - source (TStoixeiouDDA): The struct that will be used to initialize the
  target.

Return value:
  - 0 : The function executed successfully.
*/
int TSDDA_setValue(TStoixeiouDDA* target, TStoixeiouDDA source);

/*
Description: This function initializes the value of key with the value of Val.

Parameters:
  - key (keyType*): The key that will be initialized.
  - Val (keyType): The value that will be used to initialize the key.

Return value:
  - 0 : The function executed successfully.
*/
int TSDDA_setKey(keyType* key, keyType Val);

/*
Description: This function initializes the value of Index with the value of Val.

Parameters:
  - Index (int*): The index that will be initialized.
  - Val (int): The value that will be used to initialize the index.

Return value:
  - 0 : The function executed successfully.
*/
int TSDDA_setIndex(int* Index, int Val);

/*
Description: This function compares the key field of the two structs. The output
is the following:
  - -1 : The key field of the first struct is smaller than the key field of the
    second struct.
  - 0 : The key field of the first struct is equal to the key field of the
    second struct.
  - 1 : The key field of the first struct is greater than the key field of the
    second struct.

Parameters:
  - TStoixeiouDDA: The first struct that will be compared.
  - TStoixeiouDDA: The second struct that will be compared.

Return values:
  - -1 : The key field of the first struct is smaller than the key field of the
    second struct.
  - 0 : The key field of the first struct is equal to the key field of the
    second struct.
  - 1 : The key field of the first struct is greater than the key field of the
    second struct.
*/
int TSDDA_compare(TStoixeiouDDA, TStoixeiouDDA);

// /* Main functions for insertion/deletion/searching in DDA */

// /*
// Description: Checks if the key field of the two structs are equal. If they
// are, the function returns 1, otherwise it returns 0.

// Parameters:
//   - TStoixeiouDDA: The first struct that will be compared.
//   - TStoixeiouDDA: The second struct that will be compared.

// Return values:
//   - 1 : The fields of the two structs are equal.
//   - 0 : The fields of the two structs are not equal.
// */
// int TSDDA_equal(TStoixeiouDDA, TStoixeiouDDA);

// /*
// Description: Checks if the key field of the first struct is smaller than the
// key field of the second struct. If it is, the function returns 1, otherwise
// it returns 0.

// Parameters:
//   - TStoixeiouDDA: The first struct that will be compared.
//   - TStoixeiouDDA: The second struct that will be compared.

// Return values:
//   - 1 : The key field of the first struct is smaller than the key field of
//   the second struct.
//   - 0 : The key field of the first struct is not smaller than the key field
//   of the second struct.
// */
// int TSDDA_smaller(TStoixeiouDDA, TStoixeiouDDA);

// /*
// Description: Checks if the key field of the first struct is greater than the
// key field of the second struct. If it is, the function returns 1, otherwise
// it returns 0.

// Parameters:
//   - TStoixeiouDDA: The first struct that will be compared.
//   - TStoixeiouDDA: The second struct that will be compared.

// Return values:
//   - 1 : The key field of the first struct is greater than the key field of
//   the second struct.
//   - 0 : The key field of the first struct is not greater than the key field
//   of the second struct.
// */
// int TSDDA_greater(TStoixeiouDDA, TStoixeiouDDA);

// /* Supplementary comparison functions */

// /*
// Description: Checks if the key field of the first struct is smaller or equal
// to the key field of the second struct. If it is, the function returns 1,
// otherwise it returns 0.

// Parameters:
//   - TStoixeiouDDA: The first struct that will be compared.
//   - TStoixeiouDDA: The second struct that will be compared.

// Return values:
//   - 1 : The key field of the first struct is smaller or equal to the key
//   field of the second struct.
//   - 0 : The key field of the first struct is not smaller or equal to the key
//   field of the second struct.
// */
// int TSDDA_smaller_or_equal(TStoixeiouDDA, TStoixeiouDDA);

// /*
// Description: Checks if the key field of the first struct is greater or equal
// to the key field of the second struct. If it is, the function returns 1,
// otherwise it returns 0.

// Parameters:
//   - TStoixeiouDDA: The first struct that will be compared.
//   - TStoixeiouDDA: The second struct that will be compared.

// Return values:
//   - 1 : The key field of the first struct is greater or equal to the key
//   field of the second struct.
//   - 0 : The key field of the first struct is not greater or equal to the key
//   field of the second struct.
// */
// int TSDDA_greater_or_equal(TStoixeiouDDA, TStoixeiouDDA);

// /*
// Description: Checks if the key field of the first struct is not equal to the
// key field of the second struct. If it is, the function returns 1, otherwise
// it returns 0.

// Parameters:
//   - TStoixeiouDDA: The first struct that will be compared.
//   - TStoixeiouDDA: The second struct that will be compared.

// Return values:
//   - 1 : The key field of the first struct is not equal to the key field of
//   the second struct.
//   - 0 : The key field of the first struct is equal to the key field of the
//   second struct.
// */
// int TSDDA_not_equal(TStoixeiouDDA, TStoixeiouDDA);

#endif
