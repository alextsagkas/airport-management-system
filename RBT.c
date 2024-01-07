#include "RBT.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KRED "\x1B[31m"
#define KRESET "\x1b[0m"

Nodep RBT_create_node(int key, enum color color) {
  Nodep nd = (Nodep)malloc(sizeof(struct RBT_node));
  nd->key = key;
  nd->color = color;
  nd->p = NULL;
  nd->right = NULL;
  nd->left = NULL;

  return nd;
}

void RBT_inorder_tree_walk(Nodep root, int space) {
  if(root != NULL) {
    space += 8;

    RBT_inorder_tree_walk(root->right, space);

    printf("\n");
    for(int i = 8; i < space; i++) printf(" ");

    if(root->key == -1)
      printf("%sL", KRESET);
    else if(root->color == BLACK)
      printf("%s%d", KRESET, root->key);
    else
      printf("%s%d", KRED, root->key);

    RBT_inorder_tree_walk(root->left, space);
  }
}

// BUG: Print nothing when the tree is empty
void RBT_print_tree(Nodep root) { RBT_inorder_tree_walk(root, 0); }

Nodep RBT_search_recursive(Nodep root, int key) {
  while(root != T_nil && root->key != key) {
    if(root->key > key)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

Nodep RBT_minimum(Nodep root) {
  if(root == T_nil) {
    return root;
  } else {
    while(root->left != T_nil) {
      root = root->left;
    }
    return root;
  }
}

void RBT_left_rotate(Nodep *root, Nodep x) {
  Nodep y = x->right;

  x->right = y->left;
  if(y->left != T_nil) y->left->p = x;

  y->p = x->p;
  if(x->p == T_nil)
    *root = y;
  else if(x->p->left == x)
    x->p->left = y;
  else
    x->p->right = y;

  y->left = x;
  x->p = y;
}

void RBT_right_rotate(Nodep *root, Nodep x) {
  Nodep y = x->left;

  x->left = y->right;
  if(y->right != T_nil) y->right->p = x;

  y->p = x->p;
  if(x->p == T_nil)
    *root = y;
  else if(x->p->left == x)
    x->p->left = y;
  else
    x->p->right = y;

  y->right = x;
  x->p = y;
}

void RBT_insert_fixup(Nodep *root, Nodep z) {
  Nodep y = RBT_create_node(0, RED);  // arbitrary values

  while(z->p->color == RED) {
    if(z->p == z->p->p->left) {
      y = z->p->p->right;

      if(y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if(z->p->right == z) {
          z = z->p;
          RBT_left_rotate(root, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        RBT_right_rotate(root, z->p->p);
      }
    } else {
      y = z->p->p->left;

      if(y->color == RED) {
        z->p->color = BLACK;
        y->color = BLACK;
        z->p->p->color = RED;
        z = z->p->p;
      } else {
        if(z->p->left == z) {
          z = z->p;
          RBT_right_rotate(root, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        RBT_left_rotate(root, z->p->p);
      }
    }
  }
  (*root)->color = BLACK;
}

// BUG: Fix the bug that causes the node with the same key to be added more than once
void RBT_insert(Nodep *root, Nodep z) {
  Nodep y = T_nil;
  Nodep x = *root;

  while(x != T_nil) {
    y = x;
    if(z->key < x->key)
      x = x->left;
    else
      x = x->right;
  }

  z->p = y;

  if(y == T_nil)
    *root = z;
  else if(z->key < y->key)
    y->left = z;
  else
    y->right = z;

  z->left = T_nil;
  z->right = T_nil;
  z->color = RED;

  RBT_insert_fixup(root, z);
}

void RBT_transplant(Nodep *root, Nodep u, Nodep v) {
  if(u->p == T_nil)
    *root = v;
  else if(u->p->right == u)
    u->p->right = v;
  else
    u->p->left = v;

  v->p = u->p;
}

void RBT_delete_fixup(Nodep *root, Nodep x) {
  Nodep w;

  while(x != *root && x->color == BLACK) {
    if(x == x->p->left) {
      w = x->p->right;

      if(w->color == RED) {
        x->p->color = RED;
        w->color = BLACK;
        RBT_left_rotate(root, x->p);
        w = x->p->right;
      }

      if(w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if(w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          RBT_right_rotate(root, w);
          w = x->p->right;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->right->color = BLACK;
        RBT_left_rotate(root, x->p);
        x = *root;
      }
    } else {
      w = x->p->left;

      if(w->color == RED) {
        x->p->color = RED;
        w->color = BLACK;
        RBT_right_rotate(root, x->p);
        w = x->p->left;
      }

      if(w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if(w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          RBT_left_rotate(root, w);
          w = x->p->left;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->left->color = BLACK;
        RBT_right_rotate(root, x->p);
        x = *root;
      }
    }
  }
  x->color = BLACK;
}

/*
Description: Deletes a node from the RBT

Parameters:
  - root: The root of the RBT
  - z: The node to be deleted

Return values:
  - 0: Success
  - -1: z in T_nil
*/
int RBT_delete(Nodep *root, Nodep z) {
  if(z == T_nil) {
    return -1;
  }

  Nodep y = z;
  enum color y_original_color = y->color;

  Nodep x;

  if(z->left == T_nil) {
    x = z->right;
    RBT_transplant(root, z, z->right);
  } else if(z->right == T_nil) {
    x = z->left;
    RBT_transplant(root, z, z->left);
  } else {
    y = RBT_minimum(z->right);
    y_original_color = y->color;
    x = y->right;

    if(y->p == z)
      x->p = y;
    else {
      RBT_transplant(root, y, y->right);
      y->right = z->right;
      y->right->p = y;
    }

    RBT_transplant(root, z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
  }

  if(y_original_color == BLACK) RBT_delete_fixup(root, x);

  return 0;
}
