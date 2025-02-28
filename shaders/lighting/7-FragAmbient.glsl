#version 460 core

out vec4 FragColor;

uniform float AmbientStrength;
uniform vec3 BoxColor;
uniform vec3 LightColor;

void main() {
    vec3 ambientColor = AmbientStrength * LightColor;
    vec3 result = ambientColor * BoxColor;
    FragColor = vec4(result, 1.0);
}