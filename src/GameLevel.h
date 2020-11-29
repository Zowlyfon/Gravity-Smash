//
// Created by zowlyfon on 28/11/2020.
//

#ifndef GAMEENGINE_GAMELEVEL_H
#define GAMEENGINE_GAMELEVEL_H


class GameLevel {
public:
    virtual void init()=0;
    virtual void endCond()=0;
    virtual void end()=0;

    virtual void addNewGameObject()=0;
};


#endif //GAMEENGINE_GAMELEVEL_H
