#include "../index_module/teindex.h"
#include <stdio.h>

// #define FILEPATH "data/airportsLinuxRandom.txt"
#define FILEPATH "data/airportsLinuxSorted.txt"
// #define NEW_FILEPATH "data/test/new_airportsLinuxRandom.txt"
#define NEW_FILEPATH "data/test/new_airportsLinuxSorted.txt"

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

  /*
    Verification of similarity:
    ---------------------------

     In order to check the new_file, use the diff command in the terminal
     One caveat is that the new_file contains also the arrivals and departures,
     so, you could temporarily remove them from TEIndex_writeValue in teindex.c to
     compare the files.
  */

  return 0;
}