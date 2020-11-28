//
// Created by zowlyfon on 27/11/2020.
//

#ifndef GAMEENGINE_ICOSPHERE_H
#define GAMEENGINE_ICOSPHERE_H

#include <map>
#include <algorithm>
#include <execution>
#include <map>

#include "PhysicsObject.h"
#include "ComputeShader.h"

class IcoSphere : public RenderObject{
public:
    explicit IcoSphere(unsigned int subs=4);
    ~IcoSphere();
    void init() override;
    void draw(float playerSize) override;

protected:
    void createIcosahedron();
    void subdivideMesh();
    void initIcosphere();

    std::map<std::pair<GLuint, GLuint>, GLuint> verticesMap;

    std::vector<glm::vec4> originalVertices;

    unsigned int subs;

private:
    GLuint getMidpoint(GLuint A, GLuint B);
};


#endif //GAMEENGINE_ICOSPHERE_H
