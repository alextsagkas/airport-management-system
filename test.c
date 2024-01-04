#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum color { red, black };

typedef struct RB_Tree *Node;

struct RB_Tree {
  int key;
  enum color color;
  struct RB_Tree *p;
  struct RB_Tree *right;
  struct RB_Tree *left;
};

Node createNode(int key, enum color color) {
  Node nd = (Node)malloc(sizeof(struct RB_Tree));

  nd->key = key;
  nd->color = color;
  nd->p = NULL;
  nd->right = NULL;
  nd->left = NULL;

  return nd;
}

int main() {
  char choice;
  scanf("%c", &choice);

  enum color color = (choice == 'r') ? red : black;

  Node test_node = createNode(-1, color);

  printf("%d\n", test_node->key);
  printf("%d\n", test_node->color);

  return 0;
}