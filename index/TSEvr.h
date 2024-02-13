#ifndef __TSEvr__
#define __TSEvr__

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

// int TSEvr_setValue(TStoixeiouEvr* target, TStoixeiouEvr source);

/*
Description: Reads a line from the file from and stores the values in the
TStoixeiouEvr ELem struct

Parameters:
  - from (FILE*): The file to read from
  - Elem (TStoixeiouEvr*): The struct to store the values

Return values:
    - 0 if the operation was successful
*/
int TSEvr_readValue(FILE* from, TStoixeiouEvr* Elem);

// int TSEvr_writeValue(FILE* to, TStoixeiouEvr Elem);

#endif
