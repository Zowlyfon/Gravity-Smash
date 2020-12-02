//
// Created by zowlyfon on 01/12/2020.
//

#ifndef GAMEENGINE_GASGIANT_H
#define GAMEENGINE_GASGIANT_H

#include "GameObject.h"

class GasGiant : public GameObject {
public:
    explicit GasGiant(Shader *shader, unsigned int subs=4);
    ~GasGiant();

    void draw(float scaleFactor) override;
};


#endif //GAMEENGINE_GASGIANT_H
