#version 360 core

layout(local_size_x = 1) in;

layout(std430, binding = 0) buffer Normals {
    vec4 Normals[];
};

void main() {

}
