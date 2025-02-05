#ifndef Scene5_H
#define Scene5_H

// Custom
#include "scene.h"
#include "camera.h"

class Scene5 : public Scene {
private:
    Shader* _shader;
    unsigned int _VAO_ID;
    unsigned int _VBO_ID;
    unsigned int _EBO_ID;

    // Scene specific
    glm::vec3 _cube_positions [10];
    glm::vec3 _cube_rotations [10];

    Camera* _cam;
    int _prevMouseX = -1;
    int _prevMouseY = -1;

public:
    float mixer;
    Scene5() {}
    ~Scene5() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
    }
    void load();

    void unload() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
        _cam->reset();
        _prevMouseX = WIDTH/2;
        _prevMouseY = HEIGHT/2;
    }

    void render(float delta_time);
    void process_input(SDL_Event &event, float delta_time);
};

#endif