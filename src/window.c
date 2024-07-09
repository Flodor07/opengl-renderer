
#include "window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

GLFWwindow *createWindow(u32 height, u32 width, char *title) {

  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return NULL;
  }

  return window;
}
