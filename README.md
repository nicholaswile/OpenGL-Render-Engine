# OpenGL-Renderer
An OpenGL renderer using SDL for windowing and input processing. This is a work in progress. Compiles using the included `makefile`. 

## Scenes

### Diffuse Lighting

<img src="images/GL_Diffuse.gif">

Adds surface normals to the vertex buffer, then computes diffuse lighting finding the dot product between the light direction and the surface normal at that fragment. Reuses my shader from ambient lighting.

### Naive Global Illumination (Ambient Lighting)
<img src="images/GL_NaiveGI.gif">

Extends the color blending shader with an ambient strength factor, for basic ambient lighting, a naive approach to global illumination.

### Light / Color Blending
<img src="images/GL_AmbientLighting.gif">

Implemented solid color with light influence using separate shaders for box and light color. Notice how the base box color blends with the light color.

### UI Editor
<img src="images/OGL_Editor.gif">

Integrates <a href="https://github.com/ocornut/imgui">Dear ImGui</a> for editing the scene without recompiling. 

#### UI Controls
|Input|Action|
|:---|:---|
|`esc`|Quit|
|`space`|Hide UI|
|`tab`|Hide cursor (when UI is hidden)|
|`right arrow`|Change scene|
|`1`|Wireframe mode|
|`2`|Polygon mode|

### FPS Camera
<img src="images/OGL_FPS.gif">

#### Performance
Framerate captured with RenderDoc. The performance stabilizes around 2000 FPS. Typical frame time is less than 1 millisecond.

#### Movement Controls
|Input|Action|
|:---|:---|
|`W`|Forward|
|`S`|Back|
|`A`|Left|
|`D`|Right|
|`Mouse`|Look around|
|`Scroll wheel`|Zoom in/out|

### Rotating Camera
<img src="images/OGL_RotatingCamera.gif">

Camera class implemented. User can customize the position, target, and up-direction. 

### Perspective Correction
<img src="images/OGL_Perspective.gif"> 

Shader now multiplies `projection * view * model` matrices, the view matrix corrects the perspective. 

### 3D Transformations
<img src="images/OGL_3DCrates.gif">

Support for 3D transformations with matrices and vectors.

### Textures Demo - A wild Sprigatito has appeared!~
|100% Empty Box|Mix|100% Sprigatito|
|:-------:|:--------:|:--------:|
|<img src="images/empty.png" style="height: 30%">|<img src="images/half.png" style="height: 30%">|<img src="images/full.png" style="height: 30%">

Support for texture mapping. Press the `up` arrow key to shift the texture towards sprigatito, and `down` to shift towards the crate.

## Creating custom scenes
To create new scenes, add a scene header file in the scenes folder that extends the abstract scene base class. Then create a CPP file for your scene implementing the virtual functions with your custom logic. 

### Creating and using custom shaders
Add custom GLSL shaders to the shader folder. To use them in your scene, load them in your scene file using the shader object. 

### Scene management and scene transitions
Push your new scene file to the scene vector in the scene manager header file. When playing the game, to change scenes, press the `right` arrow key. So far, there are no observable performance drops through RenderDoc when transitioning between scenes.

<!--
### (Shaders) Drawing triangles
|Solid|Solid|Wireframe|
|:---:|:----:|:------:|
|<img src="images/interpolated_color.png" style="height: 30%">|<img src="images/filled.png" style="height: 30%">|<img src="images/wireframe.png" style="height: 30%">|
Support for shaders.
-->

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
<li>
<a href="https://glm.g-truc.net/0.9.8/index.html">GLM</a> for vector and matrix data structures and operations.
</li>
<li>
<a href="https://github.com/ocornut/imgui">Dear ImGui</a> for the user interface.
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
