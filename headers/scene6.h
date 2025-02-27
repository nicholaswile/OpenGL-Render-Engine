#ifndef Scene6_H
#define Scene6_H

// Custom
#include "scene.h"
#include "fpsplayer.h"

class Scene6: public Scene {
private:
    Shader* _boxShader;
    Shader* _lightShader;
    unsigned int _VAO_ID_CUBE, _VAO_ID_LIGHT;
    unsigned int _VBO_ID;
    unsigned int _EBO_ID;

    // Our UI state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);
    bool render_ui = false;

    // Camera* _cam;
    FPSPlayer* _fpsPlayer;

    glm::vec3 _lightPos = glm::vec3(1.2f, 1.f, 2.f);
    glm::vec3 _lightColor = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 _boxColor = glm::vec3(1.f,182.f/255.f,193.f/255.f);

    glm::vec3 _cube_positions[10];
    glm::vec3 _cube_rotations[10];

public:
    float mixer;
    Scene6() {}
    ~Scene6() {
        glDeleteVertexArrays(1, &_VAO_ID_CUBE);
        glDeleteVertexArrays(1, &_VAO_ID_LIGHT);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);

        _fpsPlayer->reset();

        delete _fpsPlayer;
        delete _boxShader;
    }
    void load() override;

    void unload() override{
        glDeleteVertexArrays(1, &_VAO_ID_CUBE);
        glDeleteVertexArrays(1, &_VAO_ID_LIGHT);
        glDeleteBuffers(1, &_VBO_ID);
        glDeleteBuffers(1, &_EBO_ID);

        _fpsPlayer->reset();

        delete _fpsPlayer;
        delete _boxShader;
    }

    void render(float delta_time) override;
    void display_ui() override;
    void process_input(SDL_Event &event, float delta_time, bool key_down) override;
};

#endif