#ifndef FPSCAM_H
#define FPSCAM_H

#include "camera.h"

class FPSPlayer {
private:
    int _prevMouseX = -1;
    int _prevMouseY = -1;

public:
    Camera* _cam;
    FPSPlayer() {
        SDL_GetMouseState(&_prevMouseX, &_prevMouseY);
    }
    void process_input(SDL_Event &event, float delta_time);
    void reset() {
        _cam->reset();
        _prevMouseX = WIDTH/2;
        _prevMouseY = HEIGHT/2;
    }
};

#endif