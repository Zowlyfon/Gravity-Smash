//
// Created by zowlyfon on 02/12/2020.
//

#ifndef GAMEENGINE_LARGEPLANET_H
#define GAMEENGINE_LARGEPLANET_H

#include "GameObject.h"
#include "Ocean.h"

class LargePlanet : public GameObject {
public:
    LargePlanet(Shader *shader,
                ComputeShader *computeShader,
                unsigned int subs=4);
    ~LargePlanet();
};


#endif //GAMEENGINE_LARGEPLANET_H
