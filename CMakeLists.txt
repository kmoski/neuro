cmake_minimum_required(VERSION 3.16)
project(neuro)
set(CMAKE_CXX_STANDARD 20)

# neuro

set(TARGET_NEURO neuro)
add_library(${TARGET_NEURO} STATIC)
set(NEURO_SOURCE
    src/neuron.h
    src/neural_net.h src/neural_net.cpp)
target_sources(${TARGET_NEURO}
    PUBLIC ${NEURO_SOURCE})

# tests

find_package(GTest)
enable_testing()

set(TARGET_TESTS ${TARGET_NEURO}_test)
add_executable(${TARGET_TESTS})
set(TEST_MAIN_ENTRY
    test/main.cpp)
set(UNIT_SOURCE
    test/unit/neural_net.h test/unit/neural_net.cpp)
add_dependencies(${TARGET_TESTS} ${TARGET_NEURO})
target_sources(${TARGET_TESTS}
    PRIVATE ${TEST_MAIN_ENTRY}
    PUBLIC ${UNIT_SOURCE})
target_include_directories(${TARGET_TESTS}
    PRIVATE ${GTEST_INCLUDE_DIR})
target_link_libraries(${TARGET_TESTS}
    ${TARGET_NEURO}
    gtest
    gtest_main
    pthread)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
install(TARGETS ${TARGET_TESTS} RUNTIME)
install(TARGETS ${TARGET_NEURO} LIBRARY)
