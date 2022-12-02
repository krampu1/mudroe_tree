#include "../tree/tree.h"
#include "../io/io.h"
#include "../speak/speak.h"
#include <stdio.h>
#include <string.h>
#include <random>

std::mt19937 rnd(1337);

const size_t COUNT_SEP_PHRASE = 3;

const char * sep[COUNT_SEP_PHRASE] = {
    "и",
    "а также",
    "для разнообразия",
};

static void print_info(Node *node);

void wiki(Node *tree) {
    speak("о ком вы хотели узнать?");
    printf("кого искать?\n");

    char *info = (char *)calloc(1, MAX_INFO_SIZE);
    assert(info != nullptr);
    clear_buffer();
    get_line_n(info, MAX_INFO_SIZE);

    Node *leaf = find_leaf(tree, info);
    
    if (leaf == nullptr) {
        speak("примите мои извинения.");
        printf("я не нашёл ничего о %s в своей базе\n", info);
    }
    else {
        print_info(leaf);
    }
}

static void print_info(Node *node) {
    char *info = (char *)calloc(1, MAX_PHRASE_SIZE);
    assert(info != nullptr);
    char *ptr = info;
    int n = 0;

    sprintf(ptr, "%s это %n", node->info, &n);
    ptr += n;

    printf("%s это - ", node->info);

    while (node != nullptr && node->father != nullptr) {
        if (node->father->left == node) {
            sprintf(ptr, " не %n", &n);
            ptr += n;

            printf("не ");   
        }

        sprintf(ptr, "%s %n", node->father->info, &n);
        ptr += n;

        printf("%s", node->father->info);

        if (node->father->father != nullptr) {
            sprintf(ptr, ", %s %n", sep[((int)rnd())%COUNT_SEP_PHRASE], &n);
            ptr += n;
        }

        node = node->father;
    }
    sprintf(ptr, ".");

    speak("%s", info);

    printf(".\n");

    free(info);
}