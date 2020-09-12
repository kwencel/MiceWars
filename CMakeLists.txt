cmake_minimum_required(VERSION 3.3)
project(MiceWars)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCE_FILES GLOB src/**.cpp src/**.h)

file (GLOB SOURCES src/**.cpp src/**.h)
add_executable(MiceWars ${SOURCES})

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(MiceWars
                        ${SDL2_LIBRARY}
                        ${SDL2_IMAGE_LIBRARIES}
                        ${SDL2_TTF_LIBRARY})
