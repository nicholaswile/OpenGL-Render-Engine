#ifndef SHADER_H
#define SHADER_H

// OpenGL
#include <glad/glad.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// CPP
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // Shader program identifier.
    unsigned int ID;

    // Reads and builds the shader program.
    Shader(const char* vert_path, const char* frag_path);

    // Activates the shader.
    void use();
    void set_bool(const std::string &name, bool value) const;
    void set_int(const std::string &name, int value) const;
    void set_float(const std::string &name, float value) const;
    void set_vec3(const std::string &name, const glm::vec3 value) const;
};

#endif