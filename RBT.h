#ifndef RBT
#define RBT

typedef struct RBT_node *Nodep;

enum color { RED, BLACK };

struct RBT_node {
  int key;
  enum color color;
  struct RBT_node *p;
  struct RBT_node *right;
  struct RBT_node *left;
};

struct RBT_tree {
  Nodep root;
  Nodep nil;
};

Nodep T_nil;

Nodep RBT_create_node(int key, enum color color);
void RBT_print_tree(Nodep root);
Nodep RBT_search(Nodep root, int key);
void RBT_insert(Nodep *root, Nodep z);
int RBT_delete(Nodep *root, Nodep z);

#endif