﻿#pragma once
#include <memory>
#include <string>

#include "Collision.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Pickup;

struct Vertex
{
    glm::vec3 Pos;
    glm::vec3 Color;
    glm::vec3 Normal = glm::vec3(0.f);
    Vertex(glm::vec3 Pos, glm::vec3 rgb) : Pos(Pos), Color(rgb)
    {
    }
};

struct Triangles
{
    unsigned int a, b, c;
    Triangles(unsigned int a, unsigned int b, unsigned int c) : a(a), b(b), c(c)
    {
    }
};

class Cube;

class Mesh
{
    int count = 0;

public:
    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndices;
    std::vector<Triangles> tIndices;
    std::vector<std::shared_ptr<Cube>> Package;

	bool isTarrain = false;
    bool isLine = false;

     float xy(float t, float u);
	void CreateTerrain(float xStart, float yStart, float xEnd, float yEnd, float Step);

    void Draw();

    float calculate_Normal(const glm::vec3&& AB, const glm::vec3&& AC);

    bool FindTerrainHeight(glm::vec3& Player);

    void BindBuffers();

    static float f(float x);
    void CreateCurve(Mesh ThePlane);

    unsigned int VAO;
private:

    unsigned int VBO;
    unsigned int EBO;
};


class Cube{
    int index = 0;
    glm::vec3 Position;
    glm::vec3 Scale;
    glm::vec3 Rotation;

public:
    Cube()
    {
    }
    bool bShouldRender = true;
    bool bIsPlayer = false;
    bool bCanInteract = false;
    bool bIsPickup = false;
    bool bIsDoor = false;
    bool bDoorInteracted = false;

    float NPCDirection = 1;
    float NPCSpeed = 0.1f;
    

    Cube* OverlappedCube = nullptr;

    void CreateCube(glm::vec3 position, glm::vec3 scale, glm::vec3 color, bool isPickup = false, bool isPlayer = false, glm::vec3 rotation = glm::vec3(0.f), bool isDoor = false);
    void CreateInvertedCube(glm::vec3 position, glm::vec3 scale, glm::vec3 color, glm::vec3 rotation = glm::vec3(0.f));
    void Draw();

    std::shared_ptr<Collision> Collider;
    glm::vec3& GetPosition() { return Position; }
    glm::vec3& GetScale() { return Scale; }
    glm::vec3& GetRotation() { return Rotation; }
    int& GetIndex() { return index; }
    void AddCollider(glm::vec3 scale,ECollisionType collisionType, glm::vec3 offset = glm::vec3(0.f));
    void MoveNPC(Cube& NPC, glm::vec3 pos);
    void ChasePlayer(Cube& Player);
    virtual ~Cube();

    void BindBuffers();

	unsigned int VAO;
private:
    
    unsigned int VBO;
    unsigned int EBO;

    std::vector<Vertex> cVertices;
    std::vector<Triangles> cIndices;
};

