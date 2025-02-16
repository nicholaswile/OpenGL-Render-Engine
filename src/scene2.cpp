#include "../headers/scene2.h"

float Scene2::mixer = 0.5f;

void Scene2::load() {

    // Shaders
    _shader = new Shader("shaders/vert3.glsl", "shaders/frag3.glsl"); // texture shader

    float vertices[] = {
        // positions              // colors               // tex coords (u,v)
                                                                                      //  front
        -0.5f, -0.5f, -0.5f,       0.0f, 0.0f, 1.0f,       0.0f, 0.0f,                // bottom left
         0.5f, -0.5f, -0.5f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,                // bottom right
         0.5f,  0.5f, -0.5f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,                // top right
        -0.5f,  0.5f, -0.5f,       1.0f, 0.0f, 1.0f,       0.0f, 1.0f,                // top left
        -0.5f, -0.5f,  0.5f,       0.0f, 0.0f, 1.0f,       0.0f, 0.0f,                // bottom left
         0.5f, -0.5f,  0.5f,       0.0f, 1.0f, 0.0f,       1.0f, 0.0f,                // bottom right
         0.5f,  0.5f,  0.5f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,                // top right
        -0.5f,  0.5f,  0.5f,       1.0f, 0.0f, 1.0f,       1.0f, 0.0f,                // top left
    };

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };

    // Copy the vertex and index data onto the GPU
    glGenBuffers(1, &_VBO_ID);                                                           // Vertex buffer object
    glGenVertexArrays(1, &_VAO_ID);                                                      // Vertex attribute object (settings, configs OpenGL how to read the data in VBO)
    glGenBuffers(1, &_EBO_ID);                                                           // Element buffer object tells OpenGL indices that make up each triangle

    glBindVertexArray(_VAO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID);                                              // Configure buffer array 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);           // Copy data to buffer memory

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO_ID);                                      // Configure element buffer array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);     // Copy data to memory

    // (layout=0) : Position (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // (layout=1) : Vert color (r, g, b)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);  

    // (layout=2) : Text coord (u, v)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);  
    
    // TEXTURES
    unsigned int textures[2];
    glGenTextures(2, textures);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    Texture::CreateTexture("textures/container.jpg", GL_TEXTURE0, GL_TEXTURE_2D, 0, GL_RGB, GL_RGB, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    Texture::CreateTexture("textures/sprigatito.png", GL_TEXTURE1, GL_TEXTURE_2D, 0, GL_RGBA, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST);

    // Set uniform variables to appropriate texture
    _shader->use();
    glUniform1i(glGetUniformLocation(_shader->ID, "texture1"), 0); // Make sure each uniform sampler corresponds to correct texture unit
    _shader->set_int("texture2", 1);

}

void Scene2::render(float delta_time) {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->use();
    _shader->set_float("mixer", mixer); 
    
    glBindVertexArray(_VAO_ID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Scene2::process_input(SDL_Event &event, float delta_time, bool key_down) {
    // if (event.type != SDL_KEYDOWN) return;

    // switch (event.key.keysym.sym) {
    //     case SDLK_UP:           if (mixer+0.01f < 1.0f) mixer += 0.01f; break; 
    //     case SDLK_DOWN:         if (mixer-0.01f > 0.0f) mixer -= 0.01f; break;
    // }  

    if (key_down) {
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_UP]) {
            if (mixer + 0.1f < 1.0f) mixer += 0.01f;
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            if (mixer + 0.1f < 1.0f) mixer -= 0.01f;
        }
    }
}