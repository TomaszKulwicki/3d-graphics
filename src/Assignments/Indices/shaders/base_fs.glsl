#version 410

layout(location=0) out vec4 vFragColor;

in vec3 theColor;

void main() {
    vFragColor = vec4(theColor, 1.0);
}
