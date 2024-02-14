#include "../index/Evretirio.h"
#include <stdio.h>

#define MAXSIZE 10

int main() {
  EvrPtr E = Evr_construct(MAXSIZE);

  TStoixeiouEvr Elem = {2561,
                        "Guajara-Mirim Airport",
                        "Guajara-Mirim",
                        "Brazil",
                        "\n",
                        "SBGM",
                        0,
                        0};
  Evr_insert(E, Elem);

  Evr_destruct(&E);

  return 0;
}