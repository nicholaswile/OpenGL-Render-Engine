#version 460 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform float AmbientStrength;
uniform vec3 BoxColor;
uniform vec3 LightColor;
uniform vec3 LightPos;

void main() {
    // Ambient
    vec3 ambientColor = AmbientStrength * LightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseColor = diff * LightColor;
    
    // Result
    vec3 result = (ambientColor + diffuseColor) * BoxColor;
    FragColor = vec4(result, 1.0);
}