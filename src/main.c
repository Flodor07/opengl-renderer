#include "camera.h"
#include "defines.h"
#include "mathc.h"
#include "mem.h"
#include "model.h"
#include "utils.h"
#include "window.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main() {
  GLFWwindow *window = createWindow(720, 1280, "test-windwo");
  Arena *arena = arena_init();

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  vec4_t color = {0.859, 0.506, 0.043, 1.0};
  VecVertex *vec_vertecies = arena_alloc(arena, sizeof(VecVertex));
  load_model("../models/cube.obj", vec_vertecies, color);

  Mesh *cube_mesh = arena_alloc(arena, sizeof(Mesh));
  init_mesh(cube_mesh, vec_vertecies->size, vec_vertecies->data,
            "../shaders/frag.glsl", "../shaders/vert.glsl");

  vec3_t camera_pos = {3.0, 0.0, 3.0};
  vec3_t camera_target = {0.0, 0.0, 0.0};
  Camera *camera = malloc(sizeof(Camera));
  create_camera(camera, camera_pos, camera_target);

  // glClearColor(0.059, 0.102, 0.38, 1.0);
  glClearColor(0.133, 0.145, 0.2, 1.0);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4_t projection;
    mat4_t view;
    mat4_perspective(projection, to_radians(90.0), (float)1280 / (float)720,
                     0.1, 100.0);

    float radius = 3;
    float camX = sin(glfwGetTime()) * radius;
    float camY = cos(glfwGetTime()) * radius;
    vec3(camera->position, camX, 0.0, camY);

    create_view_matrix(view, camera);

    vec3_t pos = {0.0, 0.0, 0.0};
    vec3_t scaling;
    vec3_one(scaling);
    vec3_multiply_f(scaling, scaling, 2.0);

    vec3_t rotation_axis = {0.3, 1.0, 3.0};
    mat4_t roation;
    mat4_rotation_axis(roation, rotation_axis, 0.5);

    draw_mesh(cube_mesh, pos, roation, scaling, view, projection);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  free(camera);
  arena_free(arena);
  return 0;
}
