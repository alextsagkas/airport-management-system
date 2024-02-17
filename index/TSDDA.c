#include "TEBST.h"
#include <assert.h>
#include <stdlib.h>

TBSTElement* TEBST_create(keyType key, int arrayIndex) {
  TBSTElement* node = (TBSTElement*)malloc(sizeof(TBSTElement));
  assert(node != NULL);

  node->key = key;
  node->arrayIndex = arrayIndex;

  return node;
}

int TEBST_delete(void* node) {
  assert(node != NULL);

  free(node);
  node = NULL;

  return 0;
}

void TEBST_fprint(FILE* out, const void* struct1) {
  assert(out != NULL);

  fprintf(out,
          "%d;%d;\n",
          ((TBSTElement*)struct1)->key,
          ((TBSTElement*)struct1)->arrayIndex);
}

void TEBST_print(const char* term_color, const void* struct1) {
  printf("%s%d", term_color, ((TBSTElement*)struct1)->key);
}

int TEBST_compare(const void* s1, const void* s2) {
  TBSTElement* ss1 = (TBSTElement*)s1;
  TBSTElement* ss2 = (TBSTElement*)s2;

  if (ss1->key < ss2->key) {
    return -1;
  } else if (ss1->key == ss2->key) {
    return 0;
  } else {
    return 1;
  }
}
