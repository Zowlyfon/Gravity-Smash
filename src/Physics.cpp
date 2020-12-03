//
// Created by zowlyfon on 23/11/2020.
//

#include "Physics.h"

void Physics::calculateGravity(std::vector<std::shared_ptr<GameObject>> &worldObjects,
                               std::shared_ptr<GameObject> player,
                               GLdouble prevTime,
                               GLdouble time)
{
    auto deltaT = time - prevTime;
    std::for_each(std::execution::par_unseq, worldObjects.begin(), worldObjects.end(), [&](auto&& object1) {
        glm::vec2 force(0.0f);
        GLfloat G = GameSettings::gravityConstant;

        for (const auto &object2 : worldObjects) {
            if (object1 != object2) {
                glm::vec2 r1 = glm::vec2(object1->PhysicsObject::position.x, object1->PhysicsObject::position.y);
                glm::vec2 r2 = glm::vec2(object2->PhysicsObject::position.x, object2->PhysicsObject::position.y);

                GLfloat distance = glm::length(object1->PhysicsObject::position - object2->PhysicsObject::position);

                glm::vec2 unitVec = glm::normalize(r1 - r2);

                force += -G * (((object1->mass * object2->mass) /
                                (distance * distance)) * unitVec);
            }
        }

        object1->velocity += (glm::vec3(force, 0.0f) / object1->mass) * (GLfloat)deltaT;
    });
}

void Physics::calculateCollisions(std::vector<std::shared_ptr<GameObject>> &worldObjects,
                                  std::shared_ptr<GameObject> player)
{
    for (const auto &object : worldObjects) {
        if (object != player && !object->dead) {
            GLfloat length = glm::length(object->PhysicsObject::position - player->PhysicsObject::position);
            if (length < (object->PhysicsObject::scale + player->PhysicsObject::scale)) {
                if (object->mass > player->mass) {
                    player->mass = (GLfloat)fmax(player->mass / 2, player->baseMass);
                    player->PhysicsObject::position = glm::vec3(
                      Utility::randF() * 5000.0f * player->PhysicsObject::scale,
                      Utility::randF() * 5000.0f * player->PhysicsObject::scale,
                      0.0f);
                    player->velocity = glm::vec3(0.0f);
                } else {
                    player->velocity = player->velocity * player->mass + object->velocity * object->mass;
                    player->mass += object->mass * GameSettings::massGain;
                    player->velocity = player->velocity / player->mass;
                    object->dead = true;
                }
                player->updateMass();
            }
        }

        for (const auto &object2 : worldObjects) {
            if (!object2->dead && !object->dead && object2 != player && object != player && object != object2) {
                GLfloat length = glm::length(object->PhysicsObject::position - object2->PhysicsObject::position);

                if (length < (object->PhysicsObject::scale + object2->PhysicsObject::scale)) {
                    if (object->mass > object2->mass) {
                        object->velocity = object->velocity * object->mass + object2->velocity * object2->mass;
                        object->mass += object2->mass / 4;
                        object->velocity = object->velocity / object->mass;
                        object2->dead = true;
                    } else {
                        object2->velocity = object2->velocity * object2->mass + object->velocity * object->mass;
                        object2->mass += object->mass / 4;
                        object2->velocity = object2->velocity / object2->mass;
                        object->dead = true;
                    }
                }
            }
        }
    }
}

void Physics::calculateOutOfRange(std::vector<std::shared_ptr<GameObject>> &worldObjects,
                                  std::shared_ptr<GameObject> player)
{
    for (const auto &object : worldObjects) {
        if (object->dead && object != player) {
            GLfloat length = glm::length(object->PhysicsObject::position - player->PhysicsObject::position);
            if (length > player->PhysicsObject::scale * 1000.0f) {
                object->dead = true;
            }
        }
    }
}

GLfloat Physics::scaleFromMass(GLfloat mass)
{
    return pow(mass, 1.0f / 3.0f) / glm::pi<float>();
}