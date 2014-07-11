#version 420 core
#pragma debug(on)

layout(std140) uniform UniformBlock {
    mat4 Model;
    vec3 light;
    vec3 color;
};

varying vec4 vNormal;
varying vec4 vPosition;

out vec4 outColor;

void main(void){
    // hardcoded light
    float diffuse = clamp(abs(dot(normalize(vNormal.xyz), normalize(light))), 0.0, 1.0);
    outColor = vec4(color * diffuse, 1.0);
}
