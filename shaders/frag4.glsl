#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;

void main() {
    FragColor = mix(texture(texture1, TexCoord)*vec4(2, 2, 2, 1), texture(texture2, TexCoord*vec2(1,-1)), mixer);
}