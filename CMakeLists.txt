cmake_minimum_required(VERSION 3.3)
project(MiceWars)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf)

set(SOURCE_FILES
        src/AI.h
        src/AI.cpp
        src/Button.h
        src/Button.cpp
        src/Game.h
        src/Game.cpp
        src/Mouse.h
        src/Mouse.cpp
        src/NotificationBox.h
        src/NotificationBox.cpp
        src/Object.h
        src/Object.cpp
        src/PlacedWeapon.h
        src/PlacedWeapon.cpp
        src/Player.h
        src/Player.cpp
        src/RangedWeapon.h
        src/RangedWeapon.cpp
        src/ThrownWeapon.h
        src/ThrownWeapon.cpp
        src/Weapon.h
        src/Weapon.cpp
        src/main.cpp
        src/global_vars.h src/Engine.cpp src/Engine.h)

add_executable(MiceWars ${SOURCE_FILES})

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR})

target_link_libraries(MiceWars
                        ${SDL2_LIBRARY}
                        ${SDL2_IMAGE_LIBRARIES})