cmake_minimum_required(VERSION 3.10)
project(ExperimentDemo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

set(ASSIMP_BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORTER ON CACHE BOOL "")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
add_subdirectory(external/assimp)

add_definitions(-DSTB_IMAGE_IMPLEMENTATION)

# Extra module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/assimp/cmake-modules")
include(utils)

# find packages
find_package(Boost 1.85.0 COMPONENTS system json REQUIRED)
find_package(OpenGL REQUIRED)
add_definitions(-DGLEW_STATIC)
set(GLEW_USE_STATIC_LIBS TRUE)
find_package(GLEW REQUIRED static) # Add this line for GLEW
find_package(GLFW REQUIRED static)
find_package(assimp REQUIRED static)

# include directories
include_directories(${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} external/glm external/gli external/stb external/assimp/include include)

# Add subdirectories

add_subdirectory(src/framework)
add_subdirectory(src/game)
