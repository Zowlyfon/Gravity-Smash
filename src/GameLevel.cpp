//
// Created by zowlyfon on 28/11/2020.
//

#include "GameLevel.h"

GameLevel::GameLevel(GLFWwindow *window, GUI *gui) : window(window), gui(gui), prevScaleDivisor(0.0f)
{
}

GameLevel::~GameLevel()
{
    worldObjects.clear();
    worldEffects.clear();
    delete shader;
    delete computeShader;
    delete backgroundShader;
    delete background;
    delete effectShader;
    delete effectComputeShader;
}

void GameLevel::initLevel()
{
    effectShader = new Shader("generic.vert.glsl",
                        "rockEffect.frag.glsl");

    effectComputeShader = new ComputeShader("rockEffect.comp.glsl");

    for(int i = 0; i < GameSettings::maxObjects; i++) {
        addNewGameObject();
    }

    backgroundShader = new Shader("background.vert.glsl",
                                  "background.frag.glsl");

    background = new Background(backgroundShader);
    background->init();

    offset = glm::vec3(Utility::randF(), Utility::randF(), Utility::randF());
}

void GameLevel::runLevel()
{
    time = glfwGetTime();
    processInput(window);
    GLfloat random = Utility::randF2();

    if (random > 0.95 && worldObjects.size() < GameSettings::maxObjects) {
        addNewGameObject();
        if (worldObjects.size() < GameSettings::maxObjects / 2) {
            addNewGameObject();
        }
    }

    physics();
    draw();
    prevTime = time;
}

void GameLevel::init()
{

}

bool GameLevel::endCond()
{
    return false;
}

void GameLevel::run()
{
}

void GameLevel::physics()
{
    Physics::calculateGravity(worldObjects, player, prevTime, time);

    Physics::calculateCollisions(worldObjects, player);

    for (const auto &object : worldObjects) {
        object->physics();
    }

    for(const auto &effect : worldEffects) {
        effect->physics();
        if (effect->startTime + effect->lifespan < time) {
            effect->dead = true;
        }
    }

    Physics::calculateOutOfRange(worldObjects, player);

    /* Delete destroyed objects */
    worldObjects.erase(
      std::remove_if(
        worldObjects.begin(),
        worldObjects.end(),
        [&](auto &&object) {
            if (object->dead || (object->PhysicsObject::scale < player->PhysicsObject::scale / 32.0f)) {
                for (int i = 0; i < 10; i++) {
                    auto effect = std::make_shared<GameEffect>(effectShader, effectComputeShader, 3);
                    effect->velocity = glm::vec3(Utility::randF() * object->PhysicsObject::scale * 25.0f,
                                                 Utility::randF() * object->PhysicsObject::scale * 25.0f,
                                                 Utility::randF() * object->PhysicsObject::scale * 25.0f);
                    effect->PhysicsObject::position = object->PhysicsObject::position;
                    effect->color = object->color;
                    effect->PhysicsObject::scale = object->PhysicsObject::scale / 8.0f;
                    effect->startTime = time;
                    effect->lifespan = 2.0f;
                    effect->init();
                    worldEffects.push_back(effect);
                }
                return true;
            }
            return false;
        }),
      worldObjects.end()
    );

    worldEffects.erase(
      std::remove_if(
        worldEffects.begin(),
        worldEffects.end(),
        [&](auto &&object) {
            return object->dead;
        }),
      worldEffects.end()
    );


    for (const auto &object : worldObjects) {
        object->PhysicsObject::scale = Physics::scaleFromMass(object->mass);
    }
}

void GameLevel::draw()
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

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

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

    glm::vec3 lightPos = glm::vec3(player->RenderObject::position.x / scaleFactor, player->RenderObject::position.y / scaleFactor, 5.0f);

    glUseProgram(shader->getShaderProgram());

    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "viewPos"), 1, glm::value_ptr(cameraPos));

    shader->setMat4("projection", &projection);
    shader->setMat4("view", &view);


    glUniform3fv(glGetUniformLocation(shader->getShaderProgram(), "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform1f(glGetUniformLocation(shader->getShaderProgram(), "playerScale"), player->RenderObject::scale);

    for (const auto &object : worldObjects) {
        object->draw(scaleFactor);
    }

    glUseProgram(effectShader->getShaderProgram());
    effectShader->setMat4("projection", &projection);
    effectShader->setMat4("view", &view);
    effectShader->setVec3("lightPos", &lightPos);
    effectShader->setFloat("playerScale", player->RenderObject::scale);

    for (const auto &effect : worldEffects) {
        effect->draw(scaleFactor);
    }

    gui->draw(player);
}

void GameLevel::end()
{

}

void GameLevel::processInput(GLFWwindow *_window)
{
    GLdouble deltaT = time - prevTime;
    GLfloat step = player->PhysicsObject::scale * 10.0f * deltaT;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        player->velocity.y += step;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        player->velocity.x -= step;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        player->velocity.y -= step;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        player->velocity.x += step;
    }
}

void GameLevel::addNewGameObject()
{

}