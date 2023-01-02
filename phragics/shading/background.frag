#version 450 core

const float pi = 3.14152;

layout(location = 0) uniform mat4 u_V;

out vec4 out_color;

void swap(inout float a, inout float b) {
    float t = a;
    a = b;
    b = t;
}

int find(vec3 v, float e) {
    return int(dot(ivec3(equal(v, vec3(e))), ivec3(0, 1, 2)));
}

vec3 sorted(in vec3 v) {
    if(v[0] > v[1]) swap(v[0],v[1]);
    if(v[1] > v[2]) swap(v[1],v[2]);
    if(v[0] > v[1]) swap(v[0],v[1]);
    return v;
}

vec3 cubeColors(int face, float isNeg) {
    // vec3 col = vec3(float(face == 0), float(face == 1), float(face == 2));
    vec3 col = vec3(equal(ivec3(face), ivec3(0, 1, 2)));
    return col * (1. - 2. * isNeg) + isNeg;
}

void main() {
    vec2 resolution = vec2(1280, 720);
    vec2 coords = (2. * gl_FragCoord.xy - resolution) / resolution.y;
    vec3 dir = normalize(vec3(coords, -1.)); // Assumes fovy is 90 degrees.
    vec3 wsDir = (inverse(u_V) * vec4(dir, 0.)).xyz;

    vec3 axes = sorted(abs(wsDir));
    float maxAxis = axes[2];
    axes /= maxAxis;

    float intervals = 1. / 10.;

    float cubeEdge = smoothstep(0.01, 0., 1. - axes[1]);
    int maxi = find(abs(wsDir), maxAxis);
    vec3 cubeCol = cubeColors(maxi, float(wsDir[maxi] < 0.));
    out_color = vec4(mix(cubeCol * .2, vec3(1.), cubeEdge), 1.);
}
