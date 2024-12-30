#version 460 core

in vec4 vert_position;
out vec4 FragColor;
uniform vec4 globalColor;

void main() {
    //FragColor = vec4(globalColor.x * vert_position.x, globalColor.y * vert_position.y, globalColor.z * vert_position.z, 1.0f);
    FragColor = vert_position;
}