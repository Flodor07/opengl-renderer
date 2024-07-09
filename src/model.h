#ifndef MODEL_H
#define MODEL_H

#include "defines.h"
#include "utils.h"
#define MAX_VERTECIES 2000

typedef struct {
  u32 VAO;
  u32 VBO;
  u32 shader_program;
  u32 num_vertecies;

  VertexObject *vertecies;
} Mesh;

void load_model(char *filePath, VecVertex *vertecies, vec4_t color);
void init_mesh(Mesh *mesh, u32 num_vertecies, VertexObject *vertecies,
               char *fragment_shader_path, char *vertex_shader_path);

void draw_mesh(Mesh *mesh, vec3_t position, mat4_t rotation, vec3_t scaling,
               mat4_t view, mat4_t projection);

#endif // !MODEL_H
