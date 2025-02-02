#ifndef SHADER_H
#define SHADER_H

// OpenGL
#include <glad/glad.h>

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
};

#endif