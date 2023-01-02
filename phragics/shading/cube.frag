#version 450 core

layout(location = 13) uniform vec3 u_color;

in vec3 v2f_viewNormal;
in vec3 v2f_viewPosition;

out vec4 f_color;

void main() {
    vec3 N = normalize(v2f_viewNormal);
    vec3 L = -normalize(vec3(-1.));
    float lambertian = max(dot(N, L), 0.);
    f_color = vec4(u_color * vec3(lambertian * .5 + .5), 1.);
}
