#version 460 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 norm;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 UvTex;
out vec3 Norm;
out vec3 FragPos;
out mat3 TBNmat;

void main() {
    UvTex = uv;
    Norm = mat3(transpose(inverse(model))) * norm;
    FragPos = vec3(model * vec4(pos, 1.0));

    vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(norm, 0.0)));
    mat3 TBN = mat3(T, B, N);
    TBNmat = TBN;

    gl_Position = projection * view * model * vec4(pos, 1.0f);
}
