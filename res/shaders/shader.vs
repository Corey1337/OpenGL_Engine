#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 inColor;

out vec4 color;

void main() {
    color = vec4(inColor, 1);
    gl_Position = vec4(pos, 1.0);
}
