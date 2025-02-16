#include "../headers/fpsplayer.h"

void FPSPlayer::process_input(SDL_Event &event, float delta_time) {
    glm::vec3 new_pos = _cam->position;
    const float cam_speed = .01f*(delta_time);
    const float sensitivity = 0.25f;

    // Walk around
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        new_pos = _cam->position + cam_speed * _cam->direction;
    }
    if (keystate[SDL_SCANCODE_S]) {
        new_pos = _cam->position - cam_speed * _cam->direction;
    }
    if (keystate[SDL_SCANCODE_A]) {
        new_pos = _cam->position - cam_speed * _cam->camRight(); 
    }
    if (keystate[SDL_SCANCODE_D]) {
        new_pos = _cam->position + cam_speed * _cam->camRight();  
    }

    _cam->position = new_pos;

    // Look around 
    int currentMouseX, currentMouseY;
    SDL_GetMouseState(&currentMouseX, &currentMouseY);
    int offsetMouseX = currentMouseX - _prevMouseX;
    int offsetMouseY = _prevMouseY - currentMouseY;

    _prevMouseX = currentMouseX;
    _prevMouseY = currentMouseY;
    offsetMouseX *= sensitivity;
    offsetMouseY *= sensitivity;
    _cam->yaw += offsetMouseX;
    _cam->pitch += offsetMouseY;

    // Constrain
    if (_cam->pitch > 89.f)
        _cam->pitch = 89.f;
    if (_cam->pitch < -89.f)
        _cam->pitch = -89.f;

    _cam->yaw = glm::mod(_cam->yaw + offsetMouseX, 360.f);
    
    glm::vec3 direction;
    direction.x = glm::cos(glm::radians(_cam->yaw)) * glm::cos(glm::radians(_cam->pitch));
    direction.y = glm::sin(glm::radians(_cam->pitch));
    direction.z = glm::sin(glm::radians(_cam->yaw)) * glm::cos(glm::radians(_cam->pitch));

    _cam->direction = glm::normalize(direction);
    
    // Zoom in
    float fov = _cam->fov;
    if (event.type == SDL_MOUSEWHEEL) {
        fov -= event.wheel.y;
        if (fov < 1) fov = 1;
        else if (fov > 45) fov = 45;
    }
    _cam->fov = fov;
}