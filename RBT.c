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

#include "rbt.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Terminal Colors
#define KRED "\x1B[31m"
#define KRESET "\x1b[0m"

enum color { RED, BLACK };

// Struct representing a RBT
struct RBT_tree {
  Nodep root;
  Nodep nil;
};

// Struct representing a RBT node
struct RBT_node {
  void* key;
  enum color color;
  Nodep p;
  Nodep right;
  Nodep left;
};

Treep RBT_create_tree(void) {
  Treep T = (Treep)malloc(sizeof(struct RBT_tree));
  assert(T != NULL);

  T->nil = (Nodep)malloc(sizeof(struct RBT_node));
  assert(T->nil != NULL);
  T->nil->color = BLACK;

  T->root = T->nil;
  T->root->p = T->nil;

  return T;
}

int RBT_delete_tree(Treep T) {
  assert(T != NULL);
  assert(T->nil != NULL);

  free(T->nil);
  T->nil = NULL;

  free(T);
  T = NULL;

  return 0;
}

/*
Description: Creates an RBT node with the key parameter.

Parameters:
  - key (void *): The key of the node to be created.

Return values:
  - Nodep: The node created.

Asserts:
  - malloc returns successfully.
*/
Nodep RBT_create_node(void* key) {
  Nodep nd = (Nodep)malloc(sizeof(struct RBT_node));
  assert(nd != NULL);

  nd->key = key;
  nd->p = NULL;
  nd->right = NULL;
  nd->left = NULL;

  return nd;
}

/*
Description: Deletes the RBT node z.

Parameters:
  - z (Nodep): The node to be deleted.

Return values:
  - 0: Success.

Asserts:
  - z != NULL.
*/
int RBT_delete_node(Nodep z) {
  assert(z != NULL);

  free(z);
  z = NULL;

  return 0;
}

/*
Description: Prints the RBT T in the terminal with colorful output. It uses
inorder tree walk to achieve this, as the name suggests.

Parameters:
  - T (Treep): The RBT.
  - root (Nodep): The root of the RBT.
  - space (int): The space from the beginning of the line.
  - print (void (*)(const char *, const void *)): The pointer to the function
    that prints the key of the node. It is expected to print the data of the
    node with the terminal color that the first parameter of the function
    indicates.
*/
void RBT_inorder_tree_walk(Treep T,
                           Nodep root,
                           int space,
                           void (*print)(const char*, const void*)) {
  // This values might have changed in RB_delete.
  // However, they do not need to remain this way.
  T->nil->right = NULL;
  T->nil->left = NULL;

  Nodep tmp = root;

  // Space between nodes.
  int space_increment = 8;

  if (tmp != NULL) {
    space += space_increment;

    RBT_inorder_tree_walk(T, tmp->right, space, print);

    printf("\n");
    int i;
    for (i = space_increment; i < space; i++)
      printf(" ");

    if (tmp == T->nil)
      printf("%sL", KRESET);
    else if (tmp->color == BLACK)
      print(KRESET, tmp->key);
    else
      print(KRED, tmp->key);
    RBT_inorder_tree_walk(T, tmp->left, space, print);
  }
}

int RBT_print_tree(Treep T, void (*print)(const char*, const void*)) {
  if (T->root == T->nil) {
    return -1;
  }

  RBT_inorder_tree_walk(T, T->root, 0, print);

  return 0;
}

/*
Description: Searches the RBT T for the node with key denoted by the parameter
key. It uses the compare function to compare the keys of the nodes.

Parameters:
  - T (Treep): The RBT.
  - key (void *): The key of the node to be searched.
  - compare (int (*)(const void *, const void *)): The pointer to the
    function that compares the data. It is expected to return the following
    values:
      - -1: The data of the first node is smaller than the data of the second
        node.
      - 0: The data of the first node is equal to the data of the second node.
      - 1: The data of the first node is greater than the data of the second
        node.

Return value:
  - Nodep: The node with key denoted by the parameter key. If the node is not
    found, then it returns T->nil.
*/
Nodep RBT_search(Treep T,
                 void* key,
                 int (*compare)(const void*, const void*)) {
  Nodep tmp = T->root;

  while (tmp != T->nil && !(compare(tmp->key, key) == 0)) {
    if (compare(tmp->key, key) == 1)
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }

  return tmp;
}

/*
Description: Returns the node with the minimum key in the RBT T.

Parameters:
  - T (Treep): The RBT.
  - root (Nodep): The root of the RBT.

Return value:
  - Nodep: The node with the minimum key in the RBT T. If the RBT is empty, then
    it returns T->nil.
*/
Nodep RBT_minimum(Treep T, Nodep root) {
  if (root == T->nil) {
    return root;
  } else {
    while (root->left != T->nil) {
      root = root->left;
    }
    return root;
  }
}

/*
Description: It performs a left rotation on node x of the RBT T.

Parameters:
  - T (Treep): The RBT.
  - x (Nodep): The node to be rotated.
*/
void RBT_left_rotate(Treep T, Nodep x) {
  Nodep y = x->right;

  x->right = y->left;
  if (y->left != T->nil)
    y->left->p = x;

  y->p = x->p;
  if (x->p == T->nil)
    T->root = y;
  else if (x->p->left == x)
    x->p->left = y;
  else
    x->p->right = y;

  y->left = x;
  x->p = y;
}

/*
Description: It performs a right rotation on node x of the RBT T.

Parameters:
  - T (Treep): The RBT.
  - x (Nodep): The node to be rotated.
*/
void RBT_right_rotate(Treep T, Nodep x) {
  Nodep y = x->left;

  x->left = y->right;
  if (y->right != T->nil)
    y->right->p = x;

  y->p = x->p;
  if (x->p == T->nil)
    T->root = y;
  else if (x->p->left == x)
    x->p->left = y;
  else
    x->p->right = y;

  y->right = x;
  x->p = y;
}

/*
Description: It fixes the RBT T after an insertion of a node z,
so as that the RBT properties are not violated.

Parameters:
  - T (Treep): The RBT.
  - z (Nodep): The node that was inserted.
*/
void RBT_insert_fixup(Treep T, Nodep z) {
  Nodep y;

  while (z->p->color == RED) {
    if (z->p == z->p->p->left) {
      y = z->p->p->right;

      if (y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if (z->p->right == z) {
          z = z->p;
          RBT_left_rotate(T, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        RBT_right_rotate(T, z->p->p);
      }
    } else {
      y = z->p->p->left;

      if (y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if (z->p->left == z) {
          z = z->p;
          RBT_right_rotate(T, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        RBT_left_rotate(T, z->p->p);
      }
    }
  }
  (T->root)->color = BLACK;
}

int RBT_insert(Treep T,
               void* key,
               int (*compare)(const void*, const void*)) {

  Nodep z = RBT_create_node(key);

  if (z == NULL)
    return -1;

  Nodep y = T->nil;
  Nodep x = T->root;

  while (x != T->nil) {
    y = x;
    if (compare(z->key, x->key) == -1)
      x = x->left;
    else
      x = x->right;
  }

  z->p = y;

  if (y == T->nil)
    T->root = z;
  else if (compare(z->key, y->key) == -1)
    y->left = z;
  else
    y->right = z;

  z->left = T->nil;
  z->right = T->nil;
  z->color = RED;

  RBT_insert_fixup(T, z);

  return 0;
}

/*
Description: It performs a transplant of node u with node v of the RBT T.

Parameters:
  - T (Treep): The RBT.
  - u (Nodep): The node to be replaced.
  - v (Nodep): The node to replace with.
*/
void RBT_transplant(Treep T, Nodep u, Nodep v) {
  if (u->p == T->nil)
    T->root = v;
  else if (u->p->right == u)
    u->p->right = v;
  else
    u->p->left = v;

  v->p = u->p;
}

/*
Description: It fixes the RBT T after a deletion of a node x,
so as that the RBT properties are not violated.

Parameters:
  - T (Treep): The RBT.
  - x (Nodep): The node that was deleted.
*/
void RBT_delete_fixup(Treep T, Nodep x) {
  Nodep w;

  while (x != T->root && x->color == BLACK) {
    if (x == x->p->left) {
      w = x->p->right;

      if (w->color == RED) {
        x->p->color = RED;
        w->color = BLACK;
        RBT_left_rotate(T, x->p);
        w = x->p->right;
      }

      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          RBT_right_rotate(T, w);
          w = x->p->right;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->right->color = BLACK;
        RBT_left_rotate(T, x->p);
        x = T->root;
      }
    } else {
      w = x->p->left;

      if (w->color == RED) {
        x->p->color = RED;
        w->color = BLACK;
        RBT_right_rotate(T, x->p);
        w = x->p->left;
      }

      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          RBT_left_rotate(T, w);
          w = x->p->left;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->left->color = BLACK;
        RBT_right_rotate(T, x->p);
        x = T->root;
      }
    }
  }
  x->color = BLACK;
}

void* RBT_delete(Treep T,
                 void* key,
                 int (*compare)(const void*, const void*)) {
  Nodep z = RBT_search(T, key, compare);

  if (z == T->nil) {
    return NULL;
  }

  Nodep y = z;
  enum color y_original_color = y->color;

  Nodep x;

  if (z->left == T->nil) {
    x = z->right;
    RBT_transplant(T, z, z->right);
  } else if (z->right == T->nil) {
    x = z->left;
    RBT_transplant(T, z, z->left);
  } else {
    y = RBT_minimum(T, z->right);
    y_original_color = y->color;
    x = y->right;

    if (y->p == z)
      x->p = y;
    else {
      RBT_transplant(T, y, y->right);
      y->right = z->right;
      y->right->p = y;
    }

    RBT_transplant(T, z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
  }

  if (y_original_color == BLACK)
    RBT_delete_fixup(T, x);

  void* data = z->key;

  RBT_delete_node(z);

  return data;
}
