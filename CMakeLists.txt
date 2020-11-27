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
        src/Sphere.cpp
        src/Sphere.h
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
        imgui/backends/imgui_impl_opengl3.cpp src/Background.cpp src/Background.h src/GUI.cpp src/GUI.h src/IcosphereStore.cpp src/IcosphereStore.h)

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
configure_file(addSimplexNoise.comp.glsl ${CMAKE_CURRENT_BINARY_DIR}/addSimplexNoise.comp.glsl COPYONLY)