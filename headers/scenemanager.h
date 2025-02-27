# ifndef SCENEMANAGER_H
# define SCENEMANAGER_H

// Scenes
#include "scene.h"
#include "scene1.h"
#include "scene2.h"
#include "scene3.h"
#include "scene4.h"
#include "scene5.h"
#include "scene6.h"

class SceneManager {
private:
    static int current_scene;
    static std::vector<Scene*> scenes;

public:
    static void init(); 
    static void load_next();
    static void render(float deltatime);
    static void process_input(SDL_Event &event, float delta_time, bool key_down);
};


#endif