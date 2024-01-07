#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

int main() {
  Treep T = RBT_create_tree();
  Nodep nd;
  int return_value;

  char answer = '_';
  int key;

  while(answer != 'q') {
    printf("\n--------------------------------------------------------------\n");
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
    printf("\n--------------------------------------------------------------\n");

    switch(answer) {
      case 'i':
        printf("\nInsert an element in the RBT");
        printf("\nGive the key of the element: ");
        scanf("%d", &key);
        getchar();

        nd = RBT_create_node(key, RED);
        RBT_insert(T, nd);

        break;
      case 'd':
        printf("\nDelete an element from the RBT");
        printf("\nGive the key of the element: ");
        scanf("%d", &key);
        getchar();

        nd = RBT_search(T, key);

        if(nd == T->nil) {
          printf("Element not found\n");
          break;
        }

        return_value = RBT_delete(T, nd);

        switch(return_value) {
          case 0:
            printf("Element deleted successfully\n");
            break;
          case -1:
            printf("RBT is empty\n");
            break;

          default:
            break;
        }

        break;
      case 'p':
        printf("\nPrint the RBT");

        return_value = RBT_print_tree(T);

        switch(return_value) {
          case 0:
            printf("\nRBT printed successfully\n");
            break;
          case -1:
            printf("\nRBT is empty\n");
            break;
        }

        break;
      case 'q':

        break;
      default:
        printf("\nInvalid input, please try again.\n");
    }
  }

  printf("\nThe program has halted.");

  return 0;
}