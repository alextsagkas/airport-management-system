#include "../index/Evretirio.h"
#include "../rbt_module/rbt.h"
#include <stdio.h>

#define MAXSIZE 10
#define OUTPUT_FILEPATH "data/linux/output/test.txt"

int main() {
  /* ------------------------------------------------------ */
  EvrPtr E = Evr_construct(MAXSIZE);

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TStoixeiouEvr Elem;

  Elem.airportID = 2561;
  Elem.name = strdup("Guajara-Mirim Airport");
  Elem.city = strdup("Guajara-Mirim");
  Elem.country = strdup("Brazil");
  Elem.IATA = strdup("\\N");
  Elem.ICAO = strdup("SBGM");
  Elem.arrivals = 0;
  Elem.departures = 0;

  int insertResult = Evr_insert(E, Elem);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TStoixeiouEvr Elem1;

  Elem1.airportID = 3941;
  Elem1.name = strdup("Eleftherios Venizelos International Airport");
  Elem1.city = strdup("Athens");
  Elem1.country = strdup("Greece");
  Elem1.IATA = strdup("ATH");
  Elem1.ICAO = strdup("LGAV");
  Elem1.arrivals = 0;
  Elem1.departures = 0;

  insertResult = Evr_insert(E, Elem1);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Evr_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TStoixeiouEvr Elem2;

  Elem2.airportID = 6908;
  Elem2.name = strdup("Brest Airport");
  Elem2.city = strdup("Brest");
  Elem2.country = strdup("Belarus");
  Elem2.IATA = strdup("BQT");
  Elem2.ICAO = strdup("UMBB");
  Elem2.arrivals = 0;
  Elem2.departures = 0;

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
  FILE* out = fopen(OUTPUT_FILEPATH, "w");

  int print_result = Evr_printAll(E, out);

  switch (print_result) {
  case -2:
    printf("\nThe log file failed to be deleted.\n");
    break;
  case -1:
    printf("\nThe RBT is empty.\n");
    break;
  case 0:
    printf("\nThe file was written successfully.\n");
    break;

  default:
    break;
  }

  fclose(out);
  /* ------------------------------------------------------ */
  Evr_destruct(&E);
  /* ------------------------------------------------------ */

  return 0;
}
