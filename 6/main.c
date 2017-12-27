#include <stdlib.h>
#include "walk.h"


int main(int argc, char **argv) {
    const char *path = argc == 2 ? argv[1] : ".";

    walk(path, stdout);

    return EXIT_SUCCESS;
}