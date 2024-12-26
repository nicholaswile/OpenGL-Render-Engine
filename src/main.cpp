#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h> // Manages function pointers for OpenGL
#include <iostream>

const char* TITLE = "NikoGL";
const int WIDTH = 800, HEIGHT = 600;

void err_msg(const char* msg);

void process_input(SDL_Window *window);
bool SDL_GL_WindowShouldClose = false;
void render();

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

    
    // ----------------------------------------------------------------------------------------
    // Want to send as much data to GPU at once as possible for speed, because CPU --> GPU is slow. Use buffer to store data in memory for GPU
    
    // Create resources
    float vertices[] = {
        -0.50f, -.50f, 0.00f, // bottom left
        0.50f, -0.50f, 0.00f, // bottom right
        0.50f, 0.50f, 0.00f, // top right
        -0.5f, 0.5f, 0.00f // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    // Create an index for the vertex buffer object
    unsigned int VBO_ID;
    glGenBuffers(1, &VBO_ID); 

    // Create an index for the element buffer object to which verts make up a triangle
    unsigned int EBO_ID;
    glGenBuffers(1, &EBO_ID);

    // Create shaders to process data on GPU

    // Position
    const char* vert_shader_code = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    // Final color
    const char* frag_shader_code = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "FragColor = vec4(255.0f/255.0f, 182.0f/255.0f, 193.0f/255.0f, 1.0f);\n"
    "}\0";

    // Create shader object / ID to store shader code
    unsigned int vert_shader_ID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int frag_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach shader code to shader object 
    glShaderSource(vert_shader_ID, 1, &vert_shader_code, NULL);
    glShaderSource(frag_shader_ID, 1, &frag_shader_code, NULL);
    // Compile dynamically at run-time
    glCompileShader(vert_shader_ID);
    glCompileShader(frag_shader_ID);

    // Check if compilation was successful
    int success;
    char info_log[512];
    glGetShaderiv(vert_shader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert_shader_ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << "\n";
    }
    glGetShaderiv(frag_shader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader_ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << "\n";
    }

    // Shader program to linx both vert and frag shaders
    unsigned int shader_ID = glCreateProgram();
    glAttachShader(shader_ID, vert_shader_ID);
    glAttachShader(shader_ID, frag_shader_ID);
    glLinkProgram(shader_ID);

    glGetProgramiv(shader_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << "\n";
    }

    // Delete shaders now that they've been linked
    glDeleteShader(vert_shader_ID);
    glDeleteShader(frag_shader_ID);

    // Create vertex attribute object for configuring settings of how each vertex object is drawn
    unsigned int VAO_ID;
    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);

    // Configure buffer array with the created index
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    // Copy the user-defined vertex data to the buffer memory
    // Use static draw because this data is set once and not changed, else use DYNAMIC_DRAW
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Now the data has been stored on the GPU

    // Copy index array into element buffer to tell which vertices are used by a triangle
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret vertex data
    // Parameters: location=0 (set position in shader to 0), size of attribute=vec3 (3 values), type of data is vec* float, whether data should be normalized [0,1], stride (space between vertex attributes, 3 floats = 3*sizeof(float=32 bits) to get next vec3, offset of start of position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Activate shader program
    glUseProgram(shader_ID);
    glBindVertexArray(VAO_ID);

    // ----------------------------------------------------------------------------------------

    while (!SDL_GL_WindowShouldClose) {
        // Input
        process_input(window);

        // Rendering
        render();

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
            case SDLK_ESCAPE:       SDL_GL_WindowShouldClose = true;                break;
            case SDLK_1:            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      break;  // Wireframe
            case SDLK_2:            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      break;  // Polygon
        }

    }
}

void render() {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw 6 indices (representing vertices) which are all non-negative ints
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}