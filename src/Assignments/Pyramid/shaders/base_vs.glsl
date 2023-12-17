//vertex shader
#version 420

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec3 figureColor;

layout(std140, binding=1) uniform Transformations {
    mat4 PVM;
};

out vec3 theColor;

void main() {
    gl_Position =  PVM * a_vertex_position;
    gl_Position.zw = a_vertex_position.zw;
    theColor = figureColor;
}