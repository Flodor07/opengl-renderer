#include <glad/glad.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "camera.h"
#include "defines.h"
#include "mathc.h"
#include "mem.h"
#include "model.h"
#include "shader.h"
#include "utils.h"

void load_model(char *filePath, VecVertex *vertecies) {
  vec3_t vertex[MAX_VERTECIES];
  vec3_t vertexNormal[MAX_VERTECIES];
  vec2_t vertexTexture[MAX_VERTECIES];

  u32 vCount = 0;
  u32 vnCount = 0;
  u32 vtCount = 0;

  FILE *file = fopen(filePath, "r");
  if (file == NULL) {
    printf("error opening file\n");
    exit(EXIT_FAILURE);
  }

  vec_vertex_init(vertecies, 160);

  char *line = NULL;
  size_t len = 0;
  size_t read;

  while ((read = getline(&line, &len, file)) != -1) {
    char *words[4];

    words[0] = strtok(line, " ");
    for (int i = 1; i < 4; i++) {
      words[i] = strtok(NULL, " ");
      // ^next thing after space
    }

    if (strcmp(words[0], "v") == 0) {
      vec3(vertex[vCount], atof(words[1]), atof(words[2]), atof(words[3]));
      vCount++;
    } else if (strcmp(words[0], "vn") == 0) {
      vec3(vertexNormal[vnCount], atof(words[1]), atof(words[2]),
           atof(words[3]));
      vnCount++;

    } else if (strcmp(words[0], "vt") == 0) {
      vec2(vertexTexture[vtCount], atof(words[1]), atof(words[2]));
      vtCount++;

    } else if (strcmp(words[0], "f") == 0) {
      for (int i = 1; i < 4; i++) {
        char *face[3];
        // 0 = vertex, 1 = texture, 2 = normal
        face[0] = strtok(words[i], "/");
        face[1] = strtok(NULL, "/");
        face[2] = strtok(NULL, "/");

        VertexObject *v = malloc(sizeof(VertexObject));
        v->pos[0] = vertex[atoi(face[0]) - 1][0];
        v->pos[1] = vertex[atoi(face[0]) - 1][1];
        v->pos[2] = vertex[atoi(face[0]) - 1][2];

        v->texture[0] = vertexTexture[atoi(face[1]) - 1][0];
        v->texture[1] = vertexTexture[atoi(face[1]) - 1][1];

        v->normal[0] = vertexNormal[atoi(face[2]) - 1][0];
        v->normal[1] = vertexNormal[atoi(face[2]) - 1][1];
        v->normal[2] = vertexNormal[atoi(face[2]) - 1][2];

        vec_vertex_push(vertecies, v);
        free(v);
      }
    }
  }

  fclose(file);
  if (line) {
    free(line);
  }
}

void init_mesh(Mesh *mesh, u32 num_vertecies, VertexObject *vertecies) {
  mesh->vertecies = vertecies;
  mesh->num_vertecies = num_vertecies;
  // Create our Vertex Buffer and Vertex Array Objects
  glGenVertexArrays(1, &(mesh->VAO));
  glBindVertexArray(mesh->VAO);

  glGenBuffers(1, &(mesh->VBO));
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).

  glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexObject) * mesh->num_vertecies,
               mesh->vertecies, GL_STATIC_DRAW);

  // Position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexObject),
                        (void *)offsetof(VertexObject, pos));
  // Normal
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexObject),
                        (void *)offsetof(VertexObject, normal));
  // Texture
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexObject),
                        (void *)offsetof(VertexObject, texture));

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);
}
void init_model(Model *model, Mesh *mesh, char *vertex_shader_path,
                char *fragment_shader_path) {
  model->mesh = mesh;
  model->transform = malloc(sizeof(Transform));

  vec3_zero(model->transform->position);
  vec3_one(model->transform->scale);
  mat4_identity(model->transform->rotation);

  vec3_one(model->color);

  model->shader_program =
      createShaderProgramm(vertex_shader_path, fragment_shader_path);
}

void init_context(Context *context, vec3_t camera_pos, vec3_t camera_target) {
  context->camera = malloc(sizeof(Camera));
  create_camera(context->camera, camera_pos, camera_target);

  mat4_perspective(context->projection, to_radians(90.0),
                   (float)1280 / (float)720, 0.1, 100.0);

  vec3(context->light_pos, 10.0, 5.0, 3.0);
  vec3_one(context->light_color);
  // vec3(context->light_color, 0.3, 0.6, 1.0);
}

void free_model(Model *model) {
  free(model->transform);
  free(model);
}

void free_mesh(Mesh *mesh) {
  free(mesh->vertecies);
  free(mesh);
}

void free_context(Context *context) {
  free(context->camera);
  free(context);
}

void draw_model(Model *model, Context *context) {
  struct {
    mat4_t position;
    mat4_t scaling;
    mat4_t rotation;
    mat4_t model;
  } matrices;

  mat4_assign(matrices.rotation, model->transform->rotation);

  mat4_identity(matrices.position);
  mat4_translation(matrices.position, matrices.position,
                   model->transform->position);

  mat4_identity(matrices.scaling);
  mat4_scaling(matrices.scaling, matrices.scaling, model->transform->scale);

  mat4_multiply(matrices.model, matrices.rotation, matrices.scaling);
  mat4_multiply(matrices.model, matrices.position, matrices.model);

  mat4_t view;
  create_view_matrix(view, context->camera);

  glUseProgram(model->shader_program);

  setMat4(model->shader_program, "model", matrices.model);
  setMat4(model->shader_program, "projection", context->projection);
  setMat4(model->shader_program, "view", view);

  setVec3(model->shader_program, "vertexColor", model->color);
  setVec3(model->shader_program, "lightColor", context->light_color);
  setVec3(model->shader_program, "lightPos", context->light_pos);
  setVec3(model->shader_program, "cameraPos", context->camera->position);

  glBindVertexArray(model->mesh->VAO);
  glDrawArrays(GL_TRIANGLES, 0, model->mesh->num_vertecies);

  glUseProgram(0);
  glBindVertexArray(0);
}
