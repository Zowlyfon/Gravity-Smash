//
// Created by zowlyfon on 29/11/2020.
//

#include "AsteroidLevel.h"

AsteroidLevel::AsteroidLevel(GLFWwindow *window) : GameLevel(window)
{

}

AsteroidLevel::~AsteroidLevel()
= default;

void AsteroidLevel::init()
{

    shader = new Shader("asteroid.vert.glsl",
                        "asteroid.frag.glsl");

    computeShader = new ComputeShader("asteroidNoise.comp.glsl");

    backgroundShader = new Shader("background.vert.glsl",
                                  "background.frag.glsl");

    player = std::make_shared<Asteroid>(shader, computeShader, 6);

    player->color = glm::vec3(0.15f, 0.14f, 0.14f);
    player->mass = 1.0f;
    player->PhysicsObject::scale = Physics::scaleFromMass(50);
    player->PhysicsObject::position = glm::vec3(0.0f, 0.0f, 0.0f);

    player->init();

    worldObjects.push_back(player);

    for(int i = 0; i < GameSettings::maxObjects; i++) {
        addNewGameObject();
    }

    background = new Background(backgroundShader);
    background->init();

    gui = new GUI();
    gui->init(window);

    offset = glm::vec3(Utility::randF(), Utility::randF(), Utility::randF());
}

void AsteroidLevel::run()
{
    GLfloat random = Utility::randF2();

    if (random > 0.95 && worldObjects.size() < GameSettings::maxObjects) {
        addNewGameObject();
        if (worldObjects.size() < GameSettings::maxObjects / 2) {
            addNewGameObject();
        }
    }

    time = glfwGetTime();
    physics();
    draw();
    prevTime = time;
}

bool AsteroidLevel::endCond()
{
    return player->PhysicsObject::scale >= 1000.0f;
}

void AsteroidLevel::end()
{
}

void AsteroidLevel::addNewGameObject()
{
    std::shared_ptr<GameObject> sphere(new Asteroid(shader, computeShader));
    sphere->color = glm::vec3(0.15f, 0.14f, 0.14f);
    sphere->color += glm::vec3(Utility::randF() / 20.0f,
                               Utility::randF() / 100.0f,
                               Utility::randF() / 100.0f);

    sphere->mass = (Utility::bias(Utility::randF2(), 0.9f)) * player->mass * 200.0f + player->mass / 16;
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