#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/* Create a new directory */
void make_dir(char path[PATH_MAX], char name[]) {
    /* (path + "/") + (name + "/") -> path/name/ */
    char *new_path = strcat(strcat(strdup(path), "/"), strcat(strdup(name), "/"));

    if (mkdir(name, 0700) == -1) {
        printf("Failed when creating path: %s\n", new_path);
        exit(1);
    } else {
        printf("New directory: %s\n", new_path);
    }

    /* Free the alocated memory of new_path */
    free(new_path);
}

void make_file(char path[PATH_MAX], char name[]) {
    /* (path + "/") + name.* -> path/name.* */
    char *new_file = strcat(strcat(strdup(path), "/"), strdup(name));

    FILE *file_ptr;

    // Create a file
    file_ptr = fopen(strdup(name), "w");

    // Close the file
    fclose(file_ptr);

    printf("New file: %s\n", new_file);

    /* Free the alocated memory of new_file */
    free(new_file);
}
