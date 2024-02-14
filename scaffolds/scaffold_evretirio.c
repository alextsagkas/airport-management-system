#include "../index/Evretirio.h"
#include "../rbt_module/rbt.h"
#include <stdio.h>

#define MAXSIZE 10

int main() {
  /* ------------------------------------------------------ */
  EvrPtr E = Evr_construct(MAXSIZE);

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TStoixeiouEvr Elem = {.airportID = 2561,
                        .name = "Guajara-Mirim Airport",
                        .city = "Guajara-Mirim",
                        .country = "Brazil",
                        .IATA = "\\N",
                        .ICAO = "SBGM",
                        .arrivals = 0,
                        .departures = 0};

  int insertResult = Evr_insert(E, Elem);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TStoixeiouEvr Elem1 = {.airportID = 3941,
                         .name = "Eleftherios Venizelos International Airport",
                         .city = "Athens",
                         .country = "Greece",
                         .IATA = "ATH",
                         .ICAO = "LGAV",
                         .arrivals = 0,
                         .departures = 0};

  insertResult = Evr_insert(E, Elem1);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TStoixeiouEvr Elem2 = {.airportID = 6908,
                         .name = "Brest Airport",
                         .city = "Brest",
                         .country = "Belarus",
                         .IATA = "BQT",
                         .ICAO = "UMBB",
                         .arrivals = 0,
                         .departures = 0};
  insertResult = Evr_insert(E, Elem2);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */

  int found;
  int result = Evr_search(E, 6908, 0, &found);

  switch (result) {
  case -2:
    printf("\nThe InOut parameter is not valid.\n");
    break;
  case -1:
    printf("\nThe key was not found in the RBT.\n");
    break;
  case 0:
    printf("\nThe search was successful.\n");
    break;
  default:
    printf("\nThe result is not valid.\n");
    break;
  }

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */

  result = Evr_search(E, 6908, 1, &found);

  switch (result) {
  case -2:
    printf("\nThe InOut parameter is not valid.\n");
    break;
  case -1:
    printf("\nThe key was not found in the RBT.\n");
    break;
  case 0:
    printf("\nThe search was successful.\n");
    break;
  default:
    printf("\nThe result is not valid.\n");
    break;
  }

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */
  Evr_destruct(&E);
  /* ------------------------------------------------------ */

  return 0;
}
