#version 450

layout(location = 0) in vec3 fragColor;

// In the fragment shader you have to define your own output variable for each framebuffer
layout(location = 0) out vec4 outColor;

void main() { outColor = vec4(fragColor, 1.0); }