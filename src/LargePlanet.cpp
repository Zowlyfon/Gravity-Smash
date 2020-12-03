//
// Created by zowlyfon on 02/12/2020.
//

#include "LargePlanet.h"

LargePlanet::LargePlanet(Shader *shader,
                         ComputeShader *computeShader,
                         unsigned int subs)
{
    IcoSphere::subs = subs;
    RenderObject::shader = shader;
    RenderObject::computeShader = computeShader;
}

LargePlanet::~LargePlanet()
= default;