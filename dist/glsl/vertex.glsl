#version 420 core
varying vec3 vNormal;

void main(void){
    vNormal = gl_Normal;
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
