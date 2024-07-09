#ifndef CAMERA_H
#define CAMERA_H
#include "defines.h"

typedef struct {
  vec3_t target;
  vec3_t position;
  vec3_t globalUp;

  vec3_t right;
  vec3_t up;
} Camera;

void create_camera(Camera *camera, vec3_t position, vec3_t target);
void create_view_matrix(mfloat_t viewMatrix[MAT4_SIZE], Camera *camera);
void updateCamea(Camera *camera);

#endif // camera_h
