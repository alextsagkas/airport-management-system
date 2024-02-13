#ifndef __Evr__
#define __Evr__

#include "TSDDA.h"
#include "TSEvr.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct EvrNode* EvrPtr;

EvrPtr Evr_construct(int MaxSize);

int Evr_destruct(EvrPtr* E);

int Evr_insert(EvrPtr E, TStoixeiouEvr Data);

int Evr_search(EvrPtr E, keyType key, int InOut, int* found);

int Evr_printAll(EvrPtr E, FILE* out, int* counter);

#endif
