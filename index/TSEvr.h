#ifndef __TEIndex__
#define __TEIndex__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  int airportID;
  char* name;
  char* city;
  char* country;
  char* IATA;
  char* ICAO;
  int arrivals;
  int departures;
} TElementIndex;

/*
Description: Initializes the target struct with the values the source struct
holds.

Parameters:
  - target (TElementIndex*): The struct to be initialized.
  - source (TElementIndex): The struct to initialize the target with.

Return value:
    - 0 if the operation was successful.
*/
int TEIndex_setValue(TElementIndex* target, TElementIndex source);

/*
Description: Reads a line from the file from and stores the values in the
TElementIndex ELem struct.

Parameters:
  - from (FILE*): The file to read from.
  - Elem (TElementIndex*): The struct to store the values.

Return value:
    - 0 if the operation was successful.
*/
int TEIndex_readValue(FILE* from, TElementIndex* Elem);

/*
Description: Writes the values of the TElementIndex Elem struct to the file to.
The fields are separated with the delimeter ';' and when a char* field is NULL,
the string "\N" is written instead.

Parameters:
  - to (FILE*): The file to write to.
  - Elem (TElementIndex): The struct to write the values from.

Return value:
    - 0 if the operation was successful.
*/
int TEIndex_writeValue(FILE* to, TElementIndex Elem);

#endif
