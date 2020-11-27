//
// Created by zowlyfon on 21/11/2020.
//

#include "PhysicsObject.h"

PhysicsObject::PhysicsObject() :
velocity(glm::vec3(0.0f)), mass(0.0f), dead(false), baseSize(1.0f), baseMass(1.0f)
{

}

PhysicsObject::~PhysicsObject() = default;

void PhysicsObject::physics()
{

}

void PhysicsObject::updateMass()
{

}