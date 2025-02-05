// GLM
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    glm::vec3 _initialPos;
    glm::vec3 _initialDir;
    glm::vec3 _initialUp;

public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;

    float pitch; 
    float yaw;
    float roll;

    Camera(glm::vec3 position=glm::vec3(0, 0, 3.0f), glm::vec3 direction=glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f)) {
        this->position = position;
        _initialPos = position;
        this->direction = direction;
        _initialDir = direction;
        this->up = up;
        _initialUp = up;

        pitch = 0.f;
        yaw = -90.f;
        roll = 0.f;

    }

    inline glm::vec3 camRight() {return glm::normalize(glm::cross(direction, up));}
    glm::vec3 camUp() {return glm::normalize(glm::cross(direction, camRight()));}

    // Typically we'd want the camera to look forward. 
    // However, we may want it to track an object or stay looking at the same spot, which is why we pass a target.
    inline glm::mat4 lookAt(glm::vec3 target) {return glm::lookAt(position, target, up);}

    void reset() {
        position = _initialPos;
        direction = _initialDir;
        up = _initialUp;
    }

};

#endif