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

Nodep T_nil;

Nodep RBT_create_node(int key, enum color color);
void RBT_inorder_tree_walk(Nodep root, int space);
void RBT_print_tree(Nodep root);
Nodep RBT_search_recursive(Nodep root, int key);
Nodep RBT_minimum(Nodep root);
void RBT_left_rotate(Nodep *root, Nodep x);
void RBT_right_rotate(Nodep *root, Nodep x);
void RBT_insert_fixup(Nodep *root, Nodep z);
void RBT_insert(Nodep *root, Nodep z);
void RBT_transplant(Nodep *root, Nodep u, Nodep v);
void RBT_delete_fixup(Nodep *root, Nodep x);
int RBT_delete(Nodep *root, Nodep z);

#endif