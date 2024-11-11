#include "file_manager.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "gui_editor/main.h"

void create_project(char current_path[], char name[], char template[]) {
    /* Create the project folder */
    make_dir(current_path, strdup(name));

    /* Create the source folder -> project_name/src */
    make_dir(current_path, strcat(strdup(name), "/src"));

    /* Create the include folder -> project_name/include */
    make_dir(current_path, strcat(strdup(name), "/include"));

    /* Create the proj-maker project file -> project_name/project.json */
    make_file(current_path, strcat(strdup(name), "/project.json"));

    if (strcmp(template, "terminal") == 0) {
        write_to_file(strcat(strdup(name), "/src/main.c"), read_file("/home/themaster/Templates/terminal/main_src.txt"));
    } else if (strcmp(template, "raylib") == 0) {

    }
}

int main(int argc, char *argv[]) {
    /* Get the current path */
    char current_path[PATH_MAX];

    if (getcwd(current_path, sizeof(current_path)) != NULL) {
        printf("Current working directory: %s\n", current_path);
    } else {
        perror("getcwd() error");
        return 1;
    }

    if (strcmp(argv[1], "new") == 0) {
        if (argc < 4) {
            printf("here");
            create_project(current_path, strdup(argv[2]), "terminal");
        } else {
            printf("this");
            create_project(current_path, strdup(argv[2]), strdup(argv[3]));
        }
    } else if (strcmp(argv[1], "edit") == 0) {
        if (editor_main(current_path) != 0) {
            perror("\"project.json\"");
        }
    }

    return 0;
}
