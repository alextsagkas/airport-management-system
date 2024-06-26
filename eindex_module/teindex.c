#include "teindex.h"

#define MAX_LINE_LENGTH 150

/*
Description: Prints the fields of the given Elem struct. It is used for
debugging purposes.

Parameters:
  - Elem (TElementIndex): The struct to print.

Return value:
  - 0: Success.
*/
int TEIndex_printStruct(TElementIndex Elem);

int TEIndex_setValue(TElementIndex* target, TElementIndex source) {
  // These two fields cannot be NULL so we can use strdup directly
  target->airport_id = source.airport_id;
  target->name = strdup(source.name);

  if (source.city == NULL) {
    target->city = NULL;
  } else {
    target->city = strdup(source.city);
  }

  if (source.country == NULL) {
    target->country = NULL;
  } else {
    target->country = strdup(source.country);
  }

  if (source.IATA == NULL) {
    target->IATA = NULL;
  } else {
    target->IATA = strdup(source.IATA);
  }

  if (source.ICAO == NULL) {
    target->ICAO = NULL;
  } else {
    target->ICAO = strdup(source.ICAO);
  }

  target->arrivals = source.arrivals;
  target->departures = source.departures;

  return 0;
}

int TEIndex_readValue(FILE* from, TElementIndex* Elem) {
  char line[MAX_LINE_LENGTH];
  char delimeter[] = ";";
  char* token;

  if (fgets(line, sizeof(line), from)) {
    token = strtok(line, delimeter);
    Elem->airport_id = atoi(token);

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

  return 0;
}

int TEIndex_writeValue(FILE* to, TElementIndex Elem) {
  fprintf(to, "%d;%s;", Elem.airport_id, Elem.name);

  if (Elem.city == NULL) {
    fprintf(to, "\\N;");
  } else {
    fprintf(to, "%s;", Elem.city);
  }

  if (Elem.country == NULL) {
    fprintf(to, "\\N;");
  } else {
    fprintf(to, "%s;", Elem.country);
  }

  if (Elem.IATA == NULL) {
    fprintf(to, "\\N;");
  } else {
    fprintf(to, "%s;", Elem.IATA);
  }

  if (Elem.ICAO == NULL) {
    fprintf(to, "\\N;");
  } else {
    fprintf(to, "%s;", Elem.ICAO);
  }

  fprintf(to, "%d;%d;\n", Elem.arrivals, Elem.departures);

  return 0;
}