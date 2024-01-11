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
#include <string.h>

#include "int.h"
#include "rbt.h"
#include "string.h"

/*
Description: Prints a string separator.
*/
void print_separator();

/*
Description: Asks the user to choose the type of the key between
integer and string. The choice is returned as a char.

Parameters:
  - key_type (char*): The type of the key.

Return values:
  - 'i': The user chose integer.
  - 's': The user chose string.
*/
char choose_key_type();

/*
Description: Performs operations insert, delete and print on the RBT T.
It returns when the user chooses to quit the program.

Parameters:
  - T (Treep): The RBT.
  - key_type (char): The type of the key.
*/
void tree_operations(Treep T, char key_type);

int main() {
  // BRT where tests are done
  Treep T = RBT_create_tree();

  print_separator();
  printf("\nCreate the RBT\n");
  print_separator();

  // Choose the type of the key
  char key_type = choose_key_type();

  // Perform operations on the RBT
  tree_operations(T, key_type);

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

void tree_operations(Treep T, char key_type) {
  // User input
  char answer = '_';

  // Helper variables
  int return_value;
  void* key_generic;
  void* return_node;
  // int
  int int_key;
  key_intp int_data;
  // string
  char str_key[100];
  key_stringp str_data;

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

      if (key_type == 'i') {
        scanf("%d", &int_key);
        getchar();

        int_data = create_int_key(int_key);
        key_generic = (void*)int_data;

        RBT_insert(T, key_generic, int_comparator);
      } else {
        scanf("%s", str_key);
        getchar();

        printf("str_key: %s", str_key);

        str_data = create_string_key(str_key);
        key_generic = (void*)str_data;

        RBT_insert(T, key_generic, string_comparator);
      }

      break;
    case 'd':
      printf("\nDelete an element from the RBT");
      printf("\nGive the key of the element: ");

      if (key_type == 'i') {
        scanf("%d", &int_key);
        getchar();

        int_data = create_int_key(int_key);
        key_generic = (void*)int_data;

        return_node = RBT_delete(T, key_generic, int_comparator);

        delete_int_key(int_data);

        if ((return_node != NULL)) {
          printf("Node removed successfully from the RBT\n");
          delete_int_key(return_node);
        } else {
          printf("Node not found in the RBT\n");
        }
      } else {
        scanf("%s", str_key);
        getchar();

        str_data = create_string_key(str_key);
        key_generic = (void*)str_data;

        return_node = RBT_delete(T, key_generic, string_comparator);

        delete_string_key(str_data);

        if ((return_node != NULL)) {
          printf("Node removed successfully from the RBT\n");
          delete_string_key(return_node);
        } else {
          printf("Node not found in the RBT\n");
        }
      }

      break;
    case 'p':
      printf("\nPrint the RBT");

      if (key_type == 'i') {
        return_value = RBT_print_tree(T, int_printer);
      } else {
        return_value = RBT_print_tree(T, string_printer);
      }

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
