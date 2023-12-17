//fragment shader
#version 420

layout(std140, binding = 0) uniform Modifier {
float strength;
vec3  color;
};

layout(location=0) out vec4 vFragColor;

in vec3 theColor;

void main() {
    vFragColor = vec4(color * strength, 1.0);
}
