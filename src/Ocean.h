//
// Created by zowlyfon on 02/12/2020.
//

#ifndef GAMEENGINE_OCEAN_H
#define GAMEENGINE_OCEAN_H

#include "IcoSphere.h"

class Ocean : public IcoSphere {
public:
    Ocean(Shader *shader);
    ~Ocean();

    void init() override;
    void draw(float scaleFactor) override;

    glm::vec3 offset;

    glm::vec3 *oceanPos;
    GLfloat *oceanScale;
};


#endif //GAMEENGINE_OCEAN_H
