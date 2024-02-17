#include "TSEvr.h"

#define MAX_LINE_LENGTH 150

/*
Description: Prints the fields of the given Elem struct. It is used for
debugging purposes.

Parameters:
  - Elem (TStoixeiouEvr): The struct to print.

Return value:
  - 0: Success.
*/
int TSEvr_printStruct(TStoixeiouEvr Elem);

int TSEvr_setValue(TStoixeiouEvr* target, TStoixeiouEvr source) {
  // These two fields cannot be NULL so we can use strdup directly
  target->airportID = source.airportID;
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

  return 0;
}

int TSEvr_writeValue(FILE* to, TStoixeiouEvr Elem) {
  fprintf(to, "%d;%s;", Elem.airportID, Elem.name);

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

int TSEvr_printStruct(TStoixeiouEvr Elem) {
  printf("airportID: %d\n", Elem.airportID);
  printf("name: %s\n", Elem.name);
  printf("city: %s\n", Elem.city);
  printf("country: %s\n", Elem.country);
  printf("IATA: %s\n", Elem.IATA);
  printf("ICAO: %s\n", Elem.ICAO);
  printf("arrivals: %d\n", Elem.arrivals);
  printf("departures: %d\n", Elem.departures);
  printf("\n");

  return 0;
}