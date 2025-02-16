#include "../headers/scenemanager.h"
#include "../headers/config.h"

std::string TITLE = "NikoGL";
// Lowered resolution for screen recording on Windows
int WIDTH = 1920, HEIGHT = 1080;

float previous_time = 0.0f;
float current_time = 0.0f;
float delta_time = 0.0f;
float frame_limit = 1000.0f/60.f;
bool done = false;

void err_msg(const char* msg);
void process_input(SDL_Window *window, ImGuiIO &io);

// Main code
int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        err_msg("Failed to initialize SDL");
        return -1;
    }

    // I'm using OpenGL 4.6
    const char* glsl_version = "#version 460";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    
    SDL_Window* window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, window_flags);
    if (!window) {
        err_msg("Failed to create SDL window");
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        err_msg("Failed to create OpenGL context");
        return -1;
    }

    SDL_GL_MakeCurrent(window, glContext);
    SDL_GL_SetSwapInterval(0); // Enable vsync

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init(glsl_version);

    SDL_ShowCursor(SDL_DISABLE);

    SceneManager::init();

    // Main loop
    while (!done)
    {
        current_time = static_cast<float>(SDL_GetTicks());
        delta_time = (current_time-previous_time);
        previous_time = current_time;

        process_input(window, io);

        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        
        SceneManager::render(delta_time);

        // Display
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void err_msg(const char* msg) {
    std::cout << msg << "! SDL_Error: " << SDL_GetError() << "\n";
    SDL_Quit();
}

void process_input(SDL_Window *window, ImGuiIO &io)
{
    SDL_Event event;
    bool key_down = false;

    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        // Close window
        if (event.type == SDL_QUIT) {
            done = true;
        }
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) {
            done = true;
        }

        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        if (io.WantCaptureKeyboard || io.WantCaptureMouse)
            return;
        
        if (event.type != SDL_KEYDOWN) break;
        key_down = true;
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:       done = true;                                    break;
            case SDLK_1:            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      break;
            case SDLK_2:            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      break;
            case SDLK_RIGHT:        SceneManager::load_next();                      break;
        }
    }

    if (!io.WantCaptureKeyboard && !io.WantCaptureMouse)
        SceneManager::process_input(event, delta_time, key_down);

}