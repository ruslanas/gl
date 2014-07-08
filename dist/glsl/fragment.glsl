#version 420 core

layout(std140) uniform uBlock {
    vec3 uVec;
};

layout(std140) uniform UniformBlock {
    mat4 Model;
};

varying vec3 vNormal;
varying vec4 vPosition;

void main(void){
    float diffuse = clamp(dot(normalize(vec3(1.0, 1.0, 1.0)), normalize(vNormal)), 0.0, 1.0);
    gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0) * diffuse;
}
