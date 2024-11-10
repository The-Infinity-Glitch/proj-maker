#pragma once
#include <linux/limits.h>
#include "../include/cJSON/cJSON.h"

int file_exists(char *filename);

void make_dir(char path[PATH_MAX], char name[]);

void make_file(char path[PATH_MAX], char name[]);

cJSON *load_json_file(char *name);
