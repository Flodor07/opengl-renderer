#ifndef UTILS_H
#define UTILS_H

#include "defines.h"
#include "mem.h"

typedef struct {
  VertexObject *data;
  u32 size;
  u32 capacity;
} VecVertex;

void print_mat4(mat4_t matrix);

void vec_vertex_print(VecVertex *dynArray);
void vec_vertex_init(VecVertex *array, u32 capacity);
void vec_vertex_push(VecVertex *array, VertexObject *item);

char *readFile(const char *filePath, Arena *Arena);

#endif // !UTILS_H
