cmake_minimum_required(VERSION 3.17)
project(neuro)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_MAIN_ENTRY main.cpp)

set(PROJECT_SOURCE
    src/neuron.cpp src/neuron.h
    src/neuro_def.h
    src/simple_builder.cpp src/simple_builder.h
    src/neuro_net.cpp src/neuro_net.h)

add_executable(${PROJECT_NAME} ${PROJECT_MAIN_ENTRY} ${PROJECT_SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# Tests

find_package(GTest)
enable_testing()

set(TEST_MAIN_ENTRY
    test/main.cpp)

set(TEST_SOURCE
    test/simple_builder.cpp)

add_executable(${PROJECT_NAME}_test ${TEST_MAIN_ENTRY} ${TEST_SOURCE} ${PROJECT_SOURCE})
target_include_directories(${PROJECT_NAME}_test PUBLIC
                           ${GTEST_INCLUDE_DIR}
                           ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_test gtest gtest_main)