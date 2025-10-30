# указывайте последнюю доступную вам версию CMake

cmake_minimum_required(VERSION 3.14)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ADS_matrix-implementation)

include(cmake/function.cmake)

add_subdirectory(lib_easy_example)
add_subdirectory(lib_point)
add_subdirectory(lib_circle)
add_subdirectory(lib_math_vector)
add_subdirectory(lib_matrix)
add_subdirectory(lib_matrix_console_ui)
add_subdirectory(lib_triangle_matrix)
add_subdirectory(lib_tvector)
add_subdirectory(lib_algorithms)

add_subdirectory(main)

option(BTEST "build test?" ON)

if(BTEST)   
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()


