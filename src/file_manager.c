#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../include/cJSON/cJSON.h"

/* Check if a file exists */
int file_exists(char *filename) {
    FILE *file = fopen(filename, "r");
    int exist = 1;

    if (file != NULL) {
        exist = 0;
        fclose(file);
    }

    return exist;
}

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

    /* Create a file */
    file_ptr = fopen(strdup(name), "w");

    /* Close the file */
    fclose(file_ptr);

    printf("New file: %s\n", new_file);

    /* Free the alocated memory of new_file */
    free(new_file);
}

/* Read a json file and return a cJSON object */
cJSON *load_json_file(char *name) {
    /* Open the file */
    FILE *file = fopen(name, "r");

    if (file == NULL) {
        perror("Error");
        exit(1);
    }

    /* Read the file contents into a string */
    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), file);

    /* Close the file */
    fclose(file);

    /* Parse the JSON data */
    cJSON *json = cJSON_Parse(buffer);

    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();

        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }

        cJSON_Delete(json);

        exit(1);
    }

    return json;
}
