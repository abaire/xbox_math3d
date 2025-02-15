cmake_minimum_required(VERSION 3.18)
project(xbox_math_tests)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Og")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Og")

enable_testing()
find_package(
        Boost 1.70
        COMPONENTS
        unit_test_framework
        REQUIRED
)
include_directories("${Boost_INCLUDE_DIR}")

# Tests ----------------------------------------------

set(library_source_directory "${CMAKE_HOME_DIRECTORY}/../src")

add_executable(
        xbox_math_tests
        d3d_tests.cpp
        matrix_tests.cpp
        matrix_vector_tests.cpp
        test_main.cpp
        types_tests.cpp
        util_tests.cpp
        vector_tests.cpp
        "${library_source_directory}/xbox_math_d3d.cpp"
        "${library_source_directory}/xbox_math_d3d.h"
        "${library_source_directory}/xbox_math_frustum.cpp"
        "${library_source_directory}/xbox_math_frustum.h"
        "${library_source_directory}/xbox_math_matrix.cpp"
        "${library_source_directory}/xbox_math_matrix.h"
        "${library_source_directory}/xbox_math_quaternion.cpp"
        "${library_source_directory}/xbox_math_quaternion.h"
        "${library_source_directory}/xbox_math_types.cpp"
        "${library_source_directory}/xbox_math_types.h"
        "${library_source_directory}/xbox_math_util.cpp"
        "${library_source_directory}/xbox_math_util.h"
        "${library_source_directory}/xbox_math_vector.cpp"
        "${library_source_directory}/xbox_math_vector.h"
        util_tests.cpp
)
target_include_directories(
        xbox_math_tests
        PRIVATE "${library_source_directory}"
)
target_link_libraries(
        xbox_math_tests
        LINK_PRIVATE
        "${Boost_LIBRARIES}"
)
add_test(NAME xbox_math_tests COMMAND xbox_math_tests)
