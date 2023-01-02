#version 450 core

layout(location = 0) uniform mat4 u_M;
layout(location = 4) uniform mat4 u_V;
layout(location = 8) uniform mat4 u_P;

layout(location = 0) in vec3 a_pos;

out vec3 v2f_center;
out vec3 v2f_radiuses;

void main() {
    mat4 MV = u_V * u_M;

    v2f_center = (MV * vec4(v2f_center, 1.)).xyz;
    v2f_radiuses = (MV * vec4(v2f_radiuses, 1.)).xyz;

    gl_Position = u_P * MV * vec4(a_pos, 1.);
}
