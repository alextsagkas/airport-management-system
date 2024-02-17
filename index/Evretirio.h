#ifndef __Index__
#define __Index__

#include "tebst.h"
#include "TSEvr.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct IndexNode* IndexNodep;

/*
Description: Construct a new IndexNodep. Its fields hold the following
information:
    - The DataArray is an array of TElementIndex of size MaxSize.
    - The Index is initialized to 0, which is the first available position in
      the DataArray.
    - The TreeRoot is the root of the DDA.

Parameters:
    - Maxsize (int): The size of the DataArray.

Return values:
    - IndexNodep: A pointer to the newly constructed IndexNodep.

Asserts:
    - The IndexNodep is not NULL.
    - The DataArray is not NULL.
    - The TreeRoot is not NULL.
*/
IndexNodep Index_construct(int MaxSize);

/*
Description: Destroy an IndexNode. The function frees the memory allocated for
the DataArray and the RBT's nodes. Specifically for the elements of DataArray,
every string that is dynamically allocated is freed before the dynamically
allocated array is freed. It also frees the memory allocated for the IndexNode.

Parameters:
    - E (IndexNodep*): A pointer to the IndexNodep.

Return values:
    - 0 : if the function was successful.
*/
int Index_destruct(IndexNodep* E);

/*
Description: Insert a new TElementIndex in the IndexNodep's DataArray and RBT.

Parameters:
    - E (IndexNodep): A pointer to the IndexNodep.
    - Data (TElementIndex): The TElementIndex to be inserted.

Return values:
    - 0 : if the function was successful.
    - -1: if the insertion in the RBT was not successful.
*/
int Index_insert(IndexNodep E, TElementIndex Data);

/*
Description: Search for a TBSTElement in the IndexNodep's RBT with
corresponding key to the parameter passed in the function. The function sets the
value of the parameter found to 1 if the key was found in the RBT, otherwise it
sets it to 0. Also, if the key is found in the RBT, the function increments the
arrivals or departures of the corresponding TElementIndex in the DataArray, when
the InOut is 0 or 1, respectively.

Parameters:
    - E (IndexNodep): A pointer to the IndexNodep.
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
int Index_search(IndexNodep E, keyType key, int InOut, int* found);

/*
Description: Print all the elements in the DataArray of the IndexNodep in sorted
ascending order. For this to happen the RBT is traversed in order and the
elements are printed. Each line of the out file has the following format:
airportID;arrivals;departures;

Parameters:
    - E (IndexNodep): A pointer to the IndexNodep.
    - out (FILE*): The file to which the elements are printed.
    - counter (int*): The number of elements printed to the file.
Return values:
    - -2: if the log file used to store temporary information could not be
    deleted successfully.
    - -1: if the RBT is empty.
    - 0: if the function was successful.
*/
int Index_printAll(IndexNodep E, FILE* out, int* counter);

/*
Description: Prints the IndexNode E. Specifically, it prints the DataArray and
the RBT TreeRoot. It is used for debugging purposes only.

Parameters:
  - E (IndexNodep): The IndexNode to be printed.

Return value:
  - 0: Success.
*/
int Index_printArrayRBT(IndexNodep E);

#endif
