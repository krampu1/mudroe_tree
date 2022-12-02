#ifndef TREEH
#define TREEH

#include <cstddef>

const size_t MAX_INFO_SIZE = 201;

struct Node {
    Node *right;
    Node *left;

    Node *father;

    char info[MAX_INFO_SIZE];
};

Node * create_vertex_right(Node *node, const char info[MAX_INFO_SIZE]);

Node * create_vertex_left(Node *node, const char info[MAX_INFO_SIZE]);

void del_node(Node *node);

void init_node(Node *node);

void init_tree(Node *root);

bool is_leaf(Node *node);

void tree_insert(Node *node, Node *new_node);

Node * find_leaf(Node *node, const char *info);

#endif