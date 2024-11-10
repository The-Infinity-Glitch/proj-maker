#include "../file_manager.h"
#include <linux/limits.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int editor_main(char current_path[PATH_MAX]) {
    /* Check if the current directory has a proj-maker project */
    if (file_exists("project.json") != 0) return 1;

    /* Load the project file into a cJSON object */
    cJSON *project_file = load_json_file("project.json");

    InitWindow(800, 450, "proj-maker - [Editor]");

    int current_page = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        GuiToggleGroup((Rectangle) {10, 10, 390, 40}, "Projects;#191#Settings", &current_page);

        EndDrawing();
    }

    CloseWindow();

    /* Delete the project cJSON object */
    cJSON_Delete(project_file);
    return 0;
}
