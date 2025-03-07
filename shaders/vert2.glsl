#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;
out vec4 vert_position;

// Rotates vertices 180-degrees
void main() {
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    vertexColor = aColor;
    vert_position = gl_Position;
}