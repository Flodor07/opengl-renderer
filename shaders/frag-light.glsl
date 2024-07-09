#version 400 core

in vec3 vertex_pos;
in vec3 vertex_color;
in vec3 vertex_normal;

out vec4 color;

void main() {
    color = vec4(vertex_color, 1.0);
};
