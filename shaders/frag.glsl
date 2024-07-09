#version 400 core

in vec3 vertex_pos;
in vec3 vertex_color;
in vec3 vertex_normal;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

out vec4 color;

void main() {
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 norm = normalize(vertex_normal);
    vec3 lightDir = normalize(lightPos - vertex_pos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = lightColor * diff;

    vec3 viewDir = normalize(cameraPos - vertex_pos);
    vec3 reflectDir = reflect(-lightDir, norm);

    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    // vec3 specular = specularStrength * spec * lightColor;

    vec3 ambient = ambientStrength * lightColor;

    vec3 result = vertex_color * (ambient + diffuse);

    color = vec4(result, 1.0);
};
