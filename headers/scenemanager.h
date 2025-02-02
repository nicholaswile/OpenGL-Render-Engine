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

std::vector<Scene*> SceneManager::scenes = std::vector<Scene*>();
int SceneManager::current_scene = 0;

void SceneManager::init() {
    scenes.push_back(new Scene1());
    scenes.push_back(new Scene2());
    scenes[current_scene]->load();
}

void SceneManager::load_next() {
    scenes[current_scene]->unload();
    current_scene = ((current_scene+1)%scenes.size());
    scenes[current_scene]->load();
}

void SceneManager::render(float deltatime) {
    scenes[current_scene]->render(deltatime);
}