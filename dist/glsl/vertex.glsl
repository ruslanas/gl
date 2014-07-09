#version 420 core

layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;

// this block is not used
layout(std140) uniform uBlock {
    vec3 uVec;
};

layout(std140) uniform UniformBlock {
    mat4 Model;
};

varying vec4 vNormal;
varying vec4 vPosition;

void main(void){
    vNormal = normal;
    gl_Position = Model * position;
    vPosition = gl_Position;
}
