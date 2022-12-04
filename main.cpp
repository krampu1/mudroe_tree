#include "io/io.h"
#include "main.h"
#include "tree/tree.h"
#include "akinator/akinator.h"
#include "wiki/wiki.h"
#include "upload/upload.h"
#include "download/download.h"
#include "difference/difference.h"
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
            case DIFFERENCE:
                difference(&tree);
                break;
            case VISUAL:
                visual(&tree);
                break;
            case DOWNLOAD:
                download(&tree);
                break;
            case UPLOAD:
                upload(&tree);
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