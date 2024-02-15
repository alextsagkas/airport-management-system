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

/*
Description: Search for a TStoixeiouDDA in the EvrPtr's RBT with corresponding
key to the parameter passed in the function. The function sets the value of the
parameter found to 1 if the key was found in the RBT, otherwise it sets it to 0.
Also, if the key is found in the RBT, the function increments the arrivals or
departures of the corresponding TStoixeiouEvr in the DataArray, when the InOut
is 0 or 1, respectively.

Parameters:
    - E (EvrPtr): A pointer to the EvrPtr.
    - key (keyType): The key to be searched in the RBT.
    - InOut (int): The value of the InOut parameter is 0 if the search is for
      arrivals, and 1 if the search is for departures.
    - found (int*): A pointer to an integer that is set to 1 if the key was
      found in the RBT, otherwise it is set to 0.

Return values:
    - -2: if the InOut parameter is not 0 or 1.
    - -1: if the key was not found in the RBT.
    - 0: if the function was successful.
*/
int Evr_search(EvrPtr E, keyType key, int InOut, int* found);

// TODO: remove before submission
int Evr_printArrayRBT(EvrPtr E);

/*
Description: Print all the elements in the DataArray of the EvrPtr in sorted
ascending order. For this to happen the RBT is traversed in order and the
elements are printed. Each line of the out file has the following format:
airportID;arrivals;departures;. The function also prints the total number of
elements that were printed.

Parameters:
    - E (EvrPtr): A pointer to the EvrPtr.
    - out (FILE*): The file to which the elements are printed.
Return values:
    - -2: if the log file used to store temporary information could not be
    deleted successfully.
    - -1: if the RBT is empty.
    - 0: if the function was successful.
*/
int Evr_printAll(EvrPtr E, FILE* out);

#endif
