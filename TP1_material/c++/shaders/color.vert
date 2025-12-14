#version 330 core

// input attribute variable, given per vertex
in vec3 position;
out vec3 fragColor;

// global matrix variables
uniform mat4 view;
uniform mat4 projection;



void main() {
    // Permet de faire une pyramide arc-en-ciel
    fragColor = position + vec3(0.5, 0.2, 0.5);

    // Permet de gérer les rotations, les translations, et le scaling.
    gl_Position = projection * view * vec4(position, 1.0);
}