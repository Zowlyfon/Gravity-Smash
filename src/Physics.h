//
// Created by zowlyfon on 23/11/2020.
//

#ifndef GAMEENGINE_PHYSICS_H
#define GAMEENGINE_PHYSICS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <algorithm>
#include <execution>

#include "Utility.h"
#include "PhysicsObject.h"

class Physics {
public:
    static void calculateGravity(std::vector<std::shared_ptr<PhysicsObject>> *worldObjects,
                                 std::shared_ptr<PhysicsObject> player,
                                 GLdouble prevTime,
                                 GLdouble time);

    static void calculateCollisions(std::vector<std::shared_ptr<PhysicsObject>> *worldObjects,
                                    std::shared_ptr<PhysicsObject> player);

    static void calculateOutOfRange(std::vector<std::shared_ptr<PhysicsObject>> *worldObjects,
                                    std::shared_ptr<PhysicsObject> player);

    static GLfloat scaleFromMass(GLfloat mass);
};


#endif //GAMEENGINE_PHYSICS_H
