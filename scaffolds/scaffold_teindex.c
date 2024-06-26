#include "../eindex_module/teindex.h"
#include <stdio.h>

// #define FILEPATH "data/airports_random.txt"
#define FILEPATH "data/airports_sorted.txt"
// #define NEW_FILEPATH "data/test/new_airports_random.txt"
#define NEW_FILEPATH "data/test/new_airports_sorted.txt"

int main() {
  FILE* file = fopen(FILEPATH, "r");
  if (file == NULL) {
    return -1;
  }

  FILE* new_file = fopen(NEW_FILEPATH, "w");
  if (new_file == NULL) {
    return -1;
  }

  TElementIndex airport;
  TElementIndex airport2;

  while (!feof(file)) {
    TEIndex_readValue(file, &airport);
    TEIndex_setValue(&airport2, airport);
    TEIndex_writeValue(new_file, airport2);
  }

  fclose(file);
  fclose(new_file);

  printf("File %s has been copied to %s\n", FILEPATH, NEW_FILEPATH);

  /*
    Verification of similarity:
    ---------------------------

     In order to check the new_file, use the diff command in the terminal
     One caveat is that the new_file contains also the arrivals and
    departures, so, you could temporarily remove them from
    TEIndex_writeValue in teindex.c to compare the files.
  */

  return 0;
}