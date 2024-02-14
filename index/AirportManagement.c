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

int main() {
  EvrPtr E;

  E = Evr_construct(7200);

  insert_elements_to_evr(E);

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