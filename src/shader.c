#include "shader.h"
#include "mem.h"
#include "utils.h"
#include <mathc.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int createShaderProgramm(const char *vertexShaderPath,
                                  const char *fragmentShaerPath) {

  Arena *arena = arena_init();
  const char *vertexShaderSource = readFile(vertexShaderPath, arena);
  const char *fragmentShaderSource = readFile(fragmentShaerPath, arena);

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",
            infoLog);
  }

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  arena_free(arena);

  return shaderProgram;
}

void setMat4(unsigned int shaderProgramm, char *variableName,
             mfloat_t matrix[MAT4_SIZE]) {
  int location = glGetUniformLocation(shaderProgramm, variableName);

  glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void setVec3(unsigned int shaderProgramm, char *variableName,
             mfloat_t vec3[VEC3_SIZE]) {
  int location = glGetUniformLocation(shaderProgramm, variableName);
  glUniform3fv(location, 1, vec3);
}
void setVec4(unsigned int shaderProgramm, char *variableName,
             mfloat_t vec3[VEC4_SIZE]) {
  int location = glGetUniformLocation(shaderProgramm, variableName);
  glUniform4fv(location, 1, vec3);
}
