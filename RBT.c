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
  free(T);

  return 0;
}

Nodep RBT_create_node(void *key, enum color color) {
  Nodep nd = (Nodep)malloc(sizeof(struct RBT_node));
  assert(nd != NULL);

  nd->key = key;
  nd->color = color;
  nd->p = NULL;
  nd->right = NULL;
  nd->left = NULL;

  return nd;
}

int RBT_delete_node(Nodep z) {
  assert(z != NULL);

  free(z);

  return 0;
}

void RBT_inorder_tree_walk(Treep T,
                           Nodep root,
                           int space,
                           void (*printer)(const char *, const void *)) {
  // This values might have changed in RB_delete.
  // However, they do not need to remain this way.
  T->nil->right = NULL;
  T->nil->left = NULL;

  Nodep tmp = root;

  if (tmp != NULL) {
    space += 8;

    RBT_inorder_tree_walk(T, tmp->right, space, printer);

    printf("\n");
    for (int i = 8; i < space; i++)
      printf(" ");

    if (tmp == T->nil)
      printf("%sL", KRESET);
    else if (tmp->color == BLACK)
      printer(KRESET, tmp->key);
    else
      printer(KRED, tmp->key);
    RBT_inorder_tree_walk(T, tmp->left, space, printer);
  }
}

int RBT_print_tree(Treep T, void (*printer)(const char *, const void *)) {
  if (T->root == T->nil) {
    return -1;
  }

  RBT_inorder_tree_walk(T, T->root, 0, printer);

  return 0;
}

Nodep RBT_search(Treep T,
                 void *key,
                 int (*equalizer)(const void *, const void *),
                 int (*comparator_greater)(const void *, const void *)) {
  Nodep tmp = T->root;

  while (tmp != T->nil && !equalizer(tmp->key, key)) {
    if (comparator_greater(tmp->key, key))
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }

  return tmp;
}

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
               void *key,
               int (*comparator_smaller)(const void *, const void *)) {

  Nodep z = RBT_create_node(key, RED);

  if (z == NULL)
    return -1;

  Nodep y = T->nil;
  Nodep x = T->root;

  while (x != T->nil) {
    y = x;
    if (comparator_smaller(z->key, x->key))
      x = x->left;
    else
      x = x->right;
  }

  z->p = y;

  if (y == T->nil)
    T->root = z;
  else if (comparator_smaller(z->key, y->key))
    y->left = z;
  else
    y->right = z;

  z->left = T->nil;
  z->right = T->nil;
  z->color = RED;

  RBT_insert_fixup(T, z);

  return 0;
}

void RBT_transplant(Treep T, Nodep u, Nodep v) {
  if (u->p == T->nil)
    T->root = v;
  else if (u->p->right == u)
    u->p->right = v;
  else
    u->p->left = v;

  v->p = u->p;
}

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

int RBT_delete(Treep T,
               void *key,
               int (*equalizer)(const void *, const void *),
               int (*comparator_greater)(const void *, const void *)) {
  Nodep z = RBT_search(T, key, equalizer, comparator_greater);

  if (z == T->nil) {
    return -1;
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

  RBT_delete_node(z);

  return 0;
}
