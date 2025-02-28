#ifndef SCENE2_H
#define SCENE2_H

// Custom
#include "scene.h"

class Scene2 : public Scene {
private:
    Shader* _shader;
    unsigned int _VAO_ID;
    unsigned int _VBO_ID;
    unsigned int _EBO_ID;
public:
    static float mixer;
    Scene2() {}
    ~Scene2() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
    }
    void load() override;
    void unload() override{
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
        mixer = 0.5f; // Otherwise persists across scenes, which is cool but not what I want
    }
    void render(float delta_time) override;
    void display_ui() override {};
    void process_input(SDL_Event &event, float delta_time, bool key_down) override;
};

#endif