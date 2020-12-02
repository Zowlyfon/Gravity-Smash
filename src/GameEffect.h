//
// Created by zowlyfon on 01/12/2020.
//

#ifndef GAMEENGINE_GAMEEFFECT_H
#define GAMEENGINE_GAMEEFFECT_H

#include "GameObject.h"

class GameEffect : public GameObject {
public:
    GameEffect(Shader *shader, ComputeShader *computeShader, unsigned int subs=3);
    ~GameEffect();

    GLdouble startTime;
    GLdouble lifespan;
};


#endif //GAMEENGINE_GAMEEFFECT_H
