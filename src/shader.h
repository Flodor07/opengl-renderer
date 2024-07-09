#if !defined(shader_h)
#define shader_h
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <mathc.h>

unsigned int createShaderProgramm(const char *vertexShaderSource,
                                  const char *fragmentShaderSource);
void setMat4(unsigned int shaderProgramm, char *variableLocation,
             mfloat_t matrix[MAT4_SIZE]);
void setVec3(unsigned int shaderProgramm, char *variableName,
             mfloat_t vec3[VEC3_SIZE]);
void setVec4(unsigned int shaderProgramm, char *variableName,
             mfloat_t vec3[VEC4_SIZE]);

#endif // shader_h
