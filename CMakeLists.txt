CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3)

PROJECT(proj-manager)

ADD_EXECUTABLE(${PROJECT_NAME} src/main.c src/file_manager.c src/file_manager.h)
