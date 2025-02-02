#ifndef SCENE_H
#define SCENE_H

// Custom
#include "shader.h"
#include "texture.h"

// OpenGL
#include <glad/glad.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// CPP
#include <string>
#include <vector>

class Scene {
protected:
    virtual ~Scene() {};
    virtual void create() {};
    virtual void render(float delta_time) {};
};

#endif