cmake_minimum_required(VERSION 3.18)
project(xbox_math3d VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(xbox_math3d
        src/xbox_math_d3d.cpp
        src/xbox_math_d3d.h
        src/xbox_math_frustum.cpp
        src/xbox_math_frustum.h
        src/xbox_math_matrix.cpp
        src/xbox_math_matrix.h
        src/xbox_math_quaternion.cpp
        src/xbox_math_quaternion.h
        src/xbox_math_types.cpp
        src/xbox_math_types.h
        src/xbox_math_util.cpp
        src/xbox_math_util.h
        src/xbox_math_vector.cpp
        src/xbox_math_vector.h
)

install(
        TARGETS
        xbox_math3d
        DESTINATION
        lib
)

install(
        FILES
        src/xbox_math_d3d.h
        src/xbox_math_frustum.h
        src/xbox_math_matrix.h
        src/xbox_math_quaternion.h
        src/xbox_math_types.h
        src/xbox_math_util.h
        src/xbox_math_vector.h
        DESTINATION
        include
)
