#ifndef __TSDDA__
#define __TSDDA__

#include <stdio.h>

typedef int keyType; /* integer key for airport */

typedef struct KeyIndex {
  keyType key;
  int arrayIndex;
} TStoixeiouDDA;

int TSDDA_setValue(TStoixeiouDDA* target, TStoixeiouDDA source);

int TSDDA_setKey(keyType* key, keyType Val);

int TSDDA_setIndex(int* Index, int Val);

/* Main functions for insertion/deletion/searching in DDA */
int TSDDA_equal(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_smaller(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_greater(TStoixeiouDDA, TStoixeiouDDA);

/* Supplementary comparison functions */
int TSDDA_smaller_or_equal(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_greater_or_equal(TStoixeiouDDA, TStoixeiouDDA);
int TSDDA_not_equal(TStoixeiouDDA, TStoixeiouDDA);

#endif
