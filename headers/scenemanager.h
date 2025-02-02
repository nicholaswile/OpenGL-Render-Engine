# ifndef SCENEMANAGER_H
# define SCENEMANAGER_H

// Scenes
#include "scene.h"
#include "scene1.h"
#include "scene2.h"

class SceneManager {
public:
    static int current_scene;
    static std::vector<Scene*> scenes;
    static void init(); 
    static void load_next();
    static void render(float deltatime);
};


#endif