#version 420 core

layout(std140) uniform uBlock {
    vec3 uVec;
};

layout(std140) uniform UniformBlock {
    mat4 Model;
};

varying vec4 vNormal;
varying vec4 vPosition;

out vec4 outColor;

void main(void){
    // hardcoded light
    vec3 light = vec3(0.0, 0.0, 1.0);
    float diffuse = clamp(dot(normalize(light), normalize(vNormal.xyz)), 0.0, 1.0);
    outColor = vec4(1.0, 0.0, 0.0, 1.0) * diffuse;
}
