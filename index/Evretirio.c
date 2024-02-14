#include "Evretirio.h"
#include <assert.h>

#include "../rbt_module/rbt.h" /* h Ylopoihsh sas toy R/B */

struct EvrNode {
  TStoixeiouEvr* DataArray; /* array of size MaxSize */
  int Index;                /* index of first available element in array */
  Treep TreeRoot;           /* Root of DDA */
} EvrNode;

EvrPtr Evr_construct(int MaxSize) {
  EvrPtr E = (EvrPtr)malloc(sizeof(struct EvrNode));
  assert(E != NULL);

  E->DataArray = (TStoixeiouEvr*)malloc(MaxSize * sizeof(TStoixeiouEvr));
  assert(E->DataArray != NULL);

  // Start at 0-th position to add TStoixeiouEvr in the DataArray
  E->Index = 0;

  E->TreeRoot = RBT_create_tree();

  return E;
}

int Evr_insert(EvrPtr E, TStoixeiouEvr Data) {
  E->DataArray[E->Index] = Data;
  E->Index++;

  TStoixeiouDDA DDAData = {Data.airportID, E->Index - 1};
  if (RBT_insert((E->TreeRoot), (void*)&DDAData, TSDDA_compare) != 0) {
    return -1;
  }

  return 0;
}

// int Evr_search(EvrPtr E, keyType key, int InOut, int* found) {}

// int Evr_printAll(EvrPtr E, FILE* out, int* counter) {}

int Evr_destruct(EvrPtr* E) {
  free((*E)->DataArray);
  (*E)->DataArray = NULL;

  // TODO: free all of RBT's nodes
  RBT_delete_tree((*E)->TreeRoot);

  free(*E);
  *E = NULL;

  return 0;
}
