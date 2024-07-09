#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "mem.h"

char *readFile(const char *filePath, Arena *arena) {
  FILE *file = fopen(filePath, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file %s\n", filePath);
    return NULL;
  }

  // Go to the end of the file to get the size
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  rewind(file);

  // Allocate memory for the file contents
  char *buffer = (char *)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(file);
    return NULL;
  }

  // Read the file into the buffer
  size_t bytesRead = fread(buffer, 1, fileSize, file);
  if (bytesRead != fileSize) {
    fprintf(stderr, "Reading error\n");
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[fileSize] = '\0'; // Null-terminate the string

  fclose(file);
  return buffer;
}

void print_mat4(mat4_t matrix) {
  for (int i = 0; i < 4; i++) {
    printf("[%f | %f | %f | %f]\n", matrix[i * 4 + 0], matrix[i * 4 + 1],
           matrix[i * 4 + 2], matrix[i * 4 + 3]);
  }

  printf("\n");
}

void vec_vertex_print(VecVertex *dynArray) {
  for (int i = 0; i < dynArray->size; i++) {
    VertexObject *vo = &dynArray->data[i];

    printf("VertexObject %d\n", i);
    printf("pos: %f %f %f\n", vo->pos[0], vo->pos[1], vo->pos[2]);
    printf("texCoord: %f %f\n", vo->texture[0], vo->texture[1]);
    printf("normal: %f %f %f\n\n", vo->normal[1], vo->normal[1], vo->normal[2]);
  }
}

void vec_vertex_init(VecVertex *array, u32 capacity) {
  array->data = malloc(sizeof(VertexObject) * capacity);
  array->size = 0;
  array->capacity = capacity;
}

void vec_vertex_push(VecVertex *array, VertexObject *item) {
  if (array->size == array->capacity) {
    array->capacity *= 2;
    array->data = (VertexObject *)realloc(
        array->data, array->capacity * sizeof(VertexObject));
  }

  array->data[array->size] = *item;
  array->size++;
  // printf("%d\n", array->size);
}
