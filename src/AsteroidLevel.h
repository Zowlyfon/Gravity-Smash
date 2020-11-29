//
// Created by zowlyfon on 29/11/2020.
//

#ifndef GAMEENGINE_ASTEROIDLEVEL_H
#define GAMEENGINE_ASTEROIDLEVEL_H

#include "GameLevel.h"
#include "GameObject.h"

class AsteroidLevel : public GameLevel {
public:
    AsteroidLevel(std::shared_ptr<GameObject> player,
                  std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> worldObjects);
    ~AsteroidLevel();

    void init() override;
    void endCond() override;
    void end() override;

    void addNewGameObject() override;

    std::shared_ptr<GameObject> player;
    std::shared_ptr<std::vector<std::shared_ptr<GameObject>>> worldObjects;

};


#endif //GAMEENGINE_ASTEROIDLEVEL_H
