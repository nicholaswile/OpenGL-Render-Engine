# OpenGL-Renderer
An OpenGL renderer using SDL for windowing and input processing. This is a work in progress. Press 1/2 to toggle between wireframe/filled polygon modes and esc to close. Compiles on Windows with `mingw32-make`. 

You have to start somewhere...: 
<img src="images/interpolated_color.png">
|Filled|Wireframe|
|:----:|:------:|
|<img src="images/filled.png" style="height: 400px">|<img src="images/wireframe.png" style="height: 400px">|

For reference: the VBO stores the vertices, the EBO stores the vertex indices for each triangle, and the VAO specifies the settings for OpenGL to draw the triangles.

### Credits
<li>
<a href="https://www.khronos.org/opengl/">OpenGL </a> Khronos Specifications. Copyright (c) 2013-2020 The Khronos Group Inc.
</li>
<li>
<a href="https://github.com/Dav1dde/glad">GLAD</a> to access OpenGL functions. Copyright (c) 2013-2022 David Herberth
<li>
<a href="https://github.com/libsdl-org/SDL">Simple DirectMedia Layer</a> (SDL) for windowing and input. Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>
</li>
<li>
<a href="https://github.com/libsdl-org/SDL_image">SDL_image</a> for image decoding (might use later). Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>
</li> 
