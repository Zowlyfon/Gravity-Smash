//
// Created by zowlyfon on 02/12/2020.
//

#include "LargePlanet.h"

LargePlanet::LargePlanet(Shader *shader,
                         ComputeShader *computeShader,
                         Shader *oceanShader,
                         unsigned int subs)
{
    IcoSphere::subs = subs;
    RenderObject::shader = shader;
    RenderObject::computeShader = computeShader;
    ocean = new Ocean(oceanShader);
    ocean->oceanPos = &(RenderObject::position);
    ocean->oceanScale = &(RenderObject::scale);
    ocean->init();
}

LargePlanet::~LargePlanet()
{
    delete ocean;
}

void LargePlanet::physics()
{
    GameObject::physics();
    //ocean->position = PhysicsObject::position;
    //ocean->scale = PhysicsObject::scale;
    ocean->offset = offset + (float)glfwGetTime() / 25.0f;
}

void LargePlanet::draw(float scaleFactor)
{
    GameObject::draw(scaleFactor);
    ocean->draw(scaleFactor);
}