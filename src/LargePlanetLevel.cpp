//
// Created by zowlyfon on 02/12/2020.
//

#include "LargePlanetLevel.h"

LargePlanetLevel::LargePlanetLevel(GLFWwindow *window, GUI *gui) : GameLevel(window, gui)
{

}

LargePlanetLevel::~LargePlanetLevel()
= default;

void LargePlanetLevel::init()
{
    shader = new Shader("generic.vert.glsl",
                        "largePlanet.frag.glsl");

    computeShader = new ComputeShader("largePlanetNoise.comp.glsl");

    player = std::make_shared<LargePlanet>(shader, computeShader, 5);

    player->color = glm::vec3(0.4f, 0.4f, 0.4f);
    player->color += glm::vec3(Utility::randF() / 5.0f,
                               Utility::randF() / 5.0f,
                               Utility::randF() / 5.0f);
    player->mass = 1.0f;
    player->PhysicsObject::scale = Physics::scaleFromMass(50);
    player->PhysicsObject::position = glm::vec3(0.0f, 0.0f, 0.0f);
    player->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    player->init();

    worldObjects.push_back(player);

    initLevel();
}

void LargePlanetLevel::run()
{
    runLevel();
}

bool LargePlanetLevel::endCond()
{
    return player->PhysicsObject::scale >= 4000.0f * GameSettings::levelLength;
}

void LargePlanetLevel::end()
{

}

void LargePlanetLevel::addNewGameObject()
{
    std::shared_ptr<LargePlanet> sphere(new LargePlanet(shader, computeShader));
    sphere->color = glm::vec3(0.4f, 0.4f, 0.4f);
    sphere->color += glm::vec3(Utility::randF() / 5.0f,
                               Utility::randF() / 5.0f,
                               Utility::randF() / 5.0f);

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

    worldObjects.push_back(std::move(sphere));
}