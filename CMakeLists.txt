cmake_minimum_required(VERSION 3.18)
project(xbox_math3d VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
        _HEADERS
        src/xbox_math_d3d.h
        src/xbox_math_frustum.h
        src/xbox_math_matrix.h
        src/xbox_math_quaternion.h
        src/xbox_math_types.h
        src/xbox_math_util.h
        src/xbox_math_vector.h
)

add_library(
        ${PROJECT_NAME}
        src/xbox_math_d3d.cpp
        src/xbox_math_frustum.cpp
        src/xbox_math_matrix.cpp
        src/xbox_math_quaternion.cpp
        src/xbox_math_types.cpp
        src/xbox_math_util.cpp
        src/xbox_math_vector.cpp
        ${_HEADERS}
)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE
        _USE_MATH_DEFINES
)

set_property(
        TARGET
        ${PROJECT_NAME}
        PROPERTY
        PUBLIC_HEADER ${_HEADERS}
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
        TARGETS
        ${PROJECT_NAME}
        EXPORT XboxMathTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/XboxMathConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
        "cmake/XboxMathConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/XboxMathConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
        EXPORT XboxMathTargets
        FILE XboxMathTargets.cmake
        NAMESPACE XboxMath::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/XboxMathConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/XboxMathConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
