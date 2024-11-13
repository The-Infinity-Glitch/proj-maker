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

char *read_file(char *name) {
    FILE *file;

    /* Open a file in read mode */
    file = fopen(name, "r");

    /* Read the file contents into a string */
    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), file);

    /* Close the file */
    fclose(file);

    char *content = buffer;
    return content;
}

void write_to_file(char *file_name, char content[]) {
    FILE *file;

    /* Open a file in writing mode */
    file = fopen(file_name, "w");

    if (file == NULL) {
        printf("Error: No such file");
        return;
    }

    /* Write some text to the file */
    fputs(content, file);

    /* Close the file */
    fclose(file);
}

void create_project_file(char path[PATH_MAX], char name[], char project_template[]) {
    char *new_project_file = strcat(strdup(name), "/project.json");
    make_file(path, new_project_file);

    /* Create a cJSON object */
    cJSON *json = cJSON_CreateObject();
    cJSON_AddObjectToObject(json, "settings");
    cJSON_AddStringToObject(json->child, "cmake version", "3.28.3");
    cJSON_AddObjectToObject(json, "project");
    cJSON_AddStringToObject(json->child->next, "name", name);
    cJSON_AddArrayToObject(json->child->next, "source files");

    /* Convert cJSON object into a string */
    char *json_str = cJSON_Print(json);

    write_to_file(new_project_file, json_str);

    cJSON_free(json_str);
    cJSON_Delete(json);
}

/* Read a json file and return a cJSON object */
cJSON *load_json_file(char *name) {
    /* Open the file */
    FILE *file = fopen(name, "r");

    if (file == NULL) {
        perror("Error: No such file");
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
