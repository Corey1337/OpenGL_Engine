#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 UvTex;
out vec3 Norm;
out vec3 FragPos;

void main() {
    UvTex = uv;
    Norm = mat3(transpose(inverse(model))) * norm;
    FragPos = vec3(model * vec4(pos, 1.0));
    gl_Position = projection * view * model * vec4(pos, 1.0f);
}
