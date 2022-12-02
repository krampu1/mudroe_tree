#include "io/io.h"
#include "main.h"
#include "tree/tree.h"
#include "akinator/akinator.h"
#include "wiki/wiki.h"
#include "save/save.h"
#include "get/get.h"
#include "diff/diff.h"
#include "visual/visual.h"

int main() {
    Node tree = {0};
    init_tree(&tree);

    breaf();

    while (true) {
        unsigned int mode = get_mode();

        switch (mode) {
            case AKINATOR:
                akinator(&tree);
                break;
            case WIKI:
                wiki(&tree);
                break;
            case DIFF:
                diff(&tree);
                break;
            case VISUAL:
                visual(&tree);
                break;
            case GET:
                get(&tree);
                break;
            case SAVE:
                save(&tree);
                break;
            case EXIT:
                return 0;
                break;
            case HELP:
                help();
                break;
            default:
                printf("mode not exist\n");
                break;
        }
    }

    del_node(tree.left);
    del_node(tree.right);
}