//
// Created by zowlyfon on 28/11/2020.
//

#ifndef GAMEENGINE_GAMEOBJECT_H
#define GAMEENGINE_GAMEOBJECT_H

#include "IcoSphere.h"
#include "PhysicsObject.h"

class GameObject : public IcoSphere, public PhysicsObject{
public:
    GameObject();
    ~GameObject();

    void init() override;
    void physics() override;
    void draw(float scaleFactor) override;
    void updateMass() override;
    glm::vec3 offset;

protected:
    void runComputeShader() override;

    glm::vec3 rotAxis;
    GLfloat rotStep;
};


#endif //GAMEENGINE_GAMEOBJECT_H
