cmake_minimum_required(VERSION 3.17)
project(neuro)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_MAIN_ENTRY main.cpp)

set(PROJECT_SOURCE
    ${PROJECT_MAIN_ENTRY}
    src/neuron.cpp src/neuron.h
    src/connection.cpp src/connection.h
    src/nerve.cpp src/nerve.h
    src/neuro_def.h)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)
