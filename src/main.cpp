#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h> // Manages function pointers for OpenGL
#include <iostream>
#include <cmath> // for sin()
#include <vector>

// Custom
#include "../headers/shader.h"

const char* TITLE = "NikoGL";
const int WIDTH = 800, HEIGHT = 600;

void err_msg(const char* msg);

void process_input(SDL_Window *window);
bool SDL_GL_WindowShouldClose = false;
void render(const std::vector<Shader*> &shaders, const unsigned int VAO_IDs[]);

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
    
    // Query the number of vertex attributes limited by the hardware (the number of 4-component input variables the shader program can take on the GPU)
    int num_attrs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &num_attrs);
    std::cout << "Max num of vertex attributes supported by hardware: " << num_attrs << "\n"; // This is 16 on my hardware.

    // Create resources
    float vertices[] = {
        -0.50f, -.50f, 0.00f, // bottom left
        0.50f, -0.50f, 0.00f, // bottom right
        0.50f, 0.50f, 0.00f, // top right
        -0.5f, 0.5f, 0.00f // top left
    };


    // Test 1 - draw 2 triangles next to each other
    float tri1_verts[] = {
        // tri 1 verts              // tri 1 colors
        -.6f, -.5f, .0f,            1.0f, 0.0f, 0.0f,
        -.1f, -.5f, .0f,            0.0f, 1.0f, 0.0f,
        -.35f, .5f, .0f,            0.0f, 0.0f, 1.0f,
    };

    float tri2_verts[] = {
         // tri 2
        .1f, -.5f, .0f,
        .6f, -.5f, .0f,
        .35f, .5f, .0f,
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
    Shader* shader1 = new Shader("shaders/vert1.glsl", "shaders/frag1.glsl");
    Shader* shader2 = new Shader("shaders/vert1.glsl", "shaders/frag2.glsl");
    std::vector<Shader*> shaders = std::vector<Shader*>();
    shaders.push_back(shader1);
    shaders.push_back(shader2);

    // Create vertex attribute object for configuring settings of how each vertex object is drawn
    unsigned int VAO_ID;
    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);

    // Configure buffer array with the created index
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    // Copy the user-defined vertex data to the buffer memory
    // Use static draw because this data is set once and not changed, else use DYNAMIC_DRAW
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri1_verts), tri1_verts, GL_STATIC_DRAW);
    // Now the data has been stored on the GPU

    // Copy index array into element buffer to tell which vertices are used by a triangle
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret vertex data
    // Parameters: location=0 (set position in shader to 0), size of attribute=vec3 (3 values), type of data is vec* float, whether data should be normalized [0,1], stride (space between vertex attributes, 3 floats = 3*sizeof(float=32 bits) to get next vec3, offset of start of position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Test 2 - draw 2 triangles using 2 different VAOs and VBOs
    unsigned int VBO_IDs[2], VAO_IDs[2];
    glGenBuffers(2, VBO_IDs);
    glGenVertexArrays(2, VAO_IDs);

    glBindVertexArray(VAO_IDs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_IDs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri1_verts), tri1_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Add a pointer for color 
    // There's 6 floats for each vertex, the first 3 go to pos, the second 3 go to color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO_IDs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_IDs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri2_verts), tri2_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ----------------------------------------------------------------------------------------

    while (!SDL_GL_WindowShouldClose) {
        // Input
        process_input(window);

        // Rendering
        render(shaders, VAO_IDs);

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

void render(const std::vector<Shader*> &shaders, const unsigned int VAO_ID[]) {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Activate shader program
    shaders[0]->use();
    glBindVertexArray(VAO_ID[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Activate shader program
    shaders[1]->use();

    // Update uniform color
    float time = SDL_GetTicks()*1000; // MS --> S
    float green_val = sin(time)/2.0f+0.5f;
    
    // Can't use the SetFloat function as that only takes a single float rather than a vec4. Fix this later...
    int vert_color_location = glGetUniformLocation(shaders[1]->ID, "globalColor");
    glUniform4f(vert_color_location, 0, green_val, 0, 1.0f);
    
    glBindVertexArray(VAO_ID[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Draw 6 indices (representing vertices) which are all non-negative ints
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}