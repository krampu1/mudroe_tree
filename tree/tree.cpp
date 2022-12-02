#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tree.h"

Node * create_vertex_right(Node *node, const char info[MAX_INFO_SIZE]) {
    assert(node != nullptr);

    Node *new_node = (Node *)calloc(sizeof(Node), 1);
    assert(new_node != nullptr);

    init_node(new_node);

    memcpy(new_node->info, info, MAX_INFO_SIZE);

    new_node->father = node;

    del_node(node->right);

    node->right = new_node;

    return new_node;
}

Node * create_vertex_left(Node *node, const char info[MAX_INFO_SIZE]) {
    assert(node != nullptr);

    Node *new_node = (Node *)calloc(sizeof(Node), 1);
    assert(new_node != nullptr);

    init_node(new_node);

    memcpy(new_node->info, info, MAX_INFO_SIZE);

    new_node->father = node;

    del_node(node->left);

    node->left = new_node;

    return new_node;
}

void del_node(Node *node) {
    if (node == nullptr) {return;}

    del_node(node->right);
    del_node(node->left);

    free(node);
}

void init_node(Node *node) {
    node = (Node *)calloc(sizeof(Node), 1);

    node->left  = nullptr;
    node->right = nullptr;

    node->father = nullptr;

    memset(&(node->info[0]), 0, MAX_INFO_SIZE);
}

void init_tree(Node *root) {
    init_node(root);

    Node *left_node  = (Node *)calloc(1, sizeof(Node));
    Node *right_node = (Node *)calloc(1, sizeof(Node));

    init_node(left_node);
    init_node(right_node);


    root->left  = left_node;
    root->right = right_node;

    left_node->father  = root;
    right_node->father = root;

    strcpy(root->info,       "животное");
    strcpy(left_node->info,  "абобус");
    strcpy(right_node->info, "1.5");
}

void set_info_node(Node *node, const char info[MAX_INFO_SIZE]) {
    assert(node != nullptr);

    memcpy(node->info, info, MAX_INFO_SIZE);
}

bool is_leaf(Node *node) {
    assert(node != nullptr);

    if (node->left == nullptr && node->right == nullptr) {
        return true;
    }
    return false;
}

void tree_insert(Node *node, Node *new_node) {
    assert(node         != nullptr);
    assert(new_node     != nullptr);
    assert(node->father != nullptr);

    if (node->father->left == node) {
        node->father->left = new_node;
    }
    else {
        node->father->right = new_node;
    }
    new_node->father = node->father;
    new_node->left   = node;
    node->father     = new_node;
}

Node * find_leaf(Node *node, const char *info) {
    assert(node != nullptr);
    assert(info != nullptr);

    if (is_leaf(node)) {
        if (strncmp(info, node->info, MAX_INFO_SIZE) == 0) {
            return node;
        }
        else {
            return nullptr;
        }
    }
    else {
        Node *ans = find_leaf(node->left, info);
        if (ans != nullptr) {
            return ans;
        }

        ans = find_leaf(node->right, info);
        if (ans != nullptr) {
            return ans;
        }
    }

    return nullptr;
}