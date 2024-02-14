#ifndef __Evr__
#define __Evr__

#include "TSDDA.h"
#include "TSEvr.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct EvrNode* EvrPtr;

/*
Description: Construct a new EvrPtr. Its fields hold the following information:
    - The DataArray is an array of TStoixeiouEvr of size MaxSize.
    - The Index is initialized to 0, which is the first available position in
      the DataArray.
    - The TreeRoot is the root of the DDA.

Parameters:
    - Maxsize (int): The size of the DataArray.

Return values:
    - EvrPtr: A pointer to the newly constructed EvrPtr.

Asserts:
    - The EvrPtr is not NULL.
    - The DataArray is not NULL.
    - The TreeRoot is not NULL.
*/
EvrPtr Evr_construct(int MaxSize);

/*
Description: Destroy an EvrNode. The function frees the memory allocated for the
DataArray and the RBT's nodes. Ir also frees the memory allocated for the
EvrPtr.

Parameters:
    - E (EvrPtr*): A pointer to the EvrPtr.

Return values:
    - 0 : if the function was successful.
*/
int Evr_destruct(EvrPtr* E);

/*
Description: Insert a new TStoixeiouEvr in the EvrPtr's DataArray and RBT.

Parameters:
    - E (EvrPtr): A pointer to the EvrPtr.
    - Data (TStoixeiouEvr): The TStoixeiouEvr to be inserted.

Return values:
    - 0 : if the function was successful.
    - -1: if the insertion in the RBT was not successful.
*/
int Evr_insert(EvrPtr E, TStoixeiouEvr Data);

// int Evr_search(EvrPtr E, keyType key, int InOut, int* found);

// int Evr_printAll(EvrPtr E, FILE* out, int* counter);

#endif
