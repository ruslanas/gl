#version 420 core

layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;

layout(std140) uniform UniformBlock {
    mat4 Model;
    vec4 light;
    vec4 color;
};

varying vec4 vNormal;
varying vec4 vPosition;

void main(void){
    vNormal = normal;
    gl_Position = Model * position;
    vPosition = gl_Position;
}
