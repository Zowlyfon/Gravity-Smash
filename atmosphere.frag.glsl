#version 460
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 aPos;
} vs_out;

uniform vec3 objPos;
uniform float objSize;

void main() {
    FragColor = ((1.0f / (1.0f + objSize * objSize)) / length(vs_out.FragPos.xy - objPos.xy)) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
