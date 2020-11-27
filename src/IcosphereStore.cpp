//
// Created by zowlyfon on 26/11/2020.
//

#include "IcosphereStore.h"

IcosphereStore::IcosphereStore()
{

}

IcosphereStore::~IcosphereStore()
{

}

std::vector<glm::vec4> IcosphereStore::getIcosphere(unsigned int subs) {
    auto sphereExists =  icospheres.find(subs);
    if (sphereExists != icospheres.end()) {
        return sphereExists->second;
    }
}