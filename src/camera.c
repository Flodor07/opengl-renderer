#include "camera.h"
#include <mathc.h>
#include <stdlib.h>

void update_camera(Camera *camera) {
  vec3_t direction;
  vec3_subtract(direction, camera->position, camera->target);
  vec3_normalize(direction, direction);

  vec3_cross(camera->right, camera->globalUp, direction);
  vec3_normalize(camera->right, camera->right);

  vec3_cross(camera->up, direction, camera->right);
  vec3_normalize(camera->up, camera->up);
}

void create_camera(Camera *camera, vec3_t postion, vec3_t target) {

  vec3_assign(camera->position, postion);
  vec3_assign(camera->target, target);
  vec3(camera->globalUp, 0.0, 1.0, 0.0);

  update_camera(camera);
}

void create_view_matrix(mat4_t view_matrix, Camera *camera) {
  update_camera(camera);

  mat4_look_at(view_matrix, camera->position, camera->target, camera->up);
}
