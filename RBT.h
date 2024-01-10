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

#ifndef RBT
#define RBT

typedef struct RBT_node *Nodep;
typedef struct RBT_tree *Treep;

enum color { RED, BLACK };

struct RBT_tree {
  Nodep root;
  Nodep nil;
};

struct RBT_node {
  void *key;
  enum color color;
  Nodep p;
  Nodep right;
  Nodep left;
};

/*
Description: Creates an empty RBT struct and return a pointer to it. It
also creates the nil node (sentinel) and assigns black color to it. The
root of the RBT initially points to the sentinel node. Also, the root parent
remains the sentinel node.

Return values:
  - Treep: The RBT created.

Asserts:
  - malloc returns successfully.
*/
Treep RBT_create_tree();

/*
Description: Deletes the RBT T.

Parameters:
  - T (Treep): The RBT to be deleted.

Return values:
  - 0: Success.

Asserts:
  - T != NULL.
  - T->nil != NULL.
*/
int RBT_delete_tree(Treep T);

/*
Description: Creates an RBT node with the key parameter and inserts it
in the RBT T.

Parameters:
  - T (Treep): The RBT.
  - key (void *): The key of the node to be inserted.
  - comparator (int (*)(const void *, const void *)): The pointer to the
    function that compares the data. It is expected to return the following
    values:
      - -1: The data of the first node is smaller than the data of the second
        node.
      - 0: The data of the first node is equal to the data of the second node.
      - 1: The data of the first node is greater than the data of the second
        node.

Return values:
  - 0: Success
  - -1: z failed to be allocated.
*/
int RBT_insert(Treep T,
               void *key,
               int (*comparator)(const void *, const void *));

/*
Description: Removes the node with key denoted by the parameter key from the
RBT T. Also, it frees the memory allocated for the node when it was inserted in
the RBT T, through the RBT_insert function.

Parameters:
  - T (Treep): The root of the RBT.
  - key (void *): The key of the node to be deleted.
  - comparator (int (*)(const void *, const void *)): The pointer to the
    function that compares the data. It is expected to return the following
    values:
      - -1: The data of the first node is smaller than the data of the second
        node.
      - 0: The data of the first node is equal to the data of the second node.
      - 1: The data of the first node is greater than the data of the second
        node.


Return values:
  - 0: Success.
  - -1: Node was not found in the RBT T.
*/
int RBT_delete(Treep T,
               void *key,
               int (*comparator)(const void *, const void *));

/*
Description: Prints the RBT T.

Parameters:
  - T (Treep): The RBT to be printed.
  - printer (void (*)(const char *, const void *)): The pointer to the function
    that prints the key of the node.

Return values:
  - 0: Success.
  - -1: T is empty.
*/
int RBT_print_tree(Treep T, void (*printer)(const char *, const void *));

#endif