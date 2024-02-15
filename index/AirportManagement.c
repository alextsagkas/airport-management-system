/*
Client Program 	: AirportManagement.c
Author			    : Alexandros Tsagkaropoulos
Goal			    	: Extention of RBT to manage airports
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> /* for gettimeofday() */

#include "Evretirio.h"
#include "TSDDA.h"
#include "TSEvr.h"

#define RANDOM_FILEPATH "data/linux/airportsLinuxRandom.txt"
#define ROUTES_FILEPATH "data/linux/routesLinux.txt"
#define OUTPUT_RANDOM_FILEPATH "data/linux/output/OUTPUTRandomBST.txt"

/*
Description: Insert elements to the Evr (both DataArray and RBT) from the
RANDOM_FILEPATH file. It also prints to the console the following information:
  - Time intervals for 2^N - 1 elements where N = 9, 10, 11, 12.
  - Total time elapsed for the insertion of all elements.
  - Total elements inserted.

Parameters:
  - E (EvrPtr): Pointer to the Evr.

Returns:
  - -2: if the insertion on the RBT fails.
  - -1: if the file cannot be opened.
  - 0: if the procedure is successful.
*/
int insert_elements_to_evr(EvrPtr E);

/*
Description: Update the arrivals and departures of the airports in the RBT from
the routes file and print the following information to the
OUTPUT_RANDOM_FILEPATH:
  - Total time elapsed.
  - Mean time per route.
  - Routes counter.
  - Found counter.
  - Not found counter.

Parameters:
  - E (EvrPtr): Pointer to the Evr.

Returns:
  - -2 : if the output file cannot be opened.
  - -1: if the routes file cannot be opened.
  - 0: if the procedure is successful.
*/
int update_arrivals_departures(EvrPtr E);

int main() {
  EvrPtr E;

  E = Evr_construct(7200);

  insert_elements_to_evr(E);

  printf("\n----------------------------------------\n");

  update_arrivals_departures(E);

  printf("\n----------------------------------------\n");

  return 0;
}

int insert_elements_to_evr(EvrPtr E) {
  FILE* file;
  TStoixeiouEvr elem;
  int ret;

  file = fopen(RANDOM_FILEPATH, "r");
  if (file == NULL) {
    return -1;
  }

  // total time elapsed
  struct timeval t_start, t_end;

  double time_elapsed;

  // count time intervals for 2^N - 1 elements
  // where N = 9, 10, 11, 12.
  struct timeval t_start_9, t_end_9;
  struct timeval t_start_10, t_end_10;
  struct timeval t_start_11, t_end_11;
  struct timeval t_start_12, t_end_12;

  double time_elapsed_9;
  double time_elapsed_10;
  double time_elapsed_11;
  double time_elapsed_12;

  int count_elements = 1;

  // start timers
  gettimeofday(&t_start, NULL);
  gettimeofday(&t_start_9, NULL);
  gettimeofday(&t_start_10, NULL);
  gettimeofday(&t_start_11, NULL);
  gettimeofday(&t_start_12, NULL);

  while (!feof(file)) {
    // start timers
    if (count_elements % 511 == 0) {
      gettimeofday(&t_end_9, NULL);

      time_elapsed_9 = ((t_end_9.tv_sec - t_start_9.tv_sec) / 1000.0) +
                       ((t_end_9.tv_usec - t_start_9.tv_usec) / 1000.0);
      printf("Time interval for 511 elements: %g ms\n", time_elapsed_9);

      gettimeofday(&t_start_9, NULL);
    } else if (count_elements % 1023 == 0) {
      gettimeofday(&t_end_10, NULL);

      time_elapsed_10 = ((t_end_10.tv_sec - t_start_10.tv_sec) / 1000.0) +
                        ((t_end_10.tv_usec - t_start_10.tv_usec) / 1000.0);
      printf("Time interval for 1023 elements: %g ms\n", time_elapsed_10);

      gettimeofday(&t_start_10, NULL);
    } else if (count_elements % 2047 == 0) {
      gettimeofday(&t_end_11, NULL);

      time_elapsed_11 = ((t_end_11.tv_sec - t_start_11.tv_sec) / 1000.0) +
                        ((t_end_11.tv_usec - t_start_11.tv_usec) / 1000.0);
      printf("Time interval for 2047 elements: %g ms\n", time_elapsed_11);

      gettimeofday(&t_start_11, NULL);
    } else if (count_elements % 4095 == 0) {
      gettimeofday(&t_end_12, NULL);

      time_elapsed_12 = ((t_end_12.tv_sec - t_start_12.tv_sec) / 1000.0) +
                        ((t_end_12.tv_usec - t_start_12.tv_usec) / 1000.0);
      printf("Time interval for 4095 elements: %g ms\n", time_elapsed_12);

      gettimeofday(&t_start_12, NULL);
    }

    TSEvr_readValue(file, &elem);
    ret = Evr_insert(E, elem);
    if (ret != 0) {
      return -2;
    }

    count_elements++;
  }

  gettimeofday(&t_end, NULL);
  time_elapsed = ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                 ((t_end.tv_usec - t_start.tv_usec) / 1000.0);

  printf("\nTotal time elapsed: %g ms\n", time_elapsed);
  printf("Total elements inserted: %d\n", count_elements);

  fclose(file);
  return 0;
}

int update_arrivals_departures(EvrPtr E) {
  FILE* file = fopen(ROUTES_FILEPATH, "r");

  if (file == NULL) {
    return -1;
  }

  // Read data from routes file
  char line[100];
  char delimeter[] = ";";
  char* token;

  // Fields stored in file
  char* airline;
  int airline_id;
  char* source_airport;
  int source_airport_id;
  char* destination_airport;
  int destination_airport_id;
  char* codeshare;
  int stops;
  char* equipment;

  // Fields for searching in the RBT
  int found;

  int routes_counter = 0;
  int found_counter = 0;
  int not_found_counter = 0;

  // Time Capture
  struct timeval t_start, t_end;
  double elapsed_time;

  // Start timer
  gettimeofday(&t_start, NULL);

  while (!feof(file)) {
    // Process a line
    if (fgets(line, sizeof(line), file)) {
      // Read the fields from the line for the route
      token = strtok(line, delimeter);
      airline = strdup(token);

      token = strtok(NULL, delimeter);
      airline_id = atoi(token);

      token = strtok(NULL, delimeter);
      source_airport = strdup(token);

      token = strtok(NULL, delimeter);
      source_airport_id = atoi(token);

      token = strtok(NULL, delimeter);
      destination_airport = strdup(token);

      token = strtok(NULL, delimeter);
      destination_airport_id = atoi(token);

      token = strtok(NULL, delimeter);
      codeshare = strdup(token);

      token = strtok(NULL, delimeter);
      stops = atoi(token);

      token = strtok(NULL, delimeter);
      equipment = strdup(token);

      // Search for source airport in the RBT
      Evr_search(E, source_airport_id, 1, &found);

      if (found == 1) {
        found_counter++;
      } else {
        not_found_counter++;
      }

      // Search for the destination airport in the RBT
      Evr_search(E, destination_airport_id, 0, &found);

      if (found == 1) {
        found_counter++;
      } else {
        not_found_counter++;
      }

      // Free Strings that hold route fields
      free(airline);
      free(source_airport);
      free(destination_airport);
      free(codeshare);
      free(equipment);
    }

    routes_counter++;
  }

  // Stop timer
  gettimeofday(&t_end, NULL);

  elapsed_time = ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                 ((t_end.tv_usec - t_start.tv_usec) / 1000.0);

  // Store Information in OUTPUTRandomBST.txt
  FILE* output_file = fopen(OUTPUT_RANDOM_FILEPATH, "w");

  if (output_file == NULL) {
    return -2;
  }

  fprintf(output_file, "Total time elapsed: %g ms\n", elapsed_time);
  fprintf(output_file,
          "Mean time per route: %g ms\n",
          elapsed_time / (routes_counter * 2));
  fprintf(output_file, "Routes counter: %d\n", routes_counter);
  fprintf(output_file, "Found counter: %d\n", found_counter);
  fprintf(output_file, "Not found counter: %d\n", not_found_counter);

  fclose(output_file);

  // Close the routes file
  fclose(file);

  return 0;
}