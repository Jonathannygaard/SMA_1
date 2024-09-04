#include "Application.h"
#include "Shader.h"
#include "ShaderFileLoader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Color.h"
#include "Input.h"
#include "glm/mat4x3.hpp"

Camera Application::mCamera;
float Application::DeltaTime = 0.0f;

std::string vfs = ShaderLoader::LoadShaderFromFile("Triangle.vs");
std::string fs = ShaderLoader::LoadShaderFromFile("Triangle.fs");

void Application::init()
{
    mWindow = Window::init();
    mCamera.init();
    
    run();
}

void Application::create() {

    // Player
    Wall_1.CreateCube(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.75f, 1.3f, 5.f), Color::Blue);
    Wall_1.AddCollider(glm::vec3(0.75f, 1.3f, 0.75f), ECollisionType::Wall);

    
    Wall_2.CreateCube(glm::vec3(0.f, 0.f, 5.f), glm::vec3(3.f, 1.3f, 0.75f), Color::Blue);
    Wall_2.AddCollider(glm::vec3(0.75f, 1.3f, 0.75f), ECollisionType::Wall);
    
    
    Wall_3.CreateCube(glm::vec3(3.f, 0.f, 0.f), glm::vec3(0.75f, 1.3f, 5.f), Color::Blue);
    Wall_3.AddCollider(glm::vec3(0.75f, 1.3f, 0.75f), ECollisionType::Wall);

    
    Wall_4.CreateCube(glm::vec3(0.f, 0.f, 0.f), glm::vec3(3.f, 1.3f, 0.75f), Color::Blue);
    Wall_4.AddCollider(glm::vec3(0.75f, 1.3f, 0.75f), ECollisionType::Wall);

    
    Floor.CreateCube(glm::vec3(0.f, -0.75f, 0.f), glm::vec3(3.f, 0.75f, 5.f), Color::Blue);
    Floor.AddCollider(glm::vec3(0.75f, 1.3f, 0.75f), ECollisionType::Wall);
}

void Application::update() {

   
}

void Application::run()
{
    create();
    float FirstFrame = 0.0f;
    glm::vec3 color(Color::Teal);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(mWindow))
    {
        const auto CurrentFrame = static_cast<float>(glfwGetTime());
        DeltaTime = CurrentFrame - FirstFrame;
        FirstFrame = CurrentFrame;

        // render
        // ------
        glClearColor(color.x,color.y,color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(Shader::Program);

        update();

        glUniformMatrix4fv(mCamera.projectionLoc, 1, GL_FALSE, glm::value_ptr(mCamera.getProjection(Window::Width, Window::Height)));
        glUniformMatrix4fv(mCamera.viewLoc, 1, GL_FALSE, glm::value_ptr(mCamera.getView()));


        // Render the objects
        // -----
        Skybox.Draw();
        Wall_1.Draw();
        Wall_2.Draw();
        Wall_3.Draw();
        Wall_4.Draw();
        Floor.Draw();
        
        // input
        // -----
        //KeyBoardInput::processInput(mWindow, &Player);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}