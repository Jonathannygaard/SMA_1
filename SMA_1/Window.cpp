#include <iostream>
#include "Window.h"
#include "Input.h"
#include "Shader.h"

float Window::Width = 1920.0f;
float Window::Height = 1080.0f;

GLFWwindow* Window::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window;
    //window = glfwCreateWindow((int)Width,(int)Height,"Compulsory 2",glfwGetPrimaryMonitor(),NULL); // Fullscreen
    window = glfwCreateWindow((int)Width,(int)Height,"Compulsory 2",NULL,NULL); // Windowed
    if(window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    glViewport(0,0,Width,Height);
    glEnable(GL_DEPTH_TEST);
    Shader::CreateProgram();
    glfwSetFramebufferSizeCallback(window,Input::framebuffer_size_callback);
    glfwSetCursorPosCallback(window, MouseInput::mouse_callback);
    return window;
}
