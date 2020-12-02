//
// Created by zowlyfon on 01/12/2020.
//

#include "GasGiantLevel.h"

GasGiantLevel::GasGiantLevel(GLFWwindow *window, GUI *gui) : GameLevel(window, gui)
{

}

GasGiantLevel::~GasGiantLevel()
= default;

void GasGiantLevel::init()
{
    shader = new Shader("generic.vert.glsl",
                        "gasGiant.frag.glsl");

    player = std::make_shared<GasGiant>(shader, 4);

    player->color = glm::vec3(0.8f, 0.1f, 0.1f);
    player->mass = 1.0f;
    player->PhysicsObject::scale = Physics::scaleFromMass(50);
    player->PhysicsObject::position = glm::vec3(0.0f, 0.0f, 0.0f);
    player->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    player->init();

    worldObjects.push_back(player);

    initLevel();
}

void GasGiantLevel::run()
{
    runLevel();
}

bool GasGiantLevel::endCond()
{
    return player->PhysicsObject::scale > 8000.0f * GameSettings::levelLength;
}

void GasGiantLevel::end()
{

}

void GasGiantLevel::addNewGameObject()
{
    std::shared_ptr<GameObject> sphere(new GasGiant(shader));
    sphere->color = glm::vec3(0.5f, 0.5f, 0.5f);
    sphere->color += glm::vec3(Utility::randF() / 2.5f,
                               Utility::randF() / 2.5f,
                               Utility::randF() / 2.5f);

    sphere->mass = (Utility::bias(Utility::randF2(), 0.9f + GameSettings::difficulty)) * player->mass * 200.0f + player->mass / 16;
    sphere->PhysicsObject::scale = Physics::scaleFromMass(sphere->mass);
    sphere->PhysicsObject::position = glm::vec3(
      Utility::randF() * sphere->PhysicsObject::scale * 100.0f + player->PhysicsObject::position.x,
      Utility::randF() * sphere->PhysicsObject::scale * 100.0f + player->PhysicsObject::position.y,
      Utility::randF() * 100.0f);

    sphere->velocity = glm::vec3(Utility::randF() / (sphere->PhysicsObject::scale * 4),
                                 Utility::randF() / (sphere->PhysicsObject::scale * 4),
                                 0.0f);

    sphere->init();

    worldObjects.push_back(sphere);
}
