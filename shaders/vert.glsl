#version 400 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec4 vertexColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 vertex_color;

void main() {
    vertex_color = vertexColor;
    gl_Position = projection * view * model * vec4(vertexPos, 1.0f);
};
