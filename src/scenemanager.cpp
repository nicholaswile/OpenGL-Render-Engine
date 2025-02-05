#include "../headers/scenemanager.h"

std::vector<Scene*> SceneManager::scenes = std::vector<Scene*>();
int SceneManager::current_scene = 0;

void SceneManager::init() {
    scenes.push_back(new Scene1());
    scenes.push_back(new Scene2());
    scenes.push_back(new Scene3());
    scenes.push_back(new Scene4());
    scenes.push_back(new Scene5());
    
    current_scene = scenes.size()-1;
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

void SceneManager::process_input(SDL_Event &event, float delta_time) {
    scenes[current_scene]->process_input(event, delta_time);
}