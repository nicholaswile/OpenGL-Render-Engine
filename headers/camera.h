// GLM
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {

public:
    glm::vec3 _position;
    glm::vec3 _direction;
    glm::vec3 _up;

    Camera(glm::vec3 position=glm::vec3(0, 0, 3.0f), glm::vec3 direction=glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f)) {
        _position = position;
        _direction = direction;
        _up = up;
    }

    inline glm::vec3 camRight() {return glm::normalize(glm::cross(_direction, _up));}
    glm::vec3 camUp() {return glm::normalize(glm::cross(_direction, camRight()));}

    // Typically we'd want the camera to look forward. 
    // However, we may want it to track an object or stay looking at the same spot, which is why we pass a target.
    inline glm::mat4 lookAt(glm::vec3 target) {return glm::lookAt(_position, target, _up);}

};

#endif