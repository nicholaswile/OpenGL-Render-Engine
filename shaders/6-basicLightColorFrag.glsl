#version 460 core

out vec4 FragColor;

uniform vec3 BoxColor;
uniform vec3 LightColor;

void main() {
    FragColor = vec4(LightColor * BoxColor, 1.0);
}