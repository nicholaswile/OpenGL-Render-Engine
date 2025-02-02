#ifndef TEXTURE_H
#define TEXTURE_H

// OpenGL
#include <glad/glad.h>

// Include
#include <stb_image.h>

// CPP
#include <string>
#include <iostream>

class Texture {
public:
    static void CreateTexture(const char* texture_path, GLenum texture, GLenum texture_type, GLuint mipmap_level=0, GLenum color_format=GL_RGB, GLenum format=GL_RGB, GLenum hwrap=GL_REPEAT, GLenum vwrap=GL_REPEAT, GLenum minfilter=GL_NEAREST_MIPMAP_LINEAR, GLenum magfilter=GL_NEAREST);
};

#endif