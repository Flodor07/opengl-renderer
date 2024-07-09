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

  vec3_t camera_pos = {3.0, 0.0, 3.0};
  vec3_t camera_target = {0.0, 0.0, 0.0};
  Context *context = malloc(sizeof(Context));
  init_context(context, camera_pos, camera_target);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // MESH creation
  VecVertex *vec_vertecies = malloc(sizeof(VecVertex));
  load_model("../models/cube.obj", vec_vertecies);

  Mesh *cube_mesh = malloc(sizeof(Mesh));
  init_mesh(cube_mesh, vec_vertecies->size, vec_vertecies->data);

  // model creation
  Model *cube_model = malloc(sizeof(Model));
  init_model(cube_model, cube_mesh, "../shaders/vert.glsl",
             "../shaders/frag.glsl");

  vec3_multiply_f(cube_model->transform->scale, cube_model->transform->scale,
                  2.0);
  vec3(cube_model->color, 0.859, 0.506, 0.043);

  Model *ground_model = malloc(sizeof(Model));
  init_model(ground_model, cube_mesh, "../shaders/vert.glsl",
             "../shaders/frag.glsl");

  vec3(ground_model->transform->position, 0.0, -1.0, 0.0);
  vec3(ground_model->transform->scale, 10.0, 0.01, 10.0);
  vec3(ground_model->color, 0.133, 0.145, 0.2);

  Model *light_model = malloc(sizeof(Model));
  init_model(light_model, cube_mesh, "../shaders/vert.glsl",
             "../shaders/frag-light.glsl");

  vec3_assign(light_model->color, context->light_color);
  vec3_assign(light_model->transform->position, context->light_pos);
  vec3_multiply_f(light_model->transform->scale, light_model->transform->scale,
                  0.5);

  glClearColor(0.075, 0.051, 0.078, 1.0);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float radius = 5;
    float speed = 1.0;
    float camX = sin(glfwGetTime() * speed) * radius;
    float camY = cos(glfwGetTime() * speed) * radius;
    vec3(context->camera->position, camX, 5.0, camY);

    draw_model(light_model, context);

    for (int i = 0; i < 1; i++) {
      vec3(cube_model->transform->position, 0.0, 0.0 + 3 * i, 0.0);
      draw_model(cube_model, context);
    }

    draw_model(ground_model, context);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  free_model(cube_model);
  free_model(ground_model);
  vec_vertex_free(vec_vertecies);
  free_context(context);
  return 0;
}
