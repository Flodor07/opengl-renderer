#ifndef MODEL_H
#define MODEL_H

#include "defines.h"
#include "mem.h"
#include "utils.h"
#define MAX_VERTECIES 2000

typedef struct {
  vec3_t scale;
  vec3_t position;
  mat4_t rotation;
} Transform;

typedef struct {
  u32 VAO;
  u32 VBO;
  u32 num_vertecies;

  VertexObject *vertecies;
} Mesh;

typedef struct {
  Mesh *mesh;
  Transform *transform;
  vec4_t color;

  u32 shader_program;
} Model;

void load_model(char *filePath, VecVertex *vertecies);
void init_mesh(Mesh *mesh, u32 num_vertecies, VertexObject *vertecies);
void init_model(Model *model, Mesh *mesh, char *vertex_shader_path,
                char *fragment_shader_path);
void free_mesh(Mesh *mesh);
void free_model(Model *mesh);
void draw_model(Model *model, mat4_t view, mat4_t projection);

#endif // !MODEL_H
