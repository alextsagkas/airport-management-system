#include "index.h"
#include <assert.h>

#include "../rbt_module/rbt.h" /* h Ylopoihsh sas toy R/B */

#define LOG_FILEPATH "data/output/temp.txt"

struct IndexNode {
  TElementIndex* DataArray; /* array of size MaxSize */
  int Index;                /* index of first available element in array */
  Treep TreeRoot;           /* Root of DDA */
} IndexNode;

IndexNodep Index_construct(int MaxSize) {
  IndexNodep E = (IndexNodep)malloc(sizeof(struct IndexNode));
  assert(E != NULL);

  E->DataArray = (TElementIndex*)malloc(MaxSize * sizeof(TElementIndex));
  assert(E->DataArray != NULL);

  // Start at 0-th position to add TElementIndex in the DataArray
  E->Index = 0;

  E->TreeRoot = RBT_create_tree();

  return E;
}

int Index_insert(IndexNodep E, TElementIndex Data) {
  E->DataArray[E->Index] = Data;
  E->Index++;

  TBSTElement* DDAData = TEBST_create(Data.airport_id, E->Index - 1);
  if (RBT_insert((E->TreeRoot), (void*)DDAData, TEBST_compare) != 0) {
    return -1;
  }

  return 0;
}

int Index_search(IndexNodep E, keyType key, int InOut, int* found) {
  // The index is not used for searching, so it is set arbitrarily to 0
  TBSTElement DDAData = {.key = key, .arrayIndex = 0};

  void* result = RBT_search_key(E->TreeRoot, (void*)&DDAData, TEBST_compare);

  if (result == NULL) {
    *found = 0;
    return -1;
  } else {
    *found = 1;
  }

  TElementIndex* Data = &E->DataArray[((TBSTElement*)result)->arrayIndex];

  if (InOut == 0) {
    TEIndex_setValue(Data,
                     (TElementIndex){.airport_id = Data->airport_id,
                                     .name = Data->name,
                                     .city = Data->city,
                                     .country = Data->country,
                                     .IATA = Data->IATA,
                                     .ICAO = Data->ICAO,
                                     .arrivals = Data->arrivals + 1,
                                     .departures = Data->departures});
  } else if (InOut == 1) {
    TEIndex_setValue(Data,
                     (TElementIndex){.airport_id = Data->airport_id,
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

int Index_printAll(IndexNodep E, FILE* out, int* counter) {
  FILE* log = fopen(LOG_FILEPATH, "w+");

  // Write the airport_id and the arrayIndex to the file
  int result = RBT_print_to_file(E->TreeRoot, log, TEBST_fprint) == -1;

  // T is empty
  if (result == -1) {
    return -1;
  }

  // Reading specific variables
  char delimeter[] = ";";
  char line[100];
  char* token;

  TElementIndex* Data;

  fseek(log, 0, SEEK_SET);

  // Preamble of the data that will follow
  fprintf(out, "\nairport_id;Arrivals;Departures;\n");
  fprintf(out, "------------------------------\n");

  // Count the elements that will be printed
  *counter = 0;

  // Read the file and print the airport_id and the arrayIndex and print the
  // corresponding arrivals and departures from the DataArray
  while (fgets(line, sizeof(line), log)) {
    token = strtok(line, delimeter);
    int airport_id = atoi(token);

    token = strtok(NULL, delimeter);
    int arrayIndex = atoi(token);

    Data = &(E->DataArray[arrayIndex]);

    fprintf(out, "%d;", Data->airport_id);
    fprintf(out, "%d;", Data->arrivals);
    fprintf(out, "%d;\n", Data->departures);

    (*counter)++;
  }

  fclose(log);

  if (remove(LOG_FILEPATH) != 0)
    return -2;

  return 0;
}

int Index_destruct(IndexNodep* E) {
  keyType key;
  void* TEBSTData;

  for (int i = 0; i < (*E)->Index; i++) {
    key = (*E)->DataArray[i].airport_id;
    // Deallocate the RBT node
    TEBSTData = RBT_delete((*E)->TreeRoot, (void*)&key, TEBST_compare);
    // Deallocate the key of the RBT node
    TEBST_delete(TEBSTData);

    // Deallocate the strings that used strdup
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

  // Deallocate the IndexNode
  free(*E);
  *E = NULL;

  return 0;
}

int Index_printArrayRBT(IndexNodep E) {
  printf("\n----------------------------------\n");
  for (int i = 0; i < E->Index; i++) {
    printf("Index: %d\n", i);
    printf("Airport ID: %d\n", E->DataArray[i].airport_id);
    printf("Name: %s\n", E->DataArray[i].name);
    printf("City: %s\n", E->DataArray[i].city);
    printf("Country: %s\n", E->DataArray[i].country);
    printf("IATA: %s\n", E->DataArray[i].IATA);
    printf("ICAO: %s\n", E->DataArray[i].ICAO);
    printf("Arrivals: %d\n", E->DataArray[i].arrivals);
    printf("Departures: %d\n", E->DataArray[i].departures);
    printf("\n");
  }

  RBT_print_tree(E->TreeRoot, TEBST_print);
  printf("\n----------------------------------\n");

  return 0;
}
