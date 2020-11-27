#version 460

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 aPos;
} gs_in[];

out GS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 aPos;
} gs_out;

void main() {

    vec3 a = vec3(gl_in[0].gl_Position);
    vec3 b = vec3(gl_in[1].gl_Position);
    vec3 c = vec3(gl_in[2].gl_Position);

    vec3 aFragPos = gs_in[0].FragPos;
    vec3 bFragPos = gs_in[1].FragPos;
    vec3 cFragPos = gs_in[2].FragPos;

    vec3 normal = normalize(cross(b - a, c - b));

    int i;
    for (i = 0; i < gl_in.length(); i++) {
        gl_Position = gl_in[i].gl_Position;
        gs_out.FragPos = gs_in[i].FragPos;
        //gs_out.Normal = normal;
        gs_out.Normal = gs_in[i].Normal;
        gs_out.aPos = gs_in[i].aPos;
        EmitVertex();
    }


    EndPrimitive();
}
