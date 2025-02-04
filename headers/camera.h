// GLM
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    glm::vec3 _position;
    glm::vec3 _target;
    glm::vec3 _up;

public:
    Camera(glm::vec3 position=glm::vec3(0, 0, 0), glm::vec3 target=glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f)) {
        _position = position;
        _target = target;
        set_up(up);
    }

    glm::vec3 get_position() {return _position;};
    void set_position(glm::vec3 position) {_position = position;}

    glm::vec3 get_target() {return _target;}
    void set_target(glm::vec3 target) {_target = target;}

    glm::vec3 get_up() {return _up;}
    void set_up(glm::vec3 up) {_up = up;}

    inline glm::vec3 camDirection() {return glm::normalize(_position - _target);}
    inline glm::vec3 camRight() {return glm::normalize(glm::cross(_up, camDirection()));}
    glm::vec3 camUp() {return glm::normalize(glm::cross(camDirection(), camRight()));}

    inline glm::mat4 lookAt() {return glm::lookAt(_position, _target, _up);}

};

#endif