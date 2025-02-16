#ifndef CAMERA_H
#define CAMERA_H

// Custom
#include "config.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// SDL
#include <SDL.h>

class Camera {
private:
    glm::vec3 _initialPos;
    glm::vec3 _initialDir;
    glm::vec3 _initialUp;

public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    float fov;
    float near_plane;
    float far_plane;

    float pitch; 
    float yaw;
    float roll;

    Camera(glm::vec3 position=glm::vec3(0, 0, 3.0f), glm::vec3 direction=glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f), float fov=45.f, float near_plane=.1f, float far_plane=100.f) {
        this->position = position;
        _initialPos = position;
        this->direction = direction;
        _initialDir = direction;
        this->up = up;
        _initialUp = up;
        this->fov = fov;
        this->near_plane = near_plane;
        this->far_plane = far_plane;
        pitch = 0.f;
        yaw = -90.f;
        roll = 0.f; 
    }

    inline glm::vec3 camRight() {return glm::normalize(glm::cross(direction, up));}
    glm::vec3 camUp() {return glm::normalize(glm::cross(direction, camRight()));}

    // Typically we'd want the camera to look forward. 
    // However, we may want it to track an object or stay looking at the same spot, which is why we pass a target.
    inline glm::mat4 lookAt(glm::vec3 target) {return glm::lookAt(position, target, up);}

    virtual void reset() {
        position = _initialPos;
        direction = _initialDir;
        up = _initialUp;
    }

    glm::mat4 getViewMatrix() { return lookAt(position+direction);}

    glm::mat4 getPerspectiveMatrix() { return glm::perspective(glm::radians(fov), (float)WIDTH/HEIGHT, near_plane, far_plane);}
    
};

#endif