#include "../tree/tree.h"
#include <stdio.h>
#include <assert.h>
#include "../io/io.h"
#include "../main.h"
#include "akinator.h"
#include "../speak/speak.h"
#include <string.h>
#include <iostream>

static Node * question(Node *node);

static Node * find_leaf(Node *node);

static void ansver_not_found(Node *node);

static int check_leaf(Node *node);

void akinator(Node *tree) {
    assert(tree != nullptr);

    Node *leaf = find_leaf(tree);

    int ansver = check_leaf(leaf);

    if (ansver == NO) {
        ansver_not_found(leaf);
    }

    speak("спасибо за игру");
    printf("спасибо за игру.\n");
}

static Node * question(Node *node) {
    assert(node != nullptr);

    speak("это %s?", node->info);

    printf("это %s?\n%d - Да\n%d - Нет\n", node->info, YES, NO);
    
    int ansver = 0;

    if (scanf("%d", &ansver) != 1) {
        printf("Ответ не прочитан.\n");
        clear_buffer();
        return nullptr;
    }

    if (ansver == YES) {
        return node->right;
    }
    else if (ansver == NO) {
        return node->left;
    }
    else {
        printf("Ответ не распознан.\n");
        return nullptr;
    }

    return nullptr;
}

static Node * find_leaf(Node *node) {
    while (!is_leaf(node)) {
        Node *next_node = question(node);

        if (next_node == nullptr) {
            printf("попробуй снова.\n");
            continue;
        }
        else {
            node = next_node;
        }
    }

    return node;
}

static void ansver_not_found(Node *node) {
    speak( "я не справился со своей задачей, подскажи что ты загадал.");
    printf("я не справился со своей задачей, подскажи что ты загадал.\n");

    Node *new_node = (Node *)calloc(1, sizeof(Node));
    init_node(new_node);

    Node *new_leaf = (Node *)calloc(1, sizeof(Node));
    init_node(new_leaf);

    clear_buffer();
    get_line_n(new_leaf->info, MAX_INFO_SIZE);

    speak( "а чем отличается от %s?", node->info);
    printf("а чем отличается от %s?\n", node->info);

    get_line_n(new_node->info, MAX_INFO_SIZE);

    tree_insert(node, new_node);

    new_node->right = new_leaf;
    new_leaf->father = new_node;
}

int check_leaf(Node *node) {
    int ansver = 0;

    speak("это %s?", node->info);

    while (true) {
        printf("это %s?\n%d - Да\n%d - Нет\n", node->info, YES, NO);

        if (scanf("%d", &ansver) != 1) {
            printf("ответ не прочитался.\nпопробуй снова.\n");
            clear_buffer();
            continue;
        }

        if (ansver == YES) {
            break;
        }
        else if (ansver == NO) {
            break;
        }
    }

    return ansver;
}