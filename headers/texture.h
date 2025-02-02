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

void Texture::CreateTexture(const char* texture_path, GLenum texture, GLenum texture_type, GLuint mipmap_level, GLenum color_format, GLenum format, GLenum hwrap, GLenum vwrap, GLenum minfilter, GLenum magfilter) {
    int width, height, nChannels;
    unsigned char *data = stbi_load(texture_path, &width, &height, &nChannels, 0);
    if (data) {
        std::string dims = "("+std::to_string(width)+","+std::to_string(height)+")";
        std::cout << "Succesfully loaded texture "<< texture_path << " " << dims << "\n";
        
        // glTexImage2D - currently bound texture object has texture image attached to it
        // specifies texture target (generates texture on object bound at that target), mipmap level, color format, width/height, ignore, format and datatype of source image, actual image data
        glTexImage2D(texture_type, 0, color_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(texture_type);
    }

    else {
        std::cout << "Failed to load texture "<< texture_path << "\n";
    }

    // cleanup after generating texture and mipmaps by freeing image memory
    stbi_image_free(data);

    glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, hwrap); 
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, vwrap); 
    glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, magfilter);
}

#endif