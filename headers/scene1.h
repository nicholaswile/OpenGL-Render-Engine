#ifndef SCENE1_H
#define SCENE1_H

// Custom
#include "scene.h"

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
    void process_input(SDL_Event &event, float delta_time);
};

#endif