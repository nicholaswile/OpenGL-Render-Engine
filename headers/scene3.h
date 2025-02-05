#ifndef SCENE3_H
#define SCENE3_H

// Custom
#include "scene.h"

class Scene3 : public Scene {
private:
    Shader* _shader;
    unsigned int _VAO_ID;
    unsigned int _VBO_ID;
    unsigned int _EBO_ID;

    // Scene specific
    glm::vec3 cube_positions [10];
    glm::vec3 cube_rotations [10];

public:
    float mixer;
    Scene3() {}
    ~Scene3() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
    }
    void load();
    void unload() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
        mixer = 0.5f; // Otherwise persists across scenes, which is cool but not what I want
    }
    void render(float delta_time);
    void process_input(SDL_Event &event, float delta_time);
};

#endif