/*
author: Alexadros Tsagkaropoulos

References:

 - Introduction to Algorithms, Third Edition
 by Thomas H. Cormen, Charles E. Leiserson,
 Ronald L. Rivest and Clifford Stein.
 - Programming Language Principles and Programming Techniques notes
 from M.Sc. in Control and Computing taught by Ioannis Kotronis.
 - The Practice of Computer Programming, Second Edition
 by Brian W. Kernighan and Rob Pike.
*/

#include <stdio.h>

#include "int.h"
#include "rbt.h"

int main() {
  // BRT where tests are done
  Treep T = RBT_create_tree();

  // Helper variables
  int return_value;
  void* return_node;
  key_intp int_data;

  // User input
  char answer = '_';
  int int_key;

  printf("\n--------------------------------------------------------------\n");
  printf("\nCreate the RBT\n");

  while (answer != 'q') {
    printf(
        "\n--------------------------------------------------------------\n");
    printf("Previous answer was: %c\n", answer);
    printf("Choose from the following options:\n");
    printf(" i: Insert an element in the RBT\n");
    printf(" d: Delete an element from the RBT\n");
    printf(" p: Print the RBT\n");
    printf(" q: Quit the program\n");
    printf("Give a new choice: ");

    fflush(stdin);
    answer = getchar();
    getchar();

    printf("The new answer is: %c", answer);
    printf(
        "\n--------------------------------------------------------------\n");

    switch (answer) {
    case 'i':
      printf("\nInsert an element in the RBT");
      printf("\nGive the key of the element: ");
      scanf("%d", &int_key);
      getchar();

      int_data = create_int_key(int_key);

      RBT_insert(T, (void*)int_data, int_comparator);

      break;
    case 'd':
      printf("\nDelete an element from the RBT");
      printf("\nGive the key of the element: ");
      scanf("%d", &int_key);
      getchar();

      int_data = create_int_key(int_key);

      return_node = RBT_delete(T, (void*)int_data, int_comparator);

      delete_int_key(int_data);

      if (return_node != NULL) {
        printf("Node removed successfully from the RBT\n");

        return_value = delete_int_key(return_node);

        switch (return_value) {
        case 0:
          printf("Key strcut deleted successfully\n");
          break;
        }
      } else {
        printf("Node not found in the RBT\n");
      }

      break;
    case 'p':
      printf("\nPrint the RBT");

      return_value = RBT_print_tree(T, int_printer);

      switch (return_value) {
      case 0:
        printf("\nRBT printed successfully\n");
        break;
      case -1:
        printf("\nRBT is empty\n");
        break;
      }

      break;
    case 'q':
      printf("\nDelete the RBT\n");

      RBT_delete_tree(T);

      break;
    default:
      printf("\nInvalid input, please try again.\n");
    }
  }

  printf("\n--------------------------------------------------------------\n");
  printf("\nThe program has halted.");

  return 0;
}