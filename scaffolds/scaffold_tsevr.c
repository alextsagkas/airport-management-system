#include "../index/TSEvr.h"
#include <stdio.h>

// #define FILEPATH "data/linux/airportsLinuxRandom.txt"
#define FILEPATH "data/linux/airportsLinuxSorted.txt"
// #define NEW_FILEPATH "data/linux/test/new_airportsLinuxRandom.txt"
#define NEW_FILEPATH "data/linux/test/new_airportsLinuxSorted.txt"

int main() {
  FILE* file = fopen(FILEPATH, "r");
  if (file == NULL) {
    return -1;
  }

  FILE* new_file = fopen(NEW_FILEPATH, "w");
  if (new_file == NULL) {
    return -1;
  }

  TStoixeiouEvr airport;
  TStoixeiouEvr airport2;

  while (!feof(file)) {
    TSIndex_readValue(file, &airport);
    TSIndex_setValue(&airport2, airport);
    TSIndex_writeValue(new_file, airport2);
  }

  fclose(file);
  fclose(new_file);

  /*
    Verification of similarity:
    ---------------------------

     In order to check the new_file, use the diff command in the terminal
     One caveat is that the new_file contains also the arrivals and departures,
     so, you could temporarily remove them from TSIndex_writeValue in TSEvr.c to
     compare the files.
  */

  return 0;
}