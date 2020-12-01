//
// Created by zowlyfon on 01/12/2020.
//

#ifndef GAMEENGINE_SMALLPLANET_H
#define GAMEENGINE_SMALLPLANET_H

#include "GameObject.h"

class SmallPlanet : public GameObject {
public:
    SmallPlanet(Shader *shader, ComputeShader *computeShader, unsigned int subs=4);
    ~SmallPlanet();
};


#endif //GAMEENGINE_SMALLPLANET_H
