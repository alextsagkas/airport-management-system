#include "../index/TSEvr.h"
#include <stdio.h>

#define FILEPATH "data/linux/airportsLinuxRandom.txt"

int main() {
  TStoixeiouEvr airport;

  FILE* file = fopen(FILEPATH, "r");
  if (file == NULL) {
    return -1;
  }

  while (!feof(file)) {
    TSEvr_readValue(file, &airport);
  }

  fclose(file);

  return 0;
}