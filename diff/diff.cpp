#include "../tree/tree.h"
#include "../io/io.h"
#include "../speak/speak.h"
#include <stdio.h>

typedef Node * Type_t;
#define CANARY_PROT
#define HASH_PROT
#include "../stack/stack.h"

static void object_not_found(char *str);

static void print_diff(Node *first_leaf, Node *second_leaf);

static void stack_fill(Stack *stack, Node *node);

static void print_unique_info(Node *node, Stack *stack, char *object);

static bool top_equal(Stack *first, Stack *second);

void diff(Node *tree) {
    speak("что хотите сравнить?");

    printf("первый объект:\n");
    char *first_str = (char *)calloc(1, MAX_INFO_SIZE);
    assert(first_str != nullptr);
    clear_buffer();
    get_line_n(first_str, MAX_INFO_SIZE);

    Node *first_leaf  = find_leaf(tree, first_str);

    if (first_leaf == nullptr) {
        object_not_found(first_str);
        return;
    }

    printf("второй объект:\n");
    char *second_str = (char *)calloc(1, MAX_INFO_SIZE);
    assert(second_str != nullptr);
    get_line_n(second_str, MAX_INFO_SIZE);

    Node *second_leaf = find_leaf(tree, second_str);

    if (first_leaf == nullptr) {
        object_not_found(second_str);
        return;
    }

    print_diff(first_leaf, second_leaf);

    free(first_str);
    free(second_str);
}

static void object_not_found(char *str) {
    speak("я не знаю такого объекта.");
    printf("такого я нэпонимат.\n");
    free(str);
}

static void print_diff(Node *first_leaf, Node *second_leaf) { 
    Stack stack_first = {};
    stack_create(&stack_first);

    stack_fill(&stack_first, first_leaf);

    Stack stack_second = {};
    stack_create(&stack_second);

    stack_fill(&stack_second, second_leaf);

    Node *first_top  = nullptr;
    Node *second_top = nullptr;

    bool equal_exist = false;
    if (top_equal(&stack_first, &stack_second)) {
        printf("они схожи тем что: ");
        equal_exist = true;
    }

    while (top_equal(&stack_first, &stack_second)) {
        first_top =  stack_pop(&stack_first);
        second_top = stack_pop(&stack_second);

        printf("%s", first_top->info);

        if (top_equal(&stack_first, &stack_second)) {
            printf(", ");
        }
    }
    if (equal_exist) {
        printf("\n");
    }

    print_unique_info(first_top,  &stack_first,  first_leaf->info);
    print_unique_info(second_top, &stack_second, second_leaf->info);
}

static void stack_fill(Stack *stack, Node *node) {
    assert(stack != nullptr);
    assert(node  != nullptr);

    stack_push(stack, node);

    if (node->father != nullptr) {
        stack_fill(stack, node->father);
    }
}

static void print_unique_info(Node *node, Stack *stack, char *object) {
    if (node != nullptr) {
        printf("Отличительные черты %s: ", object);

        printf("%s", node->info);
    }
    else if (stack->size) {
        printf("Отличительные черты %s: %s", object, stack_pop(stack)->info);
    }

    while (stack->size) {
        printf(", %s", stack_pop(stack)->info);
    }
    printf("\n");
}

static bool top_equal(Stack *first, Stack *second) {
    if (first->size <= 1 || second->size <= 1) {
        return false;
    }

    if (first->data[first->size - 1] == second->data[second->size - 1] && 
        first->data[first->size - 2] == second->data[second->size - 2]) {
            return true;
    }

    return false;
}