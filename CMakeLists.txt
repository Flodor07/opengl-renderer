cmake_minimum_required(VERSION 3.0.0)

project(simple-renderer VERSION 0.1.0 LANGUAGES C)

find_package(glfw3 REQUIRED)

add_library(glad ./dependencies/glad/src/glad.c)
include_directories(glad ./dependencies/glad/include)

add_library(mathc ./dependencies/mathc/mathc.c)
include_directories(mathc ./dependencies/mathc)


add_executable(${PROJECT_NAME} src/main.c src/defines.h src/utils.h src/utils.c src/camera.h src/camera.c src/mem.c src/mem.h src/window.h src/window.c src/model.c src/model.h src/shader.c src/shader.h)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} mathc)
target_link_libraries(${PROJECT_NAME} m)
