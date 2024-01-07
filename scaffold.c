#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

int main() {
  T_nil = RBT_create_node(-1, BLACK);

  Nodep root = T_nil;

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

        RBT_insert(&root, RBT_create_node(key, RED));

        break;
      case 'd':
        printf("\nDelete an element from the RBT");
        printf("\nGive the key of the element: ");
        scanf("%d", &key);
        getchar();

        Nodep nd = RBT_search_recursive(root, key);
        int value = RBT_delete(&root, nd);

        switch(value) {
          case 0:
            printf("\nElement deleted successfully\n");
            break;
          case -1:
            printf("\nRBT is empty\n");
            break;

          default:
            break;
        }

        break;
      case 'p':
        printf("\nPrint the RBT");
        RBT_print_tree(root);
        printf("\n");

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