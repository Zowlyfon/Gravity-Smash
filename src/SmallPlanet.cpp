//
// Created by zowlyfon on 01/12/2020.
//

#include "SmallPlanet.h"

SmallPlanet::SmallPlanet(Shader *shader, ComputeShader *computeShader, unsigned int subs)
{
    IcoSphere::subs = subs;
    RenderObject::shader = shader;
    RenderObject::computeShader = computeShader;
}

SmallPlanet::~SmallPlanet()
= default;