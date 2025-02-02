#ifndef SCENE1_H
#define SCENE1_H

// Custom
#include "../headers/scene.h"

class Scene1 : public Scene {
private:
    float _mixer = .5f;
    Shader* _shader;
    unsigned int _VAO_ID;
    unsigned int _VBO_ID;
    unsigned int _EBO_ID;
public:
    Scene1() {}
    ~Scene1() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
    }
    void load();
    void unload() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
    }
    void render(float delta_time);
};


void Scene1::load() {

    // Shaders
    _shader = new Shader("shaders/vert4.glsl", "shaders/frag4.glsl"); // texture shader

    // Create mesh (might make this a class later)
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Copy the vertex and index data onto the GPU
    glGenBuffers(1, &_VBO_ID);                                                           // Vertex buffer object
    glGenVertexArrays(1, &_VAO_ID);                                                      // Vertex attribute object (settings, configs OpenGL how to read the data in VBO)
    glGenBuffers(1, &_EBO_ID);                                                           // Element buffer object tells OpenGL indices that make up each triangle

    glBindVertexArray(_VAO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID);                                              // Configure buffer array 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);          // Copy data to buffer memory

    // Tell OpenGL how to interpret vertex data
    // Parameters: location=0 (set position in shader to 0), size of attribute=vec3 (3 values), type of data is vec* float, whether data should be normalized [0,1], stride (space between vertex attributes, 3 floats = 3*sizeof(float=32 bits) to get next vec3, offset of start of position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // will give layout(location = 0) in shaders. 

    // Create new vertex attribute for this texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); // will give layout(location = 2) in shaders. 

    // TEXTURES
    unsigned int textures[2];
    glGenTextures(2, textures);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    Texture::CreateTexture("textures/container.jpg", GL_TEXTURE0, GL_TEXTURE_2D, 0, GL_RGB, GL_RGB, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    Texture::CreateTexture("textures/sprigatito.png", GL_TEXTURE1, GL_TEXTURE_2D, 0, GL_RGBA, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);

    // Set uniform variables to appropriate texture
    _shader->use();
    glUniform1i(glGetUniformLocation(_shader->ID, "texture1"), 0); // Make sure each uniform sampler corresponds to correct texture unit
    _shader->set_int("texture2", 1);

}

void Scene1::render(float delta_time) {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->use();
    _shader->set_float("mixer", _mixer); // for use in vert/frag shader 3
    
    // Transformation matrices

    // We want to scale the shape then rotate it counter-clockwise a little every frame along the z-axis
    // Order, right to left: scale <-- rotate => left to right: rotate * scale
    glm::mat4 transform = glm::mat4(1.0f); // First create an identity matrix with w=1 (homogeneous coord) for scaling
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (delta_time)/1000.0f, glm::vec3(1, 1, 1));
    transform = glm::scale(transform, glm::vec3(.5, .5, .5));  

    unsigned int transformLoc = glGetUniformLocation(_shader->ID, "transform"); 
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform)); 

    glBindVertexArray(_VAO_ID);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glm::mat4 transform2 = glm::mat4(1.0f); // First create an identity matrix with w=1 (homogeneous coord) for scaling
    transform2 = glm::translate(transform2, glm::vec3(-0.5f, 0.5f, 0.0f));
    transform2 = glm::rotate(transform2, delta_time/1000.0f, glm::vec3(-1, -1, -1));
    transform2 = glm::scale(transform2, glm::vec3(.75, .75, .75));  

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
    glBindVertexArray(_VAO_ID);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

#endif