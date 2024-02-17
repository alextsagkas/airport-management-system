#include "TSDDA.h"
#include <assert.h>
#include <stdlib.h>

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

void TSDDA_fprint(FILE* out, const void* struct1) {
  assert(out != NULL);

  fprintf(out,
          "%d;%d;\n",
          ((TStoixeiouDDA*)struct1)->key,
          ((TStoixeiouDDA*)struct1)->arrayIndex);
}

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
  } else {
    return 1;
  }
}
