//
// Created by zowlyfon on 21/11/2020.
//

#include "RenderObject.h"

RenderObject::RenderObject() :
position(glm::vec3(0.0f)), color(glm::vec3(0.5f)), scale(1.0f),
VAO(0), VBO(0), EBO(0)
{

}

RenderObject::~RenderObject() = default;

void RenderObject::init()
{

}

void RenderObject::draw(Shader *shader, float playerSize)
{

}

void RenderObject::calculateNormals()
{

}