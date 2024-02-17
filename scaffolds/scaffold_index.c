#include "../index_module/index.h"
#include "../rbt_module/rbt.h"
#include <stdio.h>

#define MAXSIZE 10
#define OUTPUT_FILEPATH "data/test/new_index.txt"

int main() {
  /* ------------------------------------------------------ */
  IndexNodep E = Index_construct(MAXSIZE);

  Index_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TElementIndex Elem;

  Elem.airportID = 2561;
  Elem.name = strdup("Guajara-Mirim Airport");
  Elem.city = strdup("Guajara-Mirim");
  Elem.country = strdup("Brazil");
  Elem.IATA = strdup("\\N");
  Elem.ICAO = strdup("SBGM");
  Elem.arrivals = 0;
  Elem.departures = 0;

  int insertResult = Index_insert(E, Elem);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Index_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TElementIndex Elem1;

  Elem1.airportID = 3941;
  Elem1.name = strdup("Eleftherios Venizelos International Airport");
  Elem1.city = strdup("Athens");
  Elem1.country = strdup("Greece");
  Elem1.IATA = strdup("ATH");
  Elem1.ICAO = strdup("LGAV");
  Elem1.arrivals = 0;
  Elem1.departures = 0;

  insertResult = Index_insert(E, Elem1);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Index_printArrayRBT(E);
  /* ------------------------------------------------------ */
  TElementIndex Elem2;

  Elem2.airportID = 6908;
  Elem2.name = strdup("Brest Airport");
  Elem2.city = strdup("Brest");
  Elem2.country = strdup("Belarus");
  Elem2.IATA = strdup("BQT");
  Elem2.ICAO = strdup("UMBB");
  Elem2.arrivals = 0;
  Elem2.departures = 0;

  insertResult = Index_insert(E, Elem2);

  if (insertResult == -1) {
    printf("\nInsertion failed.\n");
  } else if (insertResult == 0) {
    printf("\nInsertion successful.\n");
  }

  Index_printArrayRBT(E);
  /* ------------------------------------------------------ */

  int found;
  int result = Index_search(E, 6908, 0, &found);

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

  Index_printArrayRBT(E);
  /* ------------------------------------------------------ */

  result = Index_search(E, 6908, 1, &found);

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

  Index_printArrayRBT(E);
  /* ------------------------------------------------------ */
  FILE* out = fopen(OUTPUT_FILEPATH, "w");

  int counter;
  int print_result = Index_printAll(E, out, &counter);

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
  Index_destruct(&E);
  /* ------------------------------------------------------ */

  return 0;
}
