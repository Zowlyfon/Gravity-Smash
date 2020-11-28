//
// Created by zowlyfon on 27/11/2020.
//

#ifndef GAMEENGINE_ATMOSPHERE_H
#define GAMEENGINE_ATMOSPHERE_H

#include "IcoSphere.h"

class Atmosphere : public IcoSphere {
public:
    Atmosphere(std::shared_ptr<Shader> newShader);
    ~Atmosphere();
    void draw(float playerSize) override;
    void init() override;
};


#endif //GAMEENGINE_ATMOSPHERE_H
