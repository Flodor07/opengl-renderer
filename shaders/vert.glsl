#version 400 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 vertexColor;

out vec3 vertex_color;
out vec3 vertex_normal;
out vec3 vertex_pos;

void main() {
    vertex_color = vertexColor;
    vertex_normal = mat3(transpose(inverse(model))) * vertexNormal;
    vertex_pos = vertexPos;
    gl_Position = projection * view * model * vec4(vertexPos, 1.0f);
};
