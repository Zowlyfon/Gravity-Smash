//
// Created by zowlyfon on 01/12/2020.
//

#include "GameEffect.h"

GameEffect::GameEffect(Shader *shader, ComputeShader *computeShader, unsigned int subs)
{
    IcoSphere::subs = subs;
    RenderObject::shader = shader;
    RenderObject::computeShader = computeShader;
}

GameEffect::~GameEffect()
= default;