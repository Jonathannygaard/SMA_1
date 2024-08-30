#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    static float Width;
    static float Height;

    static GLFWwindow* init();
    
};
