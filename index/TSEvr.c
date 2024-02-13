#include "TSEvr.h"

#define MAX_LINE_LENGTH 100

// int TSEvr_setValue(TStoixeiouEvr* target, TStoixeiouEvr source) {
//   target->airportID = source.airportID;
//   target->name = strdup(source.name);
//   target->city = strdup(source.city);
//   target->country = strdup(source.country);
//   target->IATA = strdup(source.IATA);
//   target->ICAO = strdup(source.ICAO);

//   return 0;
// }

int TSEvr_readValue(FILE* from, TStoixeiouEvr* Elem) {
  char line[MAX_LINE_LENGTH];
  char delimeter[] = ";";
  char* token;

  if (fgets(line, sizeof(line), from)) {
    token = strtok(line, delimeter);
    Elem->airportID = atoi(token);

    token = strtok(NULL, delimeter);
    Elem->name = strdup(token);

    // if the city is not available, set it to NULL
    token = strtok(NULL, delimeter);
    if (strcmp(token, "\\N") == 0) {
      Elem->city = NULL;
    } else {
      Elem->city = strdup(token);
    }

    // If the country is not available, set it to NULL
    token = strtok(NULL, delimeter);
    if (strcmp(token, "\\N") == 0) {
      Elem->country = NULL;
    } else {
      Elem->country = strdup(token);
    }

    // If the IATA code is not available, set it to NULL
    token = strtok(NULL, delimeter);
    if (strcmp(token, "\\N") == 0) {
      Elem->IATA = NULL;
    } else {
      Elem->IATA = strdup(token);
    }

    // if the ICAO code is not available, set it to NULL
    token = strtok(NULL, delimeter);
    if (strcmp(token, "\\N") == 0) {
      Elem->ICAO = NULL;
    } else {
      Elem->ICAO = strdup(token);
    }

    // Initialize the arrivals and departures to 0
    Elem->arrivals = 0;
    Elem->departures = 0;
  }

  // Debug: Print the TStoixeiouEvr struct
  // printf("airportID: %d\n", Elem->airportID);
  // printf("name: %s\n", Elem->name);
  // printf("city: %s\n", Elem->city);
  // printf("country: %s\n", Elem->country);
  // printf("IATA: %s\n", Elem->IATA);
  // printf("ICAO: %s\n", Elem->ICAO);
  // printf("arrivals: %d\n", Elem->arrivals);
  // printf("departures: %d\n", Elem->departures);
  // printf("\n");

  return 0;
}

// int TSEvr_writeValue(FILE* to, TStoixeiouEvr Elem) {}
