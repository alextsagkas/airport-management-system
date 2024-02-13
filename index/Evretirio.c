#include "Evretirio.h"

#include "../rbt_module/rbt.h" /* h Ylopoihsh sas toy R/B */

struct EvrNode {
  TStoixeiouEvr* DataArray; /* array of size MaxSize */
  int Index;                /* index of first available element in array */
  Treep TreeRoot;           /* Root of DDA */
} EvrNode;

EvrPtr Evr_construct(int MaxSize) {}

int Evr_insert(EvrPtr E, TStoixeiouEvr Data) {}

int Evr_search(EvrPtr E, keyType key, int InOut, int* found) {}

int Evr_printAll(EvrPtr E, FILE* out, int* counter) {}

int Evr_destruct(EvrPtr* E) {}