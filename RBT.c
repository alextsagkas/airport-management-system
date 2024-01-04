#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KRED "\x1B[31m"
#define KRESET "\x1b[0m"

enum color { red, black };

struct RB_Tree {
  int key;
  enum color color;
  struct RB_Tree *p;
  struct RB_Tree *right;
  struct RB_Tree *left;
};

typedef struct RB_Tree *Node;

Node T_nil;

Node createNode(int key, enum color color) {
  Node nd = (Node)malloc(sizeof(struct RB_Tree));

  nd->key = key;
  nd->color = color;
  nd->p = NULL;
  nd->right = NULL;
  nd->left = NULL;

  return nd;
}

void inorderTreeWalk(Node root, int space) {
  if(root != NULL) {
    space += 8;

    inorderTreeWalk(root->right, space);

    printf("\n");
    for(int i = 8; i < space; i++) printf(" ");

    if(root->key == -1)
      printf("%sL", KRESET);
    else if(root->color == black)
      printf("%s%d", KRESET, root->key);
    else
      printf("%s%d", KRED, root->key);

    inorderTreeWalk(root->left, space);
  }
}

void printTree(Node root) { inorderTreeWalk(root, 0); }

// Node search(Node root, int data)
// {
//     if(root->data == data || root == NULL)
//     {
//         return root;
//     }
//     else
//     {
//         if(root->data > data)
//             search(root->left, data);
//         else
//             search(root->right, data);
//     }
// }

Node searchRecursive(Node root, int key) {
  while(root->key != key || root != T_nil) {
    if(root->key > key)
      root = root->left;
    else
      root = root->right;
  }
  return root;
}

Node minimum(Node root) {
  if(root == T_nil) {
    return root;
  } else {
    while(root->left != T_nil) {
      root = root->left;
    }
    return root;
  }
}

Node maximum(Node root) {
  if(root == T_nil) {
    return root;
  } else {
    while(root->right != T_nil) {
      root = root->right;
    }
    return root;
  }
}

Node successorNode(Node nd) {
  if(nd->right != T_nil) {
    return minimum(nd->right);
  } else {
    Node y = nd->p;
    while(y->left != nd || y != T_nil) {
      nd = nd->p;
      y = nd->p;
    }
    return y;
  }
}

Node predeseccorNode(Node nd) {
  if(nd->left != T_nil) {
    return maximum(nd->left);
  } else {
    Node y = nd->p;
    while(y != T_nil && y->right != nd) {
      nd = y;
      y = y->p;
    }
    return y;
  }
}

void Left_Rotate(Node *root, Node x) {
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

void Right_Rotate(Node *root, Node x) {
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

void RB_Insert_Fixup(Node *root, Node z) {
  Node y = createNode(0, red);  // assign arbitrary color

  while(z->p->color == red) {
    if(z->p == z->p->p->left) {
      y = z->p->p->right;

      if(y->color == red) {
        z->p->color = black;
        y->color = black;
        z->p->p->color = red;
        z = z->p->p;
      } else {
        if(z->p->right == z) {
          z = z->p;
          Left_Rotate(root, z);
        }
        z->p->color = black;
        z->p->p->color = red;
        Right_Rotate(root, z->p->p);
      }
    } else {
      y = z->p->p->left;

      if(y->color == red) {
        z->p->color = black;
        y->color = black;
        z->p->p->color = red;
        z = z->p->p;
      } else {
        if(z->p->left == z) {
          z = z->p;
          Right_Rotate(root, z);
        }
        z->p->color = black;
        z->p->p->color = red;
        Left_Rotate(root, z->p->p);
      }
    }
  }
  (*root)->color = black;
}

void RB_Insert(Node *root, Node z) {
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
  z->color = red;

  RB_Insert_Fixup(root, z);
}

void deleteTree(Node root) {
  if(root != NULL) {
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
  }
}

void RB_Transplant(Node *root, Node u, Node v) {
  if(u->p == T_nil)
    *root = v;
  else if(u->p->right == u)
    u->p->right = v;
  else
    u->p->left = v;

  v->p = u->p;
}

void RB_Delete_Fixup(Node *root, Node x) {
  Node w;

  while(x != *root && x->color == black) {
    if(x == x->p->left) {
      w = x->p->right;

      if(w->color == red) {
        x->p->color = red;
        w->color = black;
        Left_Rotate(root, x->p);
        w = x->p->right;
      }

      if(w->left->color == black && w->right->color == black) {
        w->color = red;
        x = x->p;
      } else {
        if(w->right->color == black) {
          w->left->color = black;
          w->color = red;
          Right_Rotate(root, w);
          w = x->p->right;
        }

        w->color = x->p->color;
        x->p->color = black;
        w->right->color = black;
        Left_Rotate(root, x->p);
        x = *root;
      }
    } else {
      w = x->p->left;

      if(w->color == red) {
        x->p->color = red;
        w->color = black;
        Right_Rotate(root, x->p);
        w = x->p->left;
      }

      if((w->right->color == black) && w->left->color == black) {
        w->color = red;
        x = x->p;
      } else {
        if(w->left->color == black) {
          w->right->color = black;
          w->color = red;
          Left_Rotate(root, w);
          w = x->p->left;
        }

        w->color = x->p->color;
        x->p->color = black;
        w->left->color = black;
        Right_Rotate(root, x->p);
        x = *root;
      }
    }
  }
  x->color = black;
}

void RB_Delete(Node *root, Node z) {
  Node y = z;
  enum color y_original_color = y->color;

  Node x;

  if(z->left == T_nil) {
    x = z->right;
    RB_Transplant(root, z, z->right);
  } else if(z->right == T_nil) {
    x = z->left;
    RB_Transplant(root, z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;

    if(y->p == z)
      x->p = y;
    else {
      RB_Transplant(root, y, y->right);
      y->right = z->right;
      y->right->p = y;
    }

    RB_Transplant(root, z, y);
    y->left = z->left;
    y->left->p = y;
    y->color = z->color;
  }

  if(y_original_color == black) RB_Delete_Fixup(root, x);
}

int main(void) {
  Node T_nil = createNode(-1, black);
  Node root = T_nil;

  char answer = '_';
  char choice = '_';

  int key;
  enum color color;

  while(answer != 'q') {
    printf("\n--------------------------------------------------------------\n");
    printf("Previous answer was: %c\n", answer);
    printf("Choose from the following options:\n");
    printf(" i: Insert an element in the RBT\n");
    printf(" d: Delete an element from the RBT\n");
    printf(" p: Print the RBT\n");
    printf(" q: Quit the program\n");
    printf("\nGive a new choice: ");

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

        printf("Previous choice was: %c\n", choice);
        printf("Choose the color of the node from the following options:\n");
        printf(" r: Red\n");
        printf(" b: Black\n");
        printf("Give a new choice: ");

        choice = getchar();
        getchar();

        color = (choice == 'r') ? red : black;
        printf("The enum that corresponds to the color is: %d\n", color);

        printf("%d", color);

        RB_Insert(&root, createNode(key, color));
        break;
      case 'd':
        printf("\nDelete an element from the RBT");

        break;
      case 'p':
        printf("\nPrint the RBT");

        break;
      case 'q':
        printf("\nQuit the program\n");

        break;
      default:
        printf("\nInvalid input, please try again\n");
    }
  }

  printf("\nThe program has halted");

  return 0;
}

// int main() {
//   Node root, nd1, nd2, nd3, nd4, nd5, nd6, nd7, nd8, nd9, nd10, nd11, nd12, nd13, nd14, nd15, nd16, nd17, nd18, nd19,
//   nd20;

//   T_nil = createNode(-1, black);
//   root = T_nil;

//   nd1 = createNode(26, black);
//   nd2 = createNode(17, red);
//   nd3 = createNode(41, black);
//   nd4 = createNode(14, black);
//   nd5 = createNode(21, black);
//   nd6 = createNode(30, red);
//   nd7 = createNode(47, black);
//   nd8 = createNode(10, red);
//   nd9 = createNode(16, black);
//   nd10 = createNode(19, black);
//   nd11 = createNode(23, black);
//   nd12 = createNode(28, black);
//   nd13 = createNode(38, black);
//   nd14 = createNode(7, black);
//   nd15 = createNode(12, black);
//   nd16 = createNode(15, red);
//   nd17 = createNode(20, red);
//   nd18 = createNode(35, red);
//   nd19 = createNode(39, red);
//   nd20 = createNode(3, red);

//   RB_Insert(&root, nd1);
//   RB_Insert(&root, nd2);
//   RB_Insert(&root, nd3);
//   RB_Insert(&root, nd4);
//   RB_Insert(&root, nd5);
//   RB_Insert(&root, nd6);
//   RB_Insert(&root, nd7);
//   RB_Insert(&root, nd8);
//   RB_Insert(&root, nd9);
//   RB_Insert(&root, nd10);
//   RB_Insert(&root, nd11);
//   RB_Insert(&root, nd12);
//   RB_Insert(&root, nd13);
//   RB_Insert(&root, nd14);
//   RB_Insert(&root, nd15);
//   RB_Insert(&root, nd16);
//   RB_Insert(&root, nd17);
//   RB_Insert(&root, nd18);
//   RB_Insert(&root, nd19);
//   RB_Insert(&root, nd20);

//   printTree(root);
//   printf("\n\n");

//   RB_Delete(&root, nd6);
//   printTree(root);

//   return 0;
// }