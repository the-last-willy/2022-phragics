#version 450 core

layout(location = 0) uniform mat4 u_M;
layout(location = 4) uniform mat4 u_N;
layout(location = 8) uniform mat4 u_P;
layout(location = 12) uniform mat4 u_V;

layout(location = 1) in vec3 a_normal;
layout(location = 0) in vec3 a_position;

out vec3 v2f_viewPosition;
out vec3 v2f_viewNormal;

void main() {
    vec4 vNor = u_N * vec4(a_normal, 0.);
    vec4 vPos = u_V * u_M * vec4(a_position, 1.);

    v2f_viewPosition = vPos.xyz / vPos.w;
    v2f_viewNormal = vNor.xyz;

    gl_Position = u_P * vPos;
}
