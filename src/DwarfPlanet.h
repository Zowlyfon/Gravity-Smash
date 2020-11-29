//
// Created by zowlyfon on 28/11/2020.
//

#ifndef GAMEENGINE_DWARFPLANET_H
#define GAMEENGINE_DWARFPLANET_H

#include "GameObject.h"

class DwarfPlanet : public GameObject {
public:
    DwarfPlanet(unsigned int subs=4);
    ~DwarfPlanet();
    void init() override;
    void physics() override;
    void draw(float scaleFactor) override;
    void updateMass() override;
private:
    void addNoise();

    glm::vec3 offset;
    glm::vec3 rotAxis;
    GLfloat rotStep;
};


#endif //GAMEENGINE_DWARFPLANET_H
