# ifndef SCENEMANAGER_H
# define SCENEMANAGER_H

// Scenes
#include "../headers/scene.h"
#include "../scenes/scene1.h"
#include "../scenes/scene2.h"

class SceneManager {
public:
    static int current_scene;
    static std::vector<Scene*> scenes;
    static void init(); 
    static void load_next();
    static void render(float deltatime);
};

#endif