//
// Created by zowlyfon on 27/11/2020.
//

#include "Asteroid.h"

Asteroid::Asteroid(Shader *shader, ComputeShader *computeShader, unsigned int subs)
{
    IcoSphere::subs = subs;
    RenderObject::shader = shader;
    RenderObject::computeShader = computeShader;
}

Asteroid::~Asteroid()=default;