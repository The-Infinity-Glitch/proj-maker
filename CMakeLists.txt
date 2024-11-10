CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3)

PROJECT(proj-manager)

ADD_EXECUTABLE(${PROJECT_NAME} src/main.c src/gui_editor/main.c src/gui_editor/main.h include/cJSON/cJSON.c include/cJSON/cJSON.h src/file_manager.c src/file_manager.h)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} raylib GL m pthread dl rt X11)
