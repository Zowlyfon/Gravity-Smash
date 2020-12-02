//
// Created by zowlyfon on 01/12/2020.
//

#include "SmallPlanetLevel.h"

SmallPlanetLevel::SmallPlanetLevel(GLFWwindow *window, GUI *gui) : GameLevel(window, gui)
{

}

SmallPlanetLevel::~SmallPlanetLevel()
= default;

void SmallPlanetLevel::init()
{
    shader = new Shader("generic.vert.glsl",
                        "planet.frag.glsl");

    computeShader = new ComputeShader("planetNoise.comp.glsl");


    player = std::make_shared<SmallPlanet>(shader, computeShader, 5);

    player->color = glm::vec3(0.3f, 0.3f, 0.3f);
    player->color += glm::vec3(Utility::randF() / 10.0f,
                               Utility::randF() / 10.0f,
                               Utility::randF() / 10.0f);
    player->mass = 1.0f;
    player->PhysicsObject::scale = Physics::scaleFromMass(50);
    player->PhysicsObject::position = glm::vec3(0.0f, 0.0f, 0.0f);
    player->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    player->init();

    worldObjects.push_back(player);

    initLevel();
}

void SmallPlanetLevel::run()
{
    runLevel();
}

bool SmallPlanetLevel::endCond()
{
    return player->PhysicsObject::scale >= 2000.0f * GameSettings::levelLength;
}

void SmallPlanetLevel::end()
{

}

void SmallPlanetLevel::addNewGameObject()
{
    std::shared_ptr<GameObject> sphere(new SmallPlanet(shader, computeShader));
    sphere->color = glm::vec3(0.3f, 0.3f, 0.3f);
    sphere->color += glm::vec3(Utility::randF() / 10.0f,
                               Utility::randF() / 10.0f,
                               Utility::randF() / 10.0f);

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
