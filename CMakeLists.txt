cmake_minimum_required(VERSION 3.17)
project(neuro)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_MAIN_ENTRY main.cpp)

set(PROJECT_SOURCE
    src/neuron.h src/neuron.cpp
    src/def.h
    src/builder.h src/builder.cpp
    src/neural_net.h src/neural_net.cpp
    )

add_executable(${PROJECT_NAME} ${PROJECT_MAIN_ENTRY} ${PROJECT_SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/inc)

# Tests

find_package(GTest)
enable_testing()

set(TARGET_UNIT_TESTS ${PROJECT_NAME}_unit)

set(TEST_MAIN_ENTRY
    test/main.cpp)

set(TEST_UNIT_SOURCE
    test/unit/builder.cpp test/unit/neural_net.cpp)

add_test(NAME ${TARGET_UNIT_TESTS}
         COMMAND ${TARGET_UNIT_TESTS})

add_executable(${TARGET_UNIT_TESTS}
               ${TEST_MAIN_ENTRY}
               ${TEST_UNIT_SOURCE}
               ${PROJECT_SOURCE})

target_include_directories(${TARGET_UNIT_TESTS} PUBLIC
                           ${GTEST_INCLUDE_DIR}
                           ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${TARGET_UNIT_TESTS}
                      gtest
                      gtest_main
                      pthread)
