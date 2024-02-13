#include "TSDDA.h"

int TSDDA_setValue(TStoixeiouDDA* target, TStoixeiouDDA source) {
  target->arrayIndex = source.arrayIndex;
  target->key = source.key;

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
