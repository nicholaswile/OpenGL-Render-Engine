#include "../headers/shader.h"

Shader::Shader(const char* vert_path, const char* frag_path) {
    std::string vert_code;
    std::string frag_code;
    std::ifstream vert_file;
    std::ifstream frag_file;

    vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vert_file.open(vert_path);
        frag_file.open(frag_path);

        std::stringstream vert_stream, frag_stream;
        vert_stream << vert_file.rdbuf();
        frag_stream << frag_file.rdbuf();

        vert_file.close();
        frag_file.close();

        vert_code = vert_stream.str();
        frag_code = frag_stream.str();
    }
    catch(const std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << "\n";
        std::cout << "VERT FILE: " << vert_path << "\n";
        std::cout << "FRAG FILE: " << frag_path << "\n";
    }

    const char* vert_shader_code = vert_code.c_str();
    const char* frag_shader_code = frag_code.c_str();

    int success;
    char info_log[512];

    // Create shader object / ID to store shader code
    unsigned int vert_shader_ID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int frag_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vert_shader_ID, 1, &vert_shader_code, NULL);
    glShaderSource(frag_shader_ID, 1, &frag_shader_code, NULL);
    
    // Compile dynamically at run-time
    glCompileShader(vert_shader_ID);
    glCompileShader(frag_shader_ID);

    // Check if compilation was successful
    glGetShaderiv(vert_shader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert_shader_ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << "\n";
    }

    glGetShaderiv(frag_shader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader_ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << "\n";
    }

    // Shader program to link both vert and frag shaders
    ID = glCreateProgram();

    // Attach shader code to shader object 
    glAttachShader(ID, vert_shader_ID);
    glAttachShader(ID, frag_shader_ID);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << "\n";
    }

    // Delete shaders now that they've been linked
    glDeleteShader(vert_shader_ID);
    glDeleteShader(frag_shader_ID);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::set_bool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_vec3(const std::string& name, const glm::vec3 value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.r, value.g, value.b);
}
