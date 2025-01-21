# OpenGL-Renderer
An OpenGL renderer using SDL for windowing and input processing. This is a work in progress. Press `1`/`2` to toggle between wireframe/filled polygon modes and `esc` to close. Press the `up` and `down` arrows to mix between background and foreground. Compiles on Windows with `mingw32-make`. 

### (Textures) A wild Sprigatito has appeared!~
|Empty Box|Mix|Sprigatito|
|:-------:|:--------:|:--------:|
|<img src="images/empty.png" style="height: 300px">|<img src="images/half.png" style="height: 300px">|<img src="images/full.png" style="height: 300px">

### (Shaders) Drawing triangles

|Solid|Solid|Wireframe|
|:---:|:----:|:------:|
|<img src="images/interpolated_color.png" style="height: 300px">|<img src="images/filled.png" style="height: 300px">|<img src="images/wireframe.png" style="height: 300px">|

<!-- 
For future reference: the VBO stores the vertices, the EBO stores the vertex indices for each triangle, and the VAO specifies the settings for OpenGL to draw the triangles.
-->

### Libraries and APIs
<li>
<a href="https://www.khronos.org/opengl/">OpenGL </a> Khronos Specifications. The Khronos Group Inc.
</li>
<li>
<a href="https://github.com/Dav1dde/glad">GLAD</a> to access OpenGL functions. David Herberth.
<li>
<a href="https://github.com/libsdl-org/SDL">Simple DirectMedia Layer</a> (SDL) for windowing and input. Sam Lantinga <slouken@libsdl.org>.
</li>
<li>
<a href="https://github.com/nothings/stb/blob/master/stb_image.h">stb_image.h</a> for loading textures in OpenGL. <a href="https://github.com/nothings">Sean Barrett</a>.
</li>
<!--
<li>
<a href="https://github.com/libsdl-org/SDL_image">SDL_image</a> for image decoding (might use later). Sam Lantinga <slouken@libsdl.org>
</li> 
-->

### Graphics
<li>
<a href="https://pokemon-scarlet-and-violet.fandom.com/wiki/Sprigatito">Sprigatito</a>
</li>
<li>
<a href="https://learnopengl.com/img/textures/container.jpg">Wooden Container</a>
</li>
