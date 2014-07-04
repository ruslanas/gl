#version 420 core
varying vec3 vNormal;

void main(void){
    float diffuse = dot(vec3(1.0, 1.0, 1.0), vNormal);
    gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0) * diffuse;
}
