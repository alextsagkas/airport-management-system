/*
Client Program 	: AirportManagement.c
Author			    : Alexandros Tsagkaropoulos
Goal			    	: Extention of RBT to manage airports
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "index/index.h"
#include "index/tebst.h"
#include "index/teindex.h"

// Filepaths
#define RANDOM_FILEPATH "data/linux/airportsLinuxRandom.txt"
#define SORTED_FILEPATH "data/linux/airportsLinuxSorted.txt"
#define ROUTES_FILEPATH "data/linux/routesLinux.txt"
#define output_random_file_FILEPATH "data/linux/output/OUTPUTRandomBST.txt"
#define output_sorted_file_FILEPATH "data/linux/output/OUTPUTSortedBST.txt"

/*
Description: Insert elements to the Evr (both DataArray and RBT) from the file
provided from the parameters. It also prints to the output_file the following
information:
  - Time intervals for 2^N - 1 elements where N = 9, 10, 11, 12.
  - Total time elapsed for the insertion of all elements.
  - Total elements inserted.

Parameters:
  - E (IndexNodep): Pointer to the Evr.
  - airports_file (FILE*): The file from which the airports are read.
  - output_file (FILE*): The file to which the information is printed.

Returns:
  - -1: if the insertion on the RBT fails.
  - 0: if the procedure is successful.
*/
int insert_elements_to_evr(IndexNodep E,
                           FILE* airports_file,
                           FILE* output_file);

/*
Description: Update the arrivals and departures of the airports in the RBT from
the routes_file and print the following information to the output_file:
  - Total time elapsed.
  - Mean time per route.
  - Routes counter.
  - Found counter.
  - Not found counter.

Parameters:
  - E (IndexNodep): Pointer to the Evr.
  - routes_file (FILE*): The file from which the routes are read.
  - output_file (FILE*): The file to which the information is printed.

Returns:
  - 0: if the procedure is successful.
*/
int update_arrivals_departures(IndexNodep E,
                               FILE* routes_file,
                               FILE* output_file);

/*
Description: Print the elements of the Evr to the file, in ascending order, by
traversing the RBT. The format of each line is: airportID;arrivals;departures;.
In the end, it prints the total number of elements printed and the total time
elapsed for the print completion.

Parameters:
  - E (IndexNodep): Pointer to the Evr.
  - file (FILE*): The file to which the elements are printed.

Return values:
  - -1: if the elements could not be printed to the file.
  - 0: if the procedure is successful.
*/
int print_elements_to_file(IndexNodep E, FILE* file);

/*
Description: The client program that uses the Evr to handle airports and routes
between them. The steps it executes are the following:
  1. Construct the Evr.
  2. Insert elements to the Evr from the airports_file.
  3. Update arrivals and departures from routes_file and print to output_file.
  4. Print elements and log data to the output_file.
  5. Destruct the Evr.

Parameters:
  - airports_file (FILE*): The file from which the airports are read.
  - routes_file (FILE*): The file from which the routes are read.
  - output_file (FILE*): The file to which the information is printed.

Returns:
  - 0: if the procedure is successful.
*/
int client_program(FILE* airports_file, FILE* routes_file, FILE* output_file);

int main() {
  // Sorted airports file
  printf("\n~~~~~~~~~~ Sorted Airports File ~~~~~~~~~\n");
  FILE* airports_sorted_file = fopen(SORTED_FILEPATH, "r");
  assert(airports_sorted_file != NULL);

  FILE* routes_file = fopen(ROUTES_FILEPATH, "r");
  assert(routes_file != NULL);

  FILE* output_sorted_file = fopen(output_sorted_file_FILEPATH, "w");
  assert(output_sorted_file != NULL);

  client_program(airports_sorted_file, routes_file, output_sorted_file);

  fclose(airports_sorted_file);
  fclose(output_sorted_file);

  // Random airports file
  printf("\n~~~~~~~~~ Random Airports File ~~~~~~~~~~\n");
  FILE* airports_random_file = fopen(RANDOM_FILEPATH, "r");
  assert(airports_random_file != NULL);

  FILE* output_random_file = fopen(output_random_file_FILEPATH, "w");
  assert(output_random_file != NULL);

  client_program(airports_random_file, routes_file, output_random_file);

  fclose(airports_random_file);
  fclose(routes_file);
  fclose(output_random_file);

  return 0;
}

int insert_elements_to_evr(IndexNodep E,
                           FILE* airports_file,
                           FILE* output_file) {
  TElementIndex elem;

  // total time elapsed
  struct timeval t_start, t_end;

  double time_elapsed;

  // count time intervals for 2^N - 1 elements
  // where N = 9, 10, 11, 12.
  struct timeval t_start_9, t_end_9;
  struct timeval t_start_10, t_end_10;
  struct timeval t_start_11, t_end_11;
  struct timeval t_start_12, t_end_12;

  double time_elapsed_9 = 0;
  double time_elapsed_10 = 0;
  double time_elapsed_11 = 0;
  double time_elapsed_12 = 0;

  int count_elements = 1;

  // start timers
  gettimeofday(&t_start, NULL);
  gettimeofday(&t_start_9, NULL);
  gettimeofday(&t_start_10, NULL);
  gettimeofday(&t_start_11, NULL);
  gettimeofday(&t_start_12, NULL);

  while (!feof(airports_file)) {
    // start timers
    if (count_elements % 511 == 0) {
      gettimeofday(&t_end_9, NULL);

      time_elapsed_9 += ((t_end_9.tv_sec - t_start_9.tv_sec) / 1000.0) +
                        ((t_end_9.tv_usec - t_start_9.tv_usec) / 1000.0);

      gettimeofday(&t_start_9, NULL);
    } else if (count_elements % 1023 == 0) {
      gettimeofday(&t_end_10, NULL);

      time_elapsed_10 += ((t_end_10.tv_sec - t_start_10.tv_sec) / 1000.0) +
                         ((t_end_10.tv_usec - t_start_10.tv_usec) / 1000.0);

      gettimeofday(&t_start_10, NULL);
    } else if (count_elements % 2047 == 0) {
      gettimeofday(&t_end_11, NULL);

      time_elapsed_11 += ((t_end_11.tv_sec - t_start_11.tv_sec) / 1000.0) +
                         ((t_end_11.tv_usec - t_start_11.tv_usec) / 1000.0);

      gettimeofday(&t_start_11, NULL);
    } else if (count_elements % 4095 == 0) {
      gettimeofday(&t_end_12, NULL);

      time_elapsed_12 += ((t_end_12.tv_sec - t_start_12.tv_sec) / 1000.0) +
                         ((t_end_12.tv_usec - t_start_12.tv_usec) / 1000.0);

      gettimeofday(&t_start_12, NULL);
    }

    TEIndex_readValue(airports_file, &elem);
    int ret = Index_insert(E, elem);
    if (ret != 0) {
      return -1;
    }

    count_elements++;
  }

  // Reduced by 1 because of the last iteration due to the EOF
  count_elements--;

  gettimeofday(&t_end, NULL);
  time_elapsed = ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                 ((t_end.tv_usec - t_start.tv_usec) / 1000.0);

  fprintf(output_file, "Insert Elements to Evr\n");
  fprintf(output_file, "----------------------\n");
  fprintf(output_file, "Total time elapsed: %g ms\n", time_elapsed);
  fprintf(output_file,
          "Mean time per 511  elements: %g ms\n",
          time_elapsed_9 / floor(count_elements / 511));
  fprintf(output_file,
          "Mean time per 1023 elements: %g ms\n",
          time_elapsed_10 / floor(count_elements / 1023));
  fprintf(output_file,
          "Mean time per 2047 elements: %g ms\n",
          time_elapsed_11 / floor(count_elements / 2047));
  fprintf(output_file,
          "Mean time per 4095 elements: %g ms\n",
          time_elapsed_12 / floor(count_elements / 4095));
  fprintf(output_file, "Total elements inserted: %d\n", count_elements);

  return 0;
}

int update_arrivals_departures(IndexNodep E,
                               FILE* routes_file,
                               FILE* output_file) {
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

  int search_counter = 0;
  int found_counter = 0;
  int not_found_counter = 0;

  // Time Capture
  struct timeval t_start, t_end;

  double elapsed_time = 0;
  double elapsed_time_found = 0;

  // Start from the beginning of the file -- maybe you have read it before and
  // it is still open
  fseek(routes_file, 0, SEEK_SET);

  while (!feof(routes_file)) {
    // Process a line
    if (fgets(line, sizeof(line), routes_file)) {
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

      // Start timer
      gettimeofday(&t_start, NULL);

      // Search for source airport in the RBT
      Index_search(E, source_airport_id, 1, &found);

      // Stop timer
      gettimeofday(&t_end, NULL);

      elapsed_time += ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                      ((t_end.tv_usec - t_start.tv_usec) / 1000.0);

      if (found == 1) {
        found_counter++;
        elapsed_time_found += ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                              ((t_end.tv_usec - t_start.tv_usec) / 1000.0);
      } else {
        not_found_counter++;
      }

      // Start timer
      gettimeofday(&t_start, NULL);

      // Search for the destination airport in the RBT
      Index_search(E, destination_airport_id, 0, &found);

      // Stop timer
      gettimeofday(&t_end, NULL);

      elapsed_time += ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                      ((t_end.tv_usec - t_start.tv_usec) / 1000.0);

      if (found == 1) {
        found_counter++;
        elapsed_time_found += ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                              ((t_end.tv_usec - t_start.tv_usec) / 1000.0);
      } else {
        not_found_counter++;
      }

      search_counter++;

      // Free Strings that hold route fields
      free(airline);
      free(source_airport);
      free(destination_airport);
      free(codeshare);
      free(equipment);

      search_counter++;
    }
  }

  // Stop timer
  gettimeofday(&t_end, NULL);

  // Store Information in OUTPUTRandomBST.txt
  fprintf(output_file, "\nUpdate Arrivals and Departures\n");
  fprintf(output_file, "------------------------------\n");
  fprintf(output_file, "Total time elapsed: %g ms\n", elapsed_time);
  fprintf(output_file,
          "Mean time per route: %g ms\n",
          elapsed_time / search_counter);
  fprintf(output_file,
          "Mean time per found route: %g ms\n",
          elapsed_time_found / search_counter);
  fprintf(output_file, "Search counter: %d\n", search_counter);
  fprintf(output_file, "Found counter: %d\n", found_counter);
  fprintf(output_file, "Not found counter: %d\n", not_found_counter);

  return 0;
}

int print_elements_to_file(IndexNodep E, FILE* file) {
  // Time Capture
  struct timeval t_start, t_end;

  // Start timer
  gettimeofday(&t_start, NULL);

  // Count the elements that will be printed
  int element_counter;

  int print_result = Index_printAll(E, file, &element_counter);

  if (print_result != 0) {
    return -1;
  }

  // Stop timer
  gettimeofday(&t_end, NULL);

  double elapsed_time = ((t_end.tv_sec - t_start.tv_sec) / 1000.0) +
                        ((t_end.tv_usec - t_start.tv_usec) / 1000.0);

  fprintf(file, "\nTotal time elapsed: %g ms\n", elapsed_time);
  fprintf(file, "Total elements printed: %d", element_counter);

  return 0;
}

int client_program(FILE* airports_file, FILE* routes_file, FILE* output_file) {
  // Construct the Evr
  IndexNodep E = Index_construct(7200);

  // Insert elements to the Evr from file
  int result_insert = insert_elements_to_evr(E, airports_file, output_file);

  switch (result_insert) {
  case 0:
    printf("Elements inserted to Evr successfully.\n");
    break;
  case -1:
    printf("Insertion in the RBT of the Evr failed.\n");
    break;
  default:
    assert(0);
    break;
  }

  // Update arrivals and departures from routes_file file and print to output
  // file
  int result_update = update_arrivals_departures(E, routes_file, output_file);

  switch (result_update) {
  case 0:
    printf("Arrivals and departures updated successfully.\n");
    break;
  default:
    assert(0);
    break;
  }

  // Print elements and log data to the output file
  int result_print = print_elements_to_file(E, output_file);

  switch (result_print) {
  case 0:
    printf("Elements printed to file successfully.\n");
    break;
  case -1:
    printf("Error: Elements could not be printed to file.\n");
    break;
  default:
    assert(0);
    break;
  }

  // Destruct the Evr
  int result_destruct = Index_destruct(&E);

  switch (result_destruct) {
  case 0:
    printf("Evr destructed successfully.\n");
    break;
  default:
    assert(0);
    break;
  }

  return 0;
}