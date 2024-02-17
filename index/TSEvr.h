#ifndef __TSIndex__
#define __TSIndex__

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
} TStoixeiouEvr;

/*
Description: Initializes the target struct with the values the source struct
holds.

Parameters:
  - target (TStoixeiouEvr*): The struct to be initialized.
  - source (TStoixeiouEvr): The struct to initialize the target with.

Return value:
    - 0 if the operation was successful.
*/
int TSIndex_setValue(TStoixeiouEvr* target, TStoixeiouEvr source);

/*
Description: Reads a line from the file from and stores the values in the
TStoixeiouEvr ELem struct.

Parameters:
  - from (FILE*): The file to read from.
  - Elem (TStoixeiouEvr*): The struct to store the values.

Return value:
    - 0 if the operation was successful.
*/
int TSIndex_readValue(FILE* from, TStoixeiouEvr* Elem);

/*
Description: Writes the values of the TStoixeiouEvr Elem struct to the file to.
The fields are separated with the delimeter ';' and when a char* field is NULL,
the string "\N" is written instead.

Parameters:
  - to (FILE*): The file to write to.
  - Elem (TStoixeiouEvr): The struct to write the values from.

Return value:
    - 0 if the operation was successful.
*/
int TSIndex_writeValue(FILE* to, TStoixeiouEvr Elem);

#endif
