#ifndef SCENE_H
#define SCENE_H

// Custom
#include "shader.h"
#include "texture.h"
#include "config.h"

// OpenGL
#include <glad/glad.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// SDL
#include <SDL.h>

// Dear ImGui
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

// CPP
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>

class Scene {
public:
    virtual ~Scene() {};
    virtual void load() {};
    virtual void unload() {};
    virtual void render(float delta_time) {};
    virtual void display_ui() {};
    virtual void process_input(SDL_Event &event, float delta_time, bool key_down) {};
};

#endif