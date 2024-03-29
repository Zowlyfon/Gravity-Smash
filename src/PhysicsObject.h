//
// Created by zowlyfon on 21/11/2020.
//

#ifndef GAMEENGINE_PHYSICSOBJECT_H
#define GAMEENGINE_PHYSICSOBJECT_H

#include "RenderObject.h"
class PhysicsObject {
public:
    PhysicsObject();
    ~PhysicsObject();
    virtual void physics();
    virtual void updateMass();

    glm::vec3 position;
    glm::vec3 velocity;
    GLfloat scale;
    GLfloat mass;
    bool dead;

    float baseSize;
    float baseMass;

    GLdouble prevTime;
};


#endif //GAMEENGINE_PHYSICSOBJECT_H
