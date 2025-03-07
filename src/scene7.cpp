#include "../headers/Scene7.h"

void Scene7::load() {

    // Shaders
    _boxShader = new Shader("shaders/lighting/7-VertMVP.glsl", "shaders/lighting/7-FragPhong.glsl");
    _lightShader = new Shader("shaders/lighting/7-VertMVP.glsl", "shaders/lighting/7-FragLight.glsl"); 

    float vertices[] = {
        // Position           // Normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
   
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
   
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
   
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
   
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
   
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glGenBuffers(1, &_VBO_ID);                                                           

    glGenVertexArrays(1, &_VAO_ID_CUBE);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID);   
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);          
    glBindVertexArray(_VAO_ID_CUBE);
    
    // First 3 values (position) at location=0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Second 3 values (normal vectors) at location=1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)3);
    glEnableVertexAttribArray(1);
    
    // Use same vertex buffer for the light, but only care about the first 3 values (position)
    glGenVertexArrays(1, &_VAO_ID_LIGHT);
    glBindVertexArray(_VAO_ID_LIGHT);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO_ID);   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    
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

    _fpsPlayer = new FPSPlayer();
    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cam_front= glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
    float fov = 45.0f;
    float near_plane = .1f;
    float far_plane = 100.f;
    _fpsPlayer->_cam = new Camera(cam_pos, cam_front, cam_up, fov, near_plane, far_plane);

}

void Scene7::render(float delta_time) {

    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Shader setup
    _boxShader->use();
    _boxShader->set_vec3("BoxColor", _boxColor); 
    _boxShader->set_vec3("LightColor", _lightColor); 
    _boxShader->set_float("AmbientStrength", _ambientStrength);
    _boxShader->set_vec3("LightPos", _lightPos);

    glm::mat4 model;
    glm::mat4 view = _fpsPlayer->_cam->getViewMatrix();
    glm::mat4 projection = _fpsPlayer->_cam->getPerspectiveMatrix();

    // Transformation matrices
    for (unsigned int i = 0; i < sizeof(_cube_positions)/(3*sizeof(float)); i++) {

        // Model
        model = glm::mat4(1.0f); 
        model = glm::translate(model, _cube_positions[i]);
        float timescaled = (float)SDL_GetTicks()/1000.0f;
        float angle = 0.5 * (i+1) * timescaled;
        model = glm::rotate(model, angle, _cube_rotations[i]);

        unsigned int model_loc = glGetUniformLocation(_boxShader->ID, "model"); 
        unsigned int view_loc = glGetUniformLocation(_boxShader->ID, "view"); 
        unsigned int proj_loc = glGetUniformLocation(_boxShader->ID, "projection"); 
        
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view)); 
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection)); 
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model)); 

        glBindVertexArray(_VAO_ID_CUBE);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Single Light
    _lightShader->use();
    _lightShader->set_vec3("LightColor", _lightColor);
    unsigned int view_loc = glGetUniformLocation(_lightShader->ID, "view"); 
    unsigned int proj_loc = glGetUniformLocation(_lightShader->ID, "projection"); 
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view)); 
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection)); 
    model = glm::mat4(1.f);
    model = glm::translate(model, _lightPos); 
    model = glm::scale(model, glm::vec3(.2f));
    unsigned int model_loc = glGetUniformLocation(_lightShader->ID, "model"); 
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model)); 
    glBindVertexArray(_VAO_ID_LIGHT);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    if (render_ui)
        display_ui();

}

void Scene7::process_input(SDL_Event &event, float delta_time, bool key_down) {
    if (key_down) {
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_SPACE]) {
            render_ui = !render_ui;
            if (!render_ui) {
                _fpsPlayer->recenter_mouse();
                SDL_ShowCursor(SDL_DISABLE);
            }      
        }
    }

    // Render input every frame that the game is unpaused
    if (!render_ui)
        _fpsPlayer->process_input(event, delta_time);    
}

void Scene7::display_ui() {
     // Start the Dear ImGui frame
    if (render_ui) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    }

    if (render_ui) {

        {
            ImGui::Begin("NikoGL");                         
            ImGui::Text("Color");    
            ImGui::SliderFloat("Ambient Strength", &_ambientStrength, 0, 1.f);
            ImGui::ColorEdit3("Light color", (float*)&_lightColor); 
            ImGui::InputFloat3("Light pos", (float*)&_lightPos);
            ImGui::ColorEdit3("Box color", (float*)&_boxColor); 
            ImGui::ColorEdit3("Background color", (float*)&clear_color); 
            ImGui::Text("Performance average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        if (render_ui)
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}