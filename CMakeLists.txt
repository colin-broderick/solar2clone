cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

project(solarclone)
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC src/main.cpp src/entity.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
