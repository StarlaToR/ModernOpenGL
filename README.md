# ModernOpenGL

This project have the goal to create a 3D models centered engine.

# Camera controls
- W,A,S,D : move the camera toward its direction
- Right-Click and mouse Move : move the camera direction

# Usefull information

- The models, textures, mesh, lights are charged in the main.cpp between the lignes 76 and 106.
- The .obj parser is in the loadResource function in Model.cpp. 

# ResourceManager and IResources
The ResourceManager is a map that give a resource a name. 

## Model
    - have a .obj parsed to an index array and vertex array

## Texture
    - have a .png parsed by OpenGL functions,
    - You can't apply many textures to a mesh.

# Mesh
A mesh is a object from the world. It's composed of a 3D model, a texture and the informations needed to create the model matrix (position, rotation, scale).

# Camera
The camera has the view matrix and the projection matrix.

# Light 
The 3 lights works but due to a technical problem, I had to remove the menu to add and change the directionnal lights. You can still add them in the main.cpp where i add all the first lights.
The lights are limited to 8 in the world, you can remove this limit by removing the ligne 98 in App.cpp.

## PointLight
    - has a position, 
    - lights around it,
    - get less bright with the distance

## SpotLight
    - has a direction and a position,
    - lights in a cone,
    - get less bright with the distance

## DirectionalLight
    - has a direction
    - lights every object with the same angle,

# Shader

The Shaders are functions written in GLSL that calculates the light effect and the object position in the world.

## Vertex Shader

    - first one,
    - Multiply the differents matrixes and apply it on every point to get it real position,
    - Calculates the normals and textures coordinates,

## FragmentShader
    - Second one, it get the information given by the vertex shader,
    - calculates this light intensity on every point,
    - Apply the textures,
