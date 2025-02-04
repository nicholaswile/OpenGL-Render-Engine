#ifndef Scene4_H
#define Scene4_H

// Custom
#include "scene.h"
#include "camera.h"

class Scene4 : public Scene {
private:
    Shader* _shader;
    unsigned int _VAO_ID;
    unsigned int _VBO_ID;
    unsigned int _EBO_ID;

    // Scene specific
    glm::vec3 _cube_positions [10];
    glm::vec3 _cube_rotations [10];

    Camera* _cam;

public:
    float mixer;
    Scene4() {}
    ~Scene4() {
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
};

#endif