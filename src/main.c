#include "file_manager.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    /* Get the current path */
    char current_path[PATH_MAX];

    if (getcwd(current_path, sizeof(current_path)) != NULL) {
        printf("Current working directory: %s\n", current_path);
    } else {
        perror("getcwd() error");
        return 1;
    }

    /* Create the project folder */
    make_dir(current_path, strdup(argv[1]));

    /* Create the source folder -> project_name/src */
    make_dir(current_path, strcat(strdup(argv[1]), "/src"));

    /* Create the include folder -> project_name/include */
    make_dir(current_path, strcat(strdup(argv[1]), "/include"));

    make_file(current_path, strcat(strdup(argv[1]), "/src/main.c"));
    make_file(current_path, strcat(strdup(argv[1]), "/src/test.c"));
    make_file(current_path, strcat(strdup(argv[1]), "/src/yes.c"));

    return 0;
}
