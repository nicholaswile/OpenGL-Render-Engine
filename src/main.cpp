#include <SDL.h>
#include <SDL_image.h>
#include <glad/glad.h> // Manages function pointers for OpenGL
#include <iostream>
#include <cmath> // for sin()
#include <vector>

// Custom
#include "../headers/shader.h"

// External
#include "../headers/stb_image.h"

const char* TITLE = "NikoGL";
const int WIDTH = 800, HEIGHT = 600;

void err_msg(const char* msg);

void process_input(SDL_Window *window, float &mixer);
bool SDL_GL_WindowShouldClose = false;
void render(const std::vector<Shader*> &shaders, const unsigned int VAO_IDs[]);
void render(const std::vector<Shader*> &shaders, const unsigned int VAO_ID, const unsigned int textures[], const float mixer);

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
    
    // Query the number of vertex attributes limited by the hardware (the number of 4-component input variables the shader program can take on the GPU, for mine it's 16)
    int num_attrs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &num_attrs);
    std::cout << "Max num of vertex attributes supported by hardware: " << num_attrs << "\n"; // This is 16 on my hardware.

    // Create shaders to process data on GPU
    // Shader* shader1 = new Shader("shaders/vert1.glsl", "shaders/frag1.glsl");
    // Shader* shader2 = new Shader("shaders/vert2.glsl", "shaders/frag2.glsl");
    Shader* shader3 = new Shader("shaders/vert3.glsl", "shaders/frag3.glsl"); // texture shader
    std::vector<Shader*> shaders = std::vector<Shader*>();
    // shaders.push_back(shader1);
    // shaders.push_back(shader2);
    shaders.push_back(shader3);

    // Rectangle for mapping a texture on
    float vertices[] = {
        // positions              // colors               // tex coords (u,v)
        -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,       0.0f, 0.0f,                 // bottom left
         0.5f, -0.5f, 0.0f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,                 // bottom right
         0.5f,  0.5f, 0.0f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,                 // top right
        -0.5f,  0.5f, 0.0f,       1.0f, 0.0f, 1.0f,       0.0f, 1.0f,                 // top left
    };

    unsigned int indices[] = {
        0, 1, 3,    // first triangle
        1, 2, 3     // second triangle
    };

    // // Test 1 - draw 2 triangles next to each other
    // float tri1_verts[] = {
    //     // tri 1 verts              // tri 1 colors
    //     -.6f, -.5f, .0f,            1.0f, 0.0f, 0.0f,
    //     -.1f, -.5f, .0f,            0.0f, 1.0f, 0.0f,
    //     -.35f, .5f, .0f,            0.0f, 0.0f, 1.0f,
    // };

    // float tri2_verts[] = {
    //      // tri 2
    //     .1f, -.5f, .0f,
    //     .6f, -.5f, .0f,
    //     .35f, .5f, .0f,
    // };


    // Copy the vertex and index data onto the GPU
    unsigned int VBO_ID, VAO_ID, EBO_ID;
    glGenBuffers(1, &VBO_ID);                                                           // Vertex buffer object
    glGenVertexArrays(1, &VAO_ID);                                                      // Vertex attribute object (settings, configs OpenGL how to read the data in VBO)
    glGenBuffers(1, &EBO_ID);                                                           // Element buffer object tells OpenGL indices that make up each triangle

    glBindVertexArray(VAO_ID);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);                                              // Configure buffer array 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);          // Copy data to buffer memory

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);                                      // Configure element buffer array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);    // Copy data to memory

    // Tell OpenGL how to interpret vertex data
    // Parameters: location=0 (set position in shader to 0), size of attribute=vec3 (3 values), type of data is vec* float, whether data should be normalized [0,1], stride (space between vertex attributes, 3 floats = 3*sizeof(float=32 bits) to get next vec3, offset of start of position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // will give layout(location = 0) in shaders. 

    // Add a pointer for color 
    // There's 6 floats for each vertex, the first 3 go to pos, the second 3 go to color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); // will give layout(location = 1) in shaders. 
    
    // Create new vertex attribute for this texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2); // will give layout(location = 2) in shaders. 

    // Test 2 - draw 2 triangles using 2 different VAOs and VBOs
    //glBufferData(GL_ARRAY_BUFFER, sizeof(tri1_verts), tri1_verts, GL_STATIC_DRAW);
    // unsigned int VBO_IDs[2], VAO_IDs[2];
    // glGenBuffers(2, VBO_IDs);
    // glGenVertexArrays(2, VAO_IDs);

    // glBindVertexArray(VAO_IDs[0]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO_IDs[0]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(tri1_verts), tri1_verts, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // glBindVertexArray(VAO_IDs[1]);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO_IDs[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(tri2_verts), tri2_verts, GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    unsigned int textures[2];
    glGenTextures(2, textures); // Binds num textures to texture array.
   
    // TEXTURE 1 -------------------------------------------
    // configure settings
    // wrapping
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // horizontal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // vertical
    // filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // minifcation using nearest sampling with linear mipmap selection
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // magnification using nearest sampling (jagged but i think looks clearer)

    // Create textures
    int width, height, nChannels;
    // This function fills those variables above with the correct data
    const char* filename = "textures/container.jpg";
    unsigned char *data = stbi_load(filename, &width, &height, &nChannels, 0);
    if (data) {
        std::string dims = "("+std::to_string(width)+","+std::to_string(height)+")";
        std::cout << "Succesfully loaded texture "<< filename << " " << dims << "\n";
        // glTexImage2D - currently bound texture object has texture image attached to it
        // specifies texture target (generates texture on object bound at that target), mipmap level, color format, width/height, ignore, format and datatype of source image, actual image data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture "<< filename << "\n";
    }
    // cleanup after generating texture and mipmaps by freeing image memory
    stbi_image_free(data);

    // TEXTURE 2 -------------------------------------------
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // horizontal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // vertical
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // minifcation using nearest sampling with linear mipmap selection
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // magnification using nearest sampling (jagged but i think looks clearer)

    const char* filename2 = "textures/sprigatito.png";
    data = stbi_load(filename2, &width, &height, &nChannels, 0);
    if (data) {
        std::string dims = "("+std::to_string(width)+","+std::to_string(height)+")";
        std::cout << "Succesfully loaded texture "<< filename2 << " " << dims << "\n";
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture "<< filename2 << "\n";
    }
    stbi_image_free(data);

    // Set uniform variables to appropriate texture
    shaders[0]->use();
    glUniform1i(glGetUniformLocation(shaders[0]->ID, "texture1"), 0); // Make sure each uniform sampler corresponds to correct texture unit
    shaders[0]->set_int("texture2", 1);

    // ----------------------------------------------------------------------------------------

    float mixer = 0.5;

    while (!SDL_GL_WindowShouldClose) {
        // Input
        process_input(window, mixer);

        // Rendering
        // render(shaders, VAO_IDs);
        render(shaders, VAO_ID, textures, mixer);

        // Display
        SDL_GL_SwapWindow(window);
    }

    // Free
    for (const auto &shader : shaders)
        delete shader;
    shaders.clear();

    glDeleteVertexArrays(1, &VAO_ID);
    glDeleteBuffers(1, &VBO_ID);
    glDeleteBuffers(1, &EBO_ID);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

void err_msg(const char* msg) {
    std::cout << msg << "! SDL_Error: " << SDL_GetError() << "\n";
    SDL_Quit();
}

void process_input(SDL_Window *window, float &mixer)
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        SDL_GL_WindowShouldClose = (event.type == SDL_QUIT);

        if (event.type != SDL_KEYDOWN) return;

        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:       SDL_GL_WindowShouldClose = true;                        break;
            case SDLK_1:            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);              break;  // Wireframe
            case SDLK_2:            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);              break;  // Polygon
            case SDLK_UP:           if (mixer+0.01f < 1.0f) mixer += 0.01f;                 break; 
            case SDLK_DOWN:         if (mixer-0.01f > 0.0f) mixer -= 0.01f;                 break;
        }  

    }
}

void render(const std::vector<Shader*> &shaders, const unsigned int VAO_ID, const unsigned int textures[], const float mixer) {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaders[0]->use();
    shaders[0]->set_float("mixer", mixer);

    glBindVertexArray(VAO_ID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// For using multiple VAOs
void render(const std::vector<Shader*> &shaders, const unsigned int VAO_ID[]) {
    float time = SDL_GetTicks()*1000; // MS --> S
    
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Activate shader program
    shaders[0]->use();
    glBindVertexArray(VAO_ID[0]);
    float hoffset = (sin(time));
    shaders[0]->set_float("hOffset", hoffset);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Activate shader program
    shaders[1]->use();

    // Update uniform color
    float green_val = sin(time)/2.0f+0.5f;
    
    // Can't use the SetFloat function as that only takes a single float rather than a vec4. Fix this later...
    int vert_color_location = glGetUniformLocation(shaders[1]->ID, "globalColor");
    glUniform4f(vert_color_location, 1.0f, green_val, 1.0f, 1.0f);
    
    glBindVertexArray(VAO_ID[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}