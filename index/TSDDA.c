#include "TSDDA.h"
#include <assert.h>
#include <stdlib.h>

// ------------------------------ My Functions ------------------------------ //

TStoixeiouDDA* TSDDA_create(keyType key, int arrayIndex) {
  TStoixeiouDDA* node = (TStoixeiouDDA*)malloc(sizeof(TStoixeiouDDA));
  assert(node != NULL);

  node->key = key;
  node->arrayIndex = arrayIndex;

  return node;
}

int TSDDA_delete(void* node) {
  assert(node != NULL);

  free(node);
  node = NULL;

  return 0;
}

// TODO: make it return in all paths
void TSDDA_print(const char* term_color, const void* struct1) {
  printf("%s%d", term_color, ((TStoixeiouDDA*)struct1)->key);
}

int TSDDA_compare(const void* s1, const void* s2) {
  TStoixeiouDDA* ss1 = (TStoixeiouDDA*)s1;
  TStoixeiouDDA* ss2 = (TStoixeiouDDA*)s2;

  if (ss1->key < ss2->key) {
    return -1;
  } else if (ss1->key == ss2->key) {
    return 0;
  } else if (ss1->key > ss2->key) {
    return 1;
  }
}

// ------------------------------------------------------------------------- //

// TODO: delete the following if not needed
int TSDDA_setValue(TStoixeiouDDA* target, TStoixeiouDDA source) {
  target->key = source.key;
  target->arrayIndex = source.arrayIndex;

  return 0;
}

int TSDDA_setKey(keyType* key, keyType Val) {
  *key = Val;

  return 0;
}

int TSDDA_setIndex(int* Index, int Val) {
  *Index = Val;

  return 0;
}

int TSDDA_equal(TStoixeiouDDA s1, TStoixeiouDDA s2) {
  return (s1.key == s2.key);
}

int TSDDA_smaller(TStoixeiouDDA s1, TStoixeiouDDA s2) {
  return (s1.key < s2.key);
}

int TSDDA_greater(TStoixeiouDDA s1, TStoixeiouDDA s2) {
  return (s1.key > s2.key);
}

/* The Following are already Implemented using Above */
int TSDDA_smaller_or_equal(TStoixeiouDDA s1, TStoixeiouDDA s2) {
  return TSDDA_smaller(s1, s2) || TSDDA_equal(s1, s2);
}

int TSDDA_greater_or_equal(TStoixeiouDDA s1, TStoixeiouDDA s2) {
  return TSDDA_greater(s1, s2) || TSDDA_equal(s1, s2);
}

int TSDDA_not_equal(TStoixeiouDDA s1, TStoixeiouDDA s2) {
  return !TSDDA_equal(s1, s2);
}
