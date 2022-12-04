#include "../tree/tree.h"
#include "download.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

static void get_file_name(char *file_name);

static void skip_spaces(FILE *file);

static void get_tree_from_file(Node *node, FILE *file);

static void get_string(char *, FILE *file);

void download(Node *tree) {
    del_node(tree->left);
    del_node(tree->right);
    init_node(tree);

    char *file_name = (char *)calloc(1, MAX_FILE_NAME_SIZE);
    assert(file_name != nullptr);

    get_file_name(file_name);
    char tmp[1000];
    
    FILE *file = fopen(file_name, "r");
    assert(file != nullptr);

    get_tree_from_file(tree, file);

    fclose(file);

    free(file_name);
}

static void get_file_name(char *file_name) {
    printf("Введите название файла.\n");

    scanf("%s", file_name);
}

static void get_tree_from_file(Node *node, FILE *file) {
    assert(node != nullptr);

    skip_spaces(file);
    assert(fgetc(file) == '{');

    skip_spaces(file);

    get_string(node->info, file);

    skip_spaces(file);
    int ch = fgetc(file);
    if (ch == '}') {
        return;
    }
    ungetc(ch, file);

    node->left  = (Node *)calloc(1, sizeof(Node));
    node->right = (Node *)calloc(1, sizeof(Node));
    init_node(node->left);
    init_node(node->right);

    node->left->father  = node;
    node->right->father = node;

    get_tree_from_file(node->right,  file);
    get_tree_from_file(node->left, file);

    skip_spaces(file);
    assert(fgetc(file) == '}');
}

static void skip_spaces(FILE *file) {
    int ch = fgetc(file);

    while (isspace(ch)) {
        ch = fgetc(file);
    }

    ungetc(ch, file);
}

static void get_string(char *str, FILE *file) {
    skip_spaces(file);
    assert(fgetc(file) == '\"');

    size_t len_size = 0;

    *str = fgetc(file);
    len_size++;

    while (*str != '\"') {
        str++;
        *str = fgetc(file);
        len_size++;
        
        assert(len_size < MAX_INFO_SIZE);
    }

    assert(*str == '\"');

    *str = '\0';
}