cmake_minimum_required(VERSION 3.10)
project(GhostGameRenderer)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# Extra module
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# find packages
find_package(Boost 1.85.0 COMPONENTS system REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED) # Add this line for GLEW
find_package(GLUT REQUIRED) # Add this line for FreeGlut
find_package(GLFW REQUIRED)

# include directories
include_directories(${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} include)

# specify the executable
file(GLOB SOURCES "src/*.cpp")
file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag" "shaders/*.geom")
add_executable(GhostGameRenderer ${SOURCES} ${SHADERS})

# link libraries
target_link_libraries(GhostGameRenderer ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES})
