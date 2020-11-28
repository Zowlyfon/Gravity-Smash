//
// Created by zowlyfon on 27/11/2020.
//

#ifndef GAMEENGINE_ASTEROID_H
#define GAMEENGINE_ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject {
public:
    Asteroid(unsigned int subs=4);
    ~Asteroid();
    void init() override;
    void physics() override;
    void draw(float playerSize) override;
    void updateMass() override;

private:
    void addNoise();

    glm::vec3 offset;
    glm::vec3 rotAxis;
    GLfloat rotStep;
};


#endif //GAMEENGINE_ASTEROID_H
