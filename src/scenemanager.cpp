#include "../headers/scenemanager.h"

std::vector<Scene*> SceneManager::scenes = std::vector<Scene*>();
int SceneManager::current_scene = 2;

void SceneManager::init() {
    scenes.push_back(new Scene1());
    scenes.push_back(new Scene2());
    scenes.push_back(new Scene3());
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