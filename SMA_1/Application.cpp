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
    Player.CreateCube(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.75f, 1.3f, 0.75f), Color::Blue);
    Player.AddCollider(glm::vec3(0.75f, 1.3f, 0.75f), ECollisionType::Player);
    Player.bIsPlayer = true;

    Terrain.CreateTerrain(-5,0,5,5, 1.f);
    Terrain.isTarrain = true;

    Curve.CreateCurve(Terrain);
    Curve.isLine = true;

    NPC.CreateCube(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f), Color::Green);

    NPC2.CreateCube(glm::vec3(10.f,0.f,10.f), glm::vec3(1.f), Color::Red);
    NPC2.AddCollider(glm::vec3(1.f), ECollisionType::NPC);

    Pickup.CreateCube(glm::vec3(0.5f, Terrain.FindTerrainHeight(Pickup.GetPosition()), 5.5f), glm::vec3(1.f), Color::Gold);
    Pickup.bIsPickup = true;
    Pickup.AddCollider(glm::vec3(1.f), ECollisionType::Pickup);

    Pickup2.CreateCube(glm::vec3(5.f, Terrain.FindTerrainHeight(Pickup.GetPosition()), 5.5f), glm::vec3(1.f), Color::Gold);
    Pickup2.bIsPickup = true;
    Pickup2.AddCollider(glm::vec3(1.f), ECollisionType::Pickup);
}

void Application::update() {
    Terrain.FindTerrainHeight(Player.GetPosition());

    if (NPC.GetPosition().z < -20)
    {
        NPC.NPCDirection = 1*DeltaTime;
    }
    if(NPC.GetPosition().z > 20)
    {
        NPC.NPCDirection = -1*DeltaTime;
    }
    NPC.GetPosition().x += NPC.NPCDirection;
    NPC.GetPosition().z = Mesh::f(NPC.GetPosition().x);

    NPC2.ChasePlayer(Player);

    Terrain.FindTerrainHeight(NPC.GetPosition());
    Terrain.FindTerrainHeight(NPC2.GetPosition());

    mCamera.OrbitCamera();

    Collision::CheckPickupCollisions();
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
        Player.Draw();
        Terrain.Draw();
        Curve.Draw();
        NPC.Draw();
        NPC2.Draw();
        Pickup.Draw();
        Pickup2.Draw();
        
        // input
        // -----
        KeyBoardInput::processInput(mWindow, &Player);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}