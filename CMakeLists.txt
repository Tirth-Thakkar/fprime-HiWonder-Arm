####
# This sets up the build system for the 'FprimeHiwonderArm' project, including
# components and deployments from project.cmake. In addition, it imports the core F Prime components.
####

cmake_minimum_required(VERSION 3.24.2)
project(FprimeHiwonderArm C CXX)

###############################################################################
#       Project and Tool Configuration for Project Dependencies               #
###############################################################################

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Local install prefix" FORCE)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=c++17>)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER   "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    message(STATUS "Build Optimization: Using ccache for faster rebuilds")
endif()
###############################################################################

# F Prime Project Configuration
include("${CMAKE_CURRENT_LIST_DIR}/lib/fprime/cmake/FPrime.cmake")

fprime_setup_included_code()

###############################################################################
#       External Dependencies Needed for Kinematics + Motion Planning         #
###############################################################################
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/eigen")

set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/eigen" CACHE PATH "" FORCE)
set(Eigen3_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/eigen" CACHE PATH "" FORCE)

if(NOT TARGET Eigen3::Eigen)
    add_library(Eigen3::Eigen INTERFACE IMPORTED GLOBAL)
    set_target_properties(Eigen3::Eigen PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/lib/eigen"
    )
    
    set(Eigen3_FOUND TRUE CACHE INTERNAL "")
    set(EIGEN3_FOUND TRUE CACHE INTERNAL "")
    set(EIGEN3_VERSION_OK TRUE CACHE INTERNAL "") 
    set(Eigen3_VERSION "3.4.0" CACHE INTERNAL "") 
endif()

add_subdirectory(
    "${FPRIME_PROJECT_ROOT}/lib/orocos_kinematics_dynamics/orocos_kdl" 
    "${CMAKE_BINARY_DIR}/orocos_kdl_build"
)

# Currently Motion Tracking is not used.
option (BUILD_OPENCV "Build OpenCV" OFF)
if(BUILD_OPENCV)
    set(BUILD_LIST "core;videoio;imgproc" CACHE STRING "" FORCE) 
    set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)
    set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(BUILD_JAVA OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_python2 OFF CACHE BOOL "" FORCE)
    set(BUILD_opencv_python3 OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

    set(CV_ENABLE_INTRINSICS OFF CACHE BOOL "" FORCE) 
    set(WITH_ITT OFF CACHE BOOL "" FORCE)             
    set(WITH_OPENCL OFF CACHE BOOL "" FORCE)
    
    set(OPENCV_BIN_INSTALL_PATH "bin" CACHE STRING "" FORCE)
    set(OPENCV_LIB_INSTALL_PATH "lib" CACHE STRING "" FORCE)
    set(OPENCV_INCLUDE_INSTALL_PATH "include" CACHE STRING "" FORCE)
    set(OPENCV_CONFIG_INSTALL_PATH "cmake" CACHE STRING "" FORCE)
    set(OPENCV_INSTALL_BINARIES_PREFIX "" CACHE STRING "" FORCE)

    add_subdirectory(
        "${CMAKE_CURRENT_LIST_DIR}/lib/opencv"
        "${CMAKE_BINARY_DIR}/opencv_build"
    )
endif()
###############################################################################

###############################################################################
#                           Internal F Prime Components                       #
###############################################################################

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Local project install prefix" FORCE)
include("${CMAKE_CURRENT_LIST_DIR}/project.cmake") 