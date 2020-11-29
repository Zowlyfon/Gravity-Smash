//
// Created by zowlyfon on 27/11/2020.
//

#ifndef GAMEENGINE_ASTEROID_H
#define GAMEENGINE_ASTEROID_H

#include "GameObject.h"
#include "Atmosphere.h"

class Asteroid : public GameObject {
public:
    Asteroid(unsigned int subs=4);
    ~Asteroid();
};


#endif //GAMEENGINE_ASTEROID_H
