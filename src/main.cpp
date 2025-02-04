#include "../headers/scenemanager.h"
#include "../headers/config.h"

// SDL
#include <SDL.h>

void err_msg(const char* msg);
void process_input(SDL_Window *window);
bool SDL_GL_WindowShouldClose = false;

char* TITLE = "NikoGL";
int WIDTH = 1920, HEIGHT = 1080;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // I'm using OpenGL 4.6
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_Window *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        err_msg("Failed to Create SDL window");
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (!glContext) {
        err_msg("Failed to create OpenGL context");
        return -1;
    }

    // Initialize GLAD before calling OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        err_msg("Failed to initialize GLAD");
        return -1;
    }

    // Currently the renderer is same size as SDL Window. Could make it smaller to fit other things in the window later... 
    glViewport(0, 0, WIDTH, HEIGHT);

    // Query the number of vertex attributes limited by the hardware (the number of 4-component input variables the shader program can take on the GPU, for mine it's 16)
    int num_attrs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &num_attrs);
    std::cout << "Max num of vertex attributes supported by hardware: " << num_attrs << "\n"; // This is 16 on my hardware.

    // Depth check
    glEnable(GL_DEPTH_TEST);  

    // Note: Want to send as much data to GPU at once as possible for speed, because CPU --> GPU is slow. Use buffer to store data in memory for GPU

    SceneManager::init();
    
    // Main game loop
    while (!SDL_GL_WindowShouldClose) {
        // Input
        process_input(window);

        // Rendering
        SceneManager::render((float)SDL_GetTicks());

        // Display
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void err_msg(const char* msg) {
    std::cout << msg << "! SDL_Error: " << SDL_GetError() << "\n";
    SDL_Quit();
}

void process_input(SDL_Window *window)
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        SDL_GL_WindowShouldClose = (event.type == SDL_QUIT);

        if (event.type != SDL_KEYDOWN) return;

        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:       SDL_GL_WindowShouldClose = true;                        break;
            case SDLK_1:            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);              break;  // Wireframe
            case SDLK_2:            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);              break;  // Polygon

            // Eventually i'll make a seperate input class and handle input differently depending on scene
            case SDLK_UP:           if (Scene2::mixer+0.01f < 1.0f) Scene2::mixer += 0.01f; break; 
            case SDLK_DOWN:         if (Scene2::mixer-0.01f > 0.0f) Scene2::mixer -= 0.01f; break;
            case SDLK_RIGHT:        SceneManager::load_next();                              break;
        }  
    }
}