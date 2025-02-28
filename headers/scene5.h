#ifndef Scene5_H
#define Scene5_H

// Custom
#include "scene.h"
#include "fpsplayer.h"

class Scene5 : public Scene {
private:
    Shader* _shader;
    unsigned int _VAO_ID;
    unsigned int _VBO_ID;
    unsigned int _EBO_ID;

    // Our UI state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
    bool render_ui = false;

    // Scene specific
    glm::vec3 _cube_positions [10];
    glm::vec3 _cube_rotations [10];

    // Camera* _cam;
    FPSPlayer* _fpsPlayer;

public:
    float mixer;
    Scene5() {}
    ~Scene5() {
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);
    }
    void load() override;

    void unload() override{
        glDeleteVertexArrays(1, &_VAO_ID);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);

        _fpsPlayer->reset();
    }

    void render(float delta_time) override;
    void display_ui() override;
    void process_input(SDL_Event &event, float delta_time, bool key_down) override;
};

#endif