#version 460 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 aPos;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.FragPos = vec3(model * aPos);
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
    vs_out.aPos = aPos;
    gl_Position = projection * view * model * aPos;
}