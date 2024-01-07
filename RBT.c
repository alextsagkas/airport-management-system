#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KRED "\x1B[31m"
#define KRESET "\x1b[0m"

enum color { RED, BLACK };

typedef struct RB_Tree *Node;

Node T_nil;

Node RB_create_node(int key, enum color color);
void RB_inorder_tree_walk(Node root, int space);
void RB_print_tree(Node root);
Node RB_search_recursive(Node root, int key);
Node RB_minimum(Node root);
void RB_left_rotate(Node *root, Node x);
void RB_right_rotate(Node *root, Node x);
void RB_insert_fixup(Node *root, Node z);
void RB_insert(Node *root, Node z);
void RB_transplant(Node *root, Node u, Node v);
void RB_delete_fixup(Node *root, Node x);
int RB_delete(Node *root, Node z);

int main() {
  T_nil = RB_create_node(-1, BLACK);
  Node root = T_nil;

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

        RB_insert(&root, RB_create_node(key, RED));

        break;
      case 'd':
        printf("\nDelete an element from the RBT");
        printf("\nGive the key of the element: ");
        scanf("%d", &key);
        getchar();

        Node nd = RB_search_recursive(root, key);
        int value = RB_delete(&root, nd);

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
        RB_print_tree(root);
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

struct RB_Tree {
  int key;
  enum color color;
  struct RB_Tree *p;
  struct RB_Tree *right;
  struct RB_Tree *left;
};

Node RB_create_node(int key, enum color color) {
  Node nd = (Node)malloc(sizeof(struct RB_Tree));
  nd->key = key;
  nd->color = color;
  nd->p = NULL;
  nd->right = NULL;
  nd->left = NULL;

  return nd;
}

void RB_inorder_tree_walk(Node root, int space) {
  if(root != NULL) {
    space += 8;

    RB_inorder_tree_walk(root->right, space);

    printf("\n");
    for(int i = 8; i < space; i++) printf(" ");

    if(root->key == -1)
      printf("%sL", KRESET);
    else if(root->color == BLACK)
      printf("%s%d", KRESET, root->key);
    else
      printf("%s%d", KRED, root->key);

    RB_inorder_tree_walk(root->left, space);
  }
}

// BUG: Print nothing when the tree is empty
void RB_print_tree(Node root) { RB_inorder_tree_walk(root, 0); }

Node RB_search_recursive(Node root, int key) {
  while(root != T_nil && root->key != key) {
    if(root->key > key)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

Node RB_minimum(Node root) {
  if(root == T_nil) {
    return root;
  } else {
    while(root->left != T_nil) {
      root = root->left;
    }
    return root;
  }
}

void RB_left_rotate(Node *root, Node x) {
  Node y = x->right;

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

void RB_right_rotate(Node *root, Node x) {
  Node y = x->left;

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

void RB_insert_fixup(Node *root, Node z) {
  Node y = RB_create_node(0, RED);  // arbitrary values

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
          RB_left_rotate(root, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        RB_right_rotate(root, z->p->p);
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
          RB_right_rotate(root, z);
        }
        z->p->color = BLACK;
        z->p->p->color = RED;
        RB_left_rotate(root, z->p->p);
      }
    }
  }
  (*root)->color = BLACK;
}

// BUG: Fix the bug that causes the node with the same key to be added more than once
void RB_insert(Node *root, Node z) {
  Node y = T_nil;
  Node x = *root;

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

  RB_insert_fixup(root, z);
}

void RB_transplant(Node *root, Node u, Node v) {
  if(u->p == T_nil)
    *root = v;
  else if(u->p->right == u)
    u->p->right = v;
  else
    u->p->left = v;

  v->p = u->p;
}

void RB_delete_fixup(Node *root, Node x) {
  Node w;

  while(x != *root && x->color == BLACK) {
    if(x == x->p->left) {
      w = x->p->right;

      if(w->color == RED) {
        x->p->color = RED;
        w->color = BLACK;
        RB_left_rotate(root, x->p);
        w = x->p->right;
      }

      if(w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if(w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          RB_right_rotate(root, w);
          w = x->p->right;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->right->color = BLACK;
        RB_left_rotate(root, x->p);
        x = *root;
      }
    } else {
      w = x->p->left;

      if(w->color == RED) {
        x->p->color = RED;
        w->color = BLACK;
        RB_right_rotate(root, x->p);
        w = x->p->left;
      }

      if(w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->p;
      } else {
        if(w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          RB_left_rotate(root, w);
          w = x->p->left;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->left->color = BLACK;
        RB_right_rotate(root, x->p);
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
int RB_delete(Node *root, Node z) {
  if(z == T_nil) {
    return -1;
  }

  Node y = z;
  enum color y_original_color = y->color;

  Node x;

  if(z->left == T_nil) {
    x = z->right;
    RB_transplant(root, z, z->right);
  } else if(z->right == T_nil) {
    x = z->left;
    RB_transplant(root, z, z->left);
  } else {
    y = RB_minimum(z->right);
    y_original_color = y->color;
    x = y->right;

    if(y->p == z)
      x->p = y;
    else {
      RB_transplant(root, y, y->right);
      y->right = z->right;
      y->right->p = y;
    }

    RB_transplant(root, z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
  }

  if(y_original_color == BLACK) RB_delete_fixup(root, x);

  return 0;
}
