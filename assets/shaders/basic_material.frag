#version 430

in vec2 texcoord;

uniform sampler2DArray block_texture;

void main() {
    gl_FragColor = texture(block_texture, vec3(texcoord, 1));
}