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

#include "../int_module/int.h"
#include "../rbt_module/rbt.h"
#include "../string_module/string.h"

/*
Description: Prints a string separator.
*/
void print_separator();

/*
Description: Asks the user to choose the type of the key between
integer and string. The choice is returned as a char.

Return values:
  - 'i': The user chose integer.
  - 's': The user chose string.
*/
char choose_key_type();

/*
Description: Performs operations insert, delete and print on the RBT T
that supports int keys. It returns when the user chooses to quit the program.

Parameters:
  - T (Treep): The RBT.
*/
void int_tree_operations(Treep T);

/*
Description: Performs operations insert, delete and print on the RBT T
that supports string keys. It returns when the user chooses to quit the
program.

Parameters:
  - T (Treep): The RBT.
*/
void string_tree_operations(Treep T);

int main() {
  // BRT where tests are done
  Treep T = RBT_create_tree();

  print_separator();
  printf("\nCreate the RBT\n");
  print_separator();

  // Choose the type of the key
  char key_type = choose_key_type();

  // Perform operations on the RBT
  switch (key_type) {
  case 'i':
    int_tree_operations(T);
    break;
  case 's':
    string_tree_operations(T);
    break;
  }

  return 0;
}

void print_separator() {
  printf("\n--------------------------------------------------------------\n");
}

char choose_key_type() {
  char key_type = '_';

  while (key_type != 'i' && key_type != 's') {
    printf("Previous choice was: %c\n\n", key_type);
    printf("Choose the type of the key:\n");
    printf(" i: integer\n");
    printf(" s: string\n");
    printf("Give a new choice: ");

    fflush(stdin);
    key_type = getchar();
    getchar();

    printf("\nThe new choice is: %c", key_type);
    print_separator();

    switch (key_type) {
    case 'i':
      printf("\nInteger key chosen\n");
      break;
    case 's':
      printf("\nString key chosen\n");
      break;
    default:
      printf("\nInvalid input, please try again.\n");
      print_separator();
    }
  }

  return key_type;
}

/*
Description: Performs operations insert, delete and print on the RBT T
that supports int keys. It returns when the user chooses to quit the program.

Parameters:
  - T (Treep): The RBT.
*/
void int_tree_operations(Treep T) {
  // User input
  char answer = '_';
  int int_key;

  // Helper variables
  int return_value;
  void* return_key;
  key_intp int_data;

  while (answer != 'q') {
    print_separator();
    printf("Previous answer was: %c\n\n", answer);
    printf("Choose from the following options:\n");
    printf(" i: Insert an element in the RBT\n");
    printf(" d: Delete an element from the RBT\n");
    printf(" p: Print the RBT\n");
    printf(" q: Quit the program\n");
    printf("Give a new choice: ");

    fflush(stdin);
    answer = getchar();
    getchar();

    printf("\nThe new answer is: %c", answer);
    print_separator();

    switch (answer) {
    case 'i':
      printf("\nInsert an element in the RBT");
      printf("\nGive the key of the element: ");
      scanf("%d", &int_key);
      getchar();

      int_data = int_create_key(int_key);

      RBT_insert(T, (void*)int_data, int_compare);

      break;
    case 'd':
      printf("\nDelete an element from the RBT");
      printf("\nGive the key of the element: ");
      scanf("%d", &int_key);
      getchar();

      // Create a key struct to use it for searching the node
      // that will be deleted.
      int_data = int_create_key(int_key);

      return_key = RBT_delete(T, (void*)int_data, int_compare);

      // Delete the key struct that was used for searching.
      int_delete_key((void*)int_data);

      if (return_key != NULL) {
        printf("Node removed successfully from the RBT\n");

        // Delete the key struct that was used by the deleted node.
        return_value = int_delete_key(return_key);

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

      return_value = RBT_print_tree(T, int_print);

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

  print_separator();
  printf("\nThe program has halted.");
}

/*
Description: Performs operations insert, delete and print on the RBT T
that supports string keys. It returns when the user chooses to quit the
program.

Parameters:
  - T (Treep): The RBT.
*/
void string_tree_operations(Treep T) {
  // User input
  char answer = '_';
  char string_key[100];

  // Helper variables
  int return_value;
  void* return_key;
  key_stringp string_data;

  while (answer != 'q') {
    print_separator();
    printf("Previous answer was: %c\n\n", answer);
    printf("Choose from the following options:\n");
    printf(" i: Insert an element in the RBT\n");
    printf(" d: Delete an element from the RBT\n");
    printf(" p: Print the RBT\n");
    printf(" q: Quit the program\n");
    printf("Give a new choice: ");

    fflush(stdin);
    answer = getchar();
    getchar();

    printf("\nThe new answer is: %c", answer);
    print_separator();

    switch (answer) {
    case 'i':
      printf("\nInsert an element in the RBT");
      printf("\nGive the key of the element: ");
      fgets(string_key, 100, stdin);

      string_data = string_create_key(string_key);

      RBT_insert(T, (void*)string_data, string_compare);

      break;
    case 'd':
      printf("\nDelete an element from the RBT");
      printf("\nGive the key of the element: ");
      fgets(string_key, 100, stdin);

      // Create a key struct to use it for searching the node
      // that will be deleted.
      string_data = string_create_key(string_key);

      return_key = RBT_delete(T, (void*)string_data, string_compare);

      // Delete the key struct that was used for searching.
      string_delete_key((void*)string_data);

      if (return_key != NULL) {
        printf("Node removed successfully from the RBT\n");

        // Delete the key struct that was used by the deleted node.
        return_value = string_delete_key(return_key);

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

      return_value = RBT_print_tree(T, string_print);

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

  print_separator();
  printf("\nThe program has halted.");
}
