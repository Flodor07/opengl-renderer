#ifndef DEFINES_H
#define DEFINES_H

#include "mathc.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef mfloat_t vec2_t[VEC2_SIZE];
typedef mfloat_t vec3_t[VEC3_SIZE];
typedef mfloat_t vec4_t[VEC4_SIZE];

typedef mfloat_t mat2_t[MAT2_SIZE];
typedef mfloat_t mat3_t[MAT3_SIZE];
typedef mfloat_t mat4_t[MAT4_SIZE];

typedef struct {
  vec3_t pos;
  vec3_t normal;
  vec2_t texture;
} VertexObject;

#define Gigabyte(i) 1024 * 1024 * 1024 * i

#define nullptr (void *)0

#endif // !DEFINES_H
