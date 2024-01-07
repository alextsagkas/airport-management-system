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

Treep RBT_create_tree();
int RBT_delete_tree(Treep T);

Nodep RBT_create_node(int key, enum color color);
int RBT_delete_node(Nodep z);

Nodep RBT_search(Treep T, int key);

int RBT_insert(Treep T, Nodep z);
int RBT_delete(Treep T, Nodep z);

int RBT_print_tree(Treep T);

#endif