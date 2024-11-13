#pragma once
#include <linux/limits.h>
#include "../include/cJSON/cJSON.h"

int file_exists(char *filename);

void make_dir(char path[PATH_MAX], char name[]);

void make_file(char path[PATH_MAX], char name[]);

char *read_file(char *name);

void write_to_file(char *file_name, char *content);

void create_project_file(char path[PATH_MAX], char name[], char project_template[]);

cJSON *load_json_file(char *name);
