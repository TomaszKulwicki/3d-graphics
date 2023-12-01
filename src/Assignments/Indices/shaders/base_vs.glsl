#version 410

layout(location=0) in  vec4 a_vertex_position;
layout(location=1) in  vec3 figureColor;

out vec3 theColor;

void main() {
    gl_Position = a_vertex_position;
    theColor = figureColor;
}
