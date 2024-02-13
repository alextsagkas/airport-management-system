#include "../index/TSEvr.h"
#include <stdio.h>

#define FILEPATH "data/linux/airportsLinuxRandom.txt"

int main() {
  TStoixeiouEvr airport;
  TStoixeiouEvr airport2;

  FILE* file = fopen(FILEPATH, "r");
  if (file == NULL) {
    return -1;
  }

  while (!feof(file)) {
    TSEvr_readValue(file, &airport);
    TSEvr_setValue(&airport2, airport);
  }

  fclose(file);

  return 0;
}