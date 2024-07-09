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

  VecVertex *vec_vertecies = arena_alloc(arena, sizeof(VecVertex));
  load_model("../models/cube.obj", vec_vertecies);

  Mesh *cube_mesh = malloc(sizeof(Mesh));
  init_mesh(cube_mesh, vec_vertecies->size, vec_vertecies->data);

  Model *cube_model = malloc(sizeof(Model));
  init_model(cube_model, cube_mesh, "../shaders/vert.glsl",
             "../shaders/frag.glsl");

  vec4(cube_model->color, 0.859, 0.506, 0.043, 1.0);

  Model *ground_model = malloc(sizeof(Model));
  init_model(ground_model, cube_mesh, "../shaders/vert.glsl",
             "../shaders/frag.glsl");

  vec3(ground_model->transform->position, 0.0, -3.0, 0.0);
  vec3(ground_model->transform->scale, 10.0, 0.6, 10.0);
  vec4(ground_model->color, 0.173, 0.2, 0.22, 1.0);

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

    float radius = 8;
    float camX = sin(glfwGetTime()) * radius;
    float camY = cos(glfwGetTime()) * radius;
    vec3(camera->position, camX, 0.0, camY);

    create_view_matrix(view, camera);
    draw_model(cube_model, view, projection);

    draw_model(ground_model, view, projection);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  free(camera);
  free_model(cube_model);
  free_model(ground_model);
  arena_free(arena);
  return 0;
}
