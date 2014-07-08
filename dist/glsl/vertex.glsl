#version 420 core

// test if blockIdx changes
layout(std140) uniform uBlock {
    vec3 uVec;
};

layout(std140) uniform UniformBlock {
    mat4 Model;
};

varying vec3 vNormal;
varying vec4 vPosition;
void main(void){
    vNormal = gl_Normal;
    gl_Position = Model * gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    vPosition = gl_Position;
}
