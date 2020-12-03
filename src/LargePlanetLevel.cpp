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

    oceanShader = new Shader("ocean.vert.glsl",
                             "ocean.frag.glsl");

    player = std::make_shared<LargePlanet>(shader, computeShader, oceanShader, 5);

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

void LargePlanetLevel::draw()
{
    float scaleFactor;

    if (prevScaleDivisor < player->baseSize &&
        prevScaleDivisor + player->baseSize / 100.0f <= player->baseSize) {
        scaleFactor = prevScaleDivisor + player->baseSize / 100.0f;
    } else if (prevScaleDivisor > player->baseSize &&
               prevScaleDivisor - player->baseSize / 100.0f >= player->baseSize) {
        scaleFactor = prevScaleDivisor - player->baseSize / 100.0f;
    } else {
        scaleFactor = player->baseSize;
    }

    prevScaleDivisor = scaleFactor;

    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    projection = glm::perspective(
      glm::radians(45.0f),
      (float)GameSettings::screenWidth / (float)GameSettings::screenHeight,
      0.1f,
      100.0f);

    glm::vec3 cameraPos = glm::vec3(player->RenderObject::position.x / scaleFactor, player->RenderObject::position.y / scaleFactor, 25.0f);

    view = glm::lookAt(cameraPos,
                       player->RenderObject::position / scaleFactor,
                       glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 offset2 = offset + (float)glfwGetTime() / 10.0f;

    glUseProgram(backgroundShader->getShaderProgram());

    glUniformMatrix4fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(glGetUniformLocation(backgroundShader->getShaderProgram(), "offset"), 1, glm::value_ptr(offset2));

    glDisable(GL_CULL_FACE);

    background->playerPos = player->RenderObject::position;
    background->draw(scaleFactor);

    glEnable(GL_CULL_FACE);

    lightPos = glm::vec3(player->RenderObject::position.x / scaleFactor, player->RenderObject::position.y / scaleFactor, 5.0f);

    glUseProgram(shader->getShaderProgram());

    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "viewPos"), 1, glm::value_ptr(cameraPos));

    shader->setMat4("projection", &projection);
    shader->setMat4("view", &view);


    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform1f(glGetUniformLocation(shader->getShaderProgram(), "playerScale"), player->RenderObject::scale);

    for (const auto &object : worldObjects) {
        object->draw(scaleFactor);
    }

    glUseProgram(oceanShader->getShaderProgram());
    oceanShader->setMat4("projection", &projection);
    oceanShader->setMat4("view", &view);
    oceanShader->setVec3("lightPos", &lightPos);
    oceanShader->setFloat("playerScale", player->RenderObject::scale);

    glUseProgram(effectShader->getShaderProgram());
    effectShader->setMat4("projection", &projection);
    effectShader->setMat4("view", &view);
    effectShader->setVec3("lightPos", &lightPos);
    effectShader->setFloat("playerScale", player->RenderObject::scale);

    for (const auto &effect : worldEffects) {
        effect->draw(scaleFactor);
    }

    gui->drawStats(player);
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
    std::shared_ptr<LargePlanet> sphere(new LargePlanet(shader, computeShader, oceanShader));
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