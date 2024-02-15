#include "Evretirio.h"
#include <assert.h>

#include "../rbt_module/rbt.h" /* h Ylopoihsh sas toy R/B */

#define LOG_FILEPATH "data/linux/output/temp.txt"

/*
Description: Prints the EvrNode E. Specifically, it prints the DataArray and the
RBT TreeRoot. It is used for debugging purposes.

Parameters:
  - E (EvrPtr): The EvrNode to be printed.

Return value:
  - 0: Success.
*/
int Evr_printArrayRBT(EvrPtr E);

struct EvrNode {
  TStoixeiouEvr* DataArray; /* array of size MaxSize */
  int Index;                /* index of first available element in array */
  Treep TreeRoot;           /* Root of DDA */
} EvrNode;

EvrPtr Evr_construct(int MaxSize) {
  EvrPtr E = (EvrPtr)malloc(sizeof(struct EvrNode));
  assert(E != NULL);

  E->DataArray = (TStoixeiouEvr*)malloc(MaxSize * sizeof(TStoixeiouEvr));
  assert(E->DataArray != NULL);

  // Start at 0-th position to add TStoixeiouEvr in the DataArray
  E->Index = 0;

  E->TreeRoot = RBT_create_tree();

  return E;
}

int Evr_insert(EvrPtr E, TStoixeiouEvr Data) {
  E->DataArray[E->Index] = Data;
  E->Index++;

  TStoixeiouDDA* DDAData = TSDDA_create(Data.airportID, E->Index - 1);
  if (RBT_insert((E->TreeRoot), (void*)DDAData, TSDDA_compare) != 0) {
    return -1;
  }

  return 0;
}

int Evr_search(EvrPtr E, keyType key, int InOut, int* found) {
  // The index is not used for searching, so it is set arbitrarily to 0
  TStoixeiouDDA DDAData = {.key = key, .arrayIndex = 0};

  void* result = RBT_search_key(E->TreeRoot, (void*)&DDAData, TSDDA_compare);

  if (result == NULL) {
    *found = 0;
    return -1;
  } else {
    *found = 1;
  }

  TStoixeiouEvr* Data = &E->DataArray[((TStoixeiouDDA*)result)->arrayIndex];

  if (InOut == 0) {
    TSEvr_setValue(Data,
                   (TStoixeiouEvr){.airportID = Data->airportID,
                                   .name = Data->name,
                                   .city = Data->city,
                                   .country = Data->country,
                                   .IATA = Data->IATA,
                                   .ICAO = Data->ICAO,
                                   .arrivals = Data->arrivals + 1,
                                   .departures = Data->departures});
  } else if (InOut == 1) {
    TSEvr_setValue(Data,
                   (TStoixeiouEvr){.airportID = Data->airportID,
                                   .name = Data->name,
                                   .city = Data->city,
                                   .country = Data->country,
                                   .IATA = Data->IATA,
                                   .ICAO = Data->ICAO,
                                   .arrivals = Data->arrivals,
                                   .departures = Data->departures + 1});
  } else {
    return -2;
  }

  return 0;
}

int Evr_printAll(EvrPtr E, FILE* out) {
  FILE* log = fopen(LOG_FILEPATH, "w+");

  // Write the AirportID and the arrayIndex to the file
  int result = RBT_print_to_file(E->TreeRoot, log, TSDDA_fprint) == -1;

  // T is empty
  if (result == -1) {
    return -1;
  }

  // Reading specific variables
  char delimeter[] = ";";
  char line[100];
  char* token;

  TStoixeiouEvr* Data;

  fseek(log, 0, SEEK_SET);

  // Read the file and print the AirportID and the arrayIndex and print the
  // corresponding arrivals and departures from the DataArray
  while (fgets(line, sizeof(line), log)) {
    token = strtok(line, delimeter);
    int airportID = atoi(token);

    token = strtok(NULL, delimeter);
    int arrayIndex = atoi(token);

    Data = &(E->DataArray[arrayIndex]);

    fprintf(out, "%d;", Data->airportID);
    fprintf(out, "%d;", Data->arrivals);
    fprintf(out, "%d;\n", Data->departures);
  }

  fclose(log);

  if (remove(LOG_FILEPATH) != 0)
    return -2;

  return 0;
}

int Evr_destruct(EvrPtr* E) {
  keyType key;
  void* TSDDAData;

  for (int i = 0; i < (*E)->Index; i++) {
    key = (*E)->DataArray[i].airportID;
    // Deallocate the RBT node
    TSDDAData = RBT_delete((*E)->TreeRoot, (void*)&key, TSDDA_compare);
    // Deallocate the key of the RBT node
    TSDDA_delete(TSDDAData);

    free((*E)->DataArray[i].name);
    free((*E)->DataArray[i].city);
    free((*E)->DataArray[i].country);
    free((*E)->DataArray[i].IATA);
    free((*E)->DataArray[i].ICAO);
  }

  // Deallocate the DataArray
  free((*E)->DataArray);
  (*E)->DataArray = NULL;

  // Deallocate the RBT
  RBT_delete_tree((*E)->TreeRoot);

  // Deallocate the EvrNode
  free(*E);
  *E = NULL;

  return 0;
}

/*
Description: Prints the EvrNode E. Specifically, it prints the DataArray and
the RBT TreeRoot. It is used for debugging purposes.

Parameters:
  - E (EvrPtr): The EvrNode to be printed.

Return value:
  - 0: Success.
*/
int Evr_printArrayRBT(EvrPtr E) {
  printf("\n----------------------------------\n");
  for (int i = 0; i < E->Index; i++) {
    printf("Index: %d\n", i);
    printf("Airport ID: %d\n", E->DataArray[i].airportID);
    printf("Name: %s\n", E->DataArray[i].name);
    printf("City: %s\n", E->DataArray[i].city);
    printf("Country: %s\n", E->DataArray[i].country);
    printf("IATA: %s\n", E->DataArray[i].IATA);
    printf("ICAO: %s\n", E->DataArray[i].ICAO);
    printf("Arrivals: %d\n", E->DataArray[i].arrivals);
    printf("Departures: %d\n", E->DataArray[i].departures);
    printf("\n");
  }

  RBT_print_tree(E->TreeRoot, TSDDA_print);
  printf("\n----------------------------------\n");

  return 0;
}
