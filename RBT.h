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

Nodep T_nil;

Treep RBT_create_tree();
Nodep RBT_create_node(int key, enum color color);
int RBT_print_tree(Treep T);
Nodep RBT_search(Treep T, int key);
void RBT_insert(Treep T, Nodep z);
int RBT_delete(Treep T, Nodep z);

#endif