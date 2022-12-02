#include "../tree/tree.h"
#include "visual.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const char *dot_file_name = "file.dot";

const size_t MAX_COMMAND_SIZE = 100;

static void print_vertex(FILE *file, Node *node);

static void print_edge(FILE *file, Node *node);

void visual(Node *tree) {
    FILE *file = fopen(dot_file_name, "w");
    assert(file != nullptr);

    fprintf(file, "digraph G {style=filled;graph [splines = headport splines=ortho];\n");

    print_vertex(file, tree);

    print_edge( file, tree);

    fprintf(file, "}");

    fclose(file);

    char *command = (char *)calloc(1, MAX_COMMAND_SIZE);

    sprintf(command, "dot -Tpng %s > %s.png", dot_file_name, dot_file_name);

    system(command);

    free(command);
}

static void print_vertex(FILE *file, Node *node) {
    assert(file != nullptr);
    assert(node != nullptr);

    fprintf(file, "VERTEX%p[label=\"%s\", shape=\"Mrecord\", style = filled, fillcolor = \"#c0ffee\"]\n", node, node->info);

    if (node->left != nullptr) {
        print_vertex(file, node->left);
    }

    if (node->right != nullptr) {
        print_vertex(file, node->right);
    }
}

static void print_edge(FILE *file, Node *node) {
    assert(file != nullptr);
    assert(node != nullptr);

    if (node->left != nullptr) {
        fprintf(file, "VERTEX%p->VERTEX%p[lable=\"L\"color=\"blue\"]\n", node, node->left);

        print_edge(file, node->left);
    }

    if (node->right != nullptr) {
        fprintf(file, "VERTEX%p->VERTEX%p[lable=\"R\"color=\"red\"]\n", node, node->right);

        print_edge(file, node->right);
    }
}