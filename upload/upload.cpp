#include "../tree/tree.h"
#include "upload.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void write_tree_to_file(FILE *file, Node *tree);

static void get_file_name(char *file_name);

void upload(Node *tree) {
    char *file_name = (char *)calloc(1, MAX_SIZE_FILE_NAME);
    assert(file_name != nullptr);

    get_file_name(file_name);

    FILE *file = fopen(file_name, "w");

    write_tree_to_file(file, tree);

    fclose(file);

    free(file_name);
}

static void get_file_name(char *file_name) {
    assert(file_name != nullptr);

    printf("пожалуйста введите название файла, куда хотите сохранить.\n");

    scanf("%s", file_name);
}

static void write_tree_to_file(FILE *file, Node *tree) {
    assert(tree != nullptr);
    assert(file != nullptr);

    fprintf(file, "{\"%s\"", tree->info);

    if (tree->left != nullptr && tree->right != nullptr) {
        write_tree_to_file(file, tree->left);
        write_tree_to_file(file, tree->right);
    }
    
    fprintf(file, "}");
}