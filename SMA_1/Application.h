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
    Cube Wall_1;
    Cube Wall_2;
    Cube Wall_3;
    Cube Wall_4;
    Cube Floor;
    
    void init();
    void create();
    void update();
    void run();   
};
