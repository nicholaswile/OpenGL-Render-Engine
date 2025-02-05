#include "../headers/Scene4.h"

void Scene4::load() {
    // Shaders
    _shader = new Shader("shaders/vert5.glsl", "shaders/frag4.glsl"); // texture shader

    // Create mesh (might make this a class later)
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Copy the vertex and index data onto the GPU
    glGenBuffers(1, &_VBO_ID);                                                           // Vertex buffer object
    glGenVertexArrays(1, &_VAO_ID);                                                      // Vertex attribute object (settings, configs OpenGL how to read the data in VBO)
    glGenBuffers(1, &_EBO_ID);                                                           // Element buffer object tells OpenGL indices that make up each triangle

    glBindVertexArray(_VAO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID);                                              // Configure buffer array 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);          // Copy data to buffer memory

    // Tell OpenGL how to interpret vertex data
    // Parameters: location=0 (set position in shader to 0), size of attribute=vec3 (3 values), type of data is vec* float, whether data should be normalized [0,1], stride (space between vertex attributes, 3 floats = 3*sizeof(float=32 bits) to get next vec3, offset of start of position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // will give layout(location = 0) in shaders. 

    // Create new vertex attribute for this texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1); // will give layout(location = 2) in shaders. 

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

    mixer = 0.5f;

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 10; i++) 
        _cube_rotations[i] = glm::vec3(float(rand()%10)/10.0f, float(rand()%10)/10.0f, float(rand()%10)/10.0f);

    _cube_positions[0] = glm::vec3( 0.0f,  0.0f,  0.0f);
    _cube_positions[1] = glm::vec3( 2.0f,  5.0f, -15.0f);
    _cube_positions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
    _cube_positions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
    _cube_positions[4] = glm::vec3( 2.4f, -0.4f, -3.5f);
    _cube_positions[5] = glm::vec3(-1.7f,  3.0f, -7.5f);
    _cube_positions[6] = glm::vec3( 1.3f, -2.0f, -2.5f);
    _cube_positions[7] = glm::vec3( 1.5f,  2.0f, -2.5f);
    _cube_positions[8] = glm::vec3( 1.5f,  0.2f, -1.5f);
    _cube_positions[9] = glm::vec3(-1.3f,  1.0f, -1.5f);          

    _cam = new Camera();

}

void Scene4::render(float delta_time) {
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->use();
    _shader->set_float("mixer", mixer); 

    const float radius = 10.0f;
    
    // Transformation matrices
    for (unsigned int i = 0; i < sizeof(_cube_positions)/(3*sizeof(float)); i++) {

        // Model
        glm::mat4 model = glm::mat4(1.0f); 
        model = glm::translate(model, _cube_positions[i]);
        float timescaled = (float)SDL_GetTicks() / 1000.0f;
        float angle = 0.5 * (i+1) * timescaled;
        model = glm::rotate(model, angle, _cube_rotations[i]);

        // View
        float camx = sin(timescaled) * radius;
        float camz = cos(timescaled) * radius;
        _cam->position = glm::vec3(camx, 0.0f, camz);
        glm::mat4 view = _cam->lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
        
        // Perspective
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)WIDTH/HEIGHT, 0.1f, 100.f);

        unsigned int model_loc = glGetUniformLocation(_shader->ID, "model"); 
        unsigned int view_loc = glGetUniformLocation(_shader->ID, "view"); 
        unsigned int proj_loc = glGetUniformLocation(_shader->ID, "projection"); 
        
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view)); 
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection)); 
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model)); 

        glBindVertexArray(_VAO_ID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Scene4::process_input(SDL_Event &event, float delta_time) {

}