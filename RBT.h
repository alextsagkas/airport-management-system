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
  int key;
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
Description: Creates a node struct with its key and color denoted by function's parameters
and returns a pointer to it. The parent, left and right child of the node are initialized to
NULL.

Parameters:
  - key (int): The key of the node.
  - color (enum color): The color of the node.

Return values:
  - Nodep: The node created.

Asserts:
  - malloc returns successfully.
*/
Nodep RBT_create_node(int key, enum color color);

/*
Description: Deletes the node z.

Parameters:
  - z (Nodep): The node to be deleted.

Return values:
  - 0: Success

Asserts:
  - z != NULL
*/
int RBT_delete_node(Nodep z);

/*
Description: Searches for the node with key key in the RBT T.
if the node is found it is returned, else it returns the sentinel.

Parameters:
  - T (Treep): The RBT to be searched.
  - key (int): The key of the node to be searched.

Returns:
  - Nodep: The node with key key or sentinel if the node is not found. If there are
  multiple nodes with the same key, the one located in the lowest level of the RBT T
  is returned.
*/
Nodep RBT_search(Treep T, int key);

/*
Description: Inserts the node z in the RBT T. The color of the node
z can be arbitrary since it will be fixed afterwards, so as the RBT
properties to be preserved.

Parameters:
  - T (Treep): The RBT.
  - z (Nodep): The node to be inserted.

Return values:
  - 0: Success
*/
int RBT_insert(Treep T, Nodep z);

/*
Description: Removes the node z from the RBT T. It is
advised that the node z is searched with the RBT_search function.
To be completely deleted from the heap, node z must be put in
function RBT_delete_node afterwards.

Parameters:
  - T (Treep): The root of the RBT.
  - z (Nodep): The node to be deleted.

Return values:
  - 0: Success.
  - -1: z in T->nil.
*/
int RBT_delete(Treep T, Nodep z);

/*
Description: Prints the RBT T.

Parameters:
  - T (Treep): The RBT to be printed.

Return values:
  - 0: Success.
  - -1: T is empty.
*/
int RBT_print_tree(Treep T);

#endif