cmake_minimum_required(VERSION 3.17)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(glad/include)
include_directories(imgui)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(glad/)

add_executable(GameEngine
        src/main.cpp
        src/Engine.cpp
        src/Engine.h
        src/RenderObject.cpp
        src/RenderObject.h
        src/Utility.cpp
        src/Utility.h
        src/PhysicsObject.cpp
        src/PhysicsObject.h
        src/Shader.cpp
        src/Shader.h
        src/Physics.cpp
        src/Physics.h
        src/ComputeShader.cpp
        src/ComputeShader.h
        imgui/imgui.h
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glfw.h
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.h
        imgui/backends/imgui_impl_opengl3.cpp
        src/Background.cpp
        src/Background.h src/GUI.cpp
        src/GUI.h src/IcosphereStore.cpp
        src/IcosphereStore.h
        src/Atmosphere.cpp
        src/Atmosphere.h
        src/IcoSphere.cpp
        src/IcoSphere.h
        src/Asteroid.cpp
        src/Asteroid.h
        src/GameObject.cpp
        src/GameObject.h
        src/GameLevel.cpp
        src/GameLevel.h
        src/AsteroidLevel.cpp
        src/AsteroidLevel.h
        src/GameSettings.cpp
        src/GameSettings.h
        src/SmallPlanetLevel.cpp
        src/SmallPlanetLevel.h
        src/SmallPlanet.cpp
        src/SmallPlanet.h src/GasGiant.cpp src/GasGiant.h src/GasGiantLevel.cpp src/GasGiantLevel.h src/MenuLevel.cpp src/MenuLevel.h)

target_link_libraries(GameEngine
        glad
        glfw
        tbb
        ${OPENGL_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ${CMAKE_DL_LIBS}
        )

configure_file(asteroid.frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/asteroid.frag.glsl COPYONLY)
configure_file(asteroid.vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/asteroid.vert.glsl COPYONLY)
#configure_file(geometry.glsl ${CMAKE_CURRENT_BINARY_DIR}/geometry.glsl COPYONLY)
configure_file(background.frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/background.frag.glsl COPYONLY)
configure_file(background.vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/background.vert.glsl COPYONLY)
configure_file(asteroidNoise.comp.glsl ${CMAKE_CURRENT_BINARY_DIR}/asteroidNoise.comp.glsl COPYONLY)
configure_file(planetNoise.comp.glsl ${CMAKE_CURRENT_BINARY_DIR}/planetNoise.comp.glsl COPYONLY)
configure_file(planet.frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/planet.frag.glsl COPYONLY)
configure_file(planet.vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/planet.vert.glsl COPYONLY)
configure_file(atmosphere.frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/atmosphere.frag.glsl COPYONLY)
configure_file(atmosphere.vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/atmosphere.vert.glsl COPYONLY)
configure_file(gasGiant.frag.glsl ${CMAKE_CURRENT_BINARY_DIR}/gasGiant.frag.glsl COPYONLY)
configure_file(gasGiant.vert.glsl ${CMAKE_CURRENT_BINARY_DIR}/gasGiant.vert.glsl COPYONLY)