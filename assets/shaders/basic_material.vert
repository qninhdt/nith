#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 pass_color;

out vec3 color;

void main() {
    gl_Position = vec4(position, 1.0f);
    color = pass_color;

}