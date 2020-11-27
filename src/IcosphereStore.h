//
// Created by zowlyfon on 26/11/2020.
//

#ifndef GAMEENGINE_ICOSPHERESTORE_H
#define GAMEENGINE_ICOSPHERESTORE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <map>

class IcosphereStore {
public:
    IcosphereStore();
    ~IcosphereStore();
    std::vector<glm::vec4> getIcosphere(unsigned int subs);

private:
    std::map<unsigned int, std::vector<glm::vec4>> icospheres;
};


#endif //GAMEENGINE_ICOSPHERESTORE_H
