# ifndef SCENEMANAGER_H
# define SCENEMANAGER_H

// Scenes
#include "scene.h"
#include "scene1.h"
#include "scene2.h"
#include "scene3.h"
#include "scene4.h"

class SceneManager {
private:
    static int current_scene;
    static std::vector<Scene*> scenes;

public:
    static void init(); 
    static void load_next();
    static void render(float deltatime);
};


#endif