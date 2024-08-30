#pragma once
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

class Application
{
public:

    GLFWwindow* mWindow;
    static Camera mCamera;
    static float DeltaTime;

    Cube Skybox;
    Cube Player;
    Mesh Terrain;
    Mesh Curve;
    Cube NPC;
    Cube NPC2;
    Cube Pickup;
    Cube Pickup2;
    
    void init();
    void create();
    void update();
    void run();   
};
