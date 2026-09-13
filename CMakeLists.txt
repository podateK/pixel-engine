cmake_minimum_required(VERSION 3.16)
project(PixelEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

add_library(PixelEngine STATIC
    src/engine/Engine.cpp
    src/engine/Window.cpp
    src/engine/Time.cpp
    src/engine/ecs/World.cpp
    src/engine/graphics/Renderer.cpp
    src/engine/graphics/Camera.cpp
    src/engine/graphics/Animation.cpp
    src/engine/physics/PhysicsWorld.cpp
    src/engine/physics/Collision.cpp
    src/engine/audio/SoundManager.cpp
    src/engine/input/InputManager.cpp
    src/engine/scene/SceneManager.cpp
    src/engine/resources/AssetManager.cpp
)

target_include_directories(PixelEngine PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(PixelEngine PUBLIC
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

target_compile_features(PixelEngine PUBLIC cxx_std_17)

option(PIXEL_BUILD_EXAMPLES "Build example projects" ON)

if(PIXEL_BUILD_EXAMPLES)
    add_subdirectory(examples/pong)
    add_subdirectory(examples/platformer)
endif()
