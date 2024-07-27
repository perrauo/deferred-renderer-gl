project(Framework)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add a definition for GHOSTGAME_FRAMEWORK_EXPORTS when building this library
add_definitions(-DGHOSTGAME_FRAMEWORK_EXPORTS)

file(GLOB_RECURSE SHADER_FILES
    ${CMAKE_SOURCE_DIR}/resources/framework/*.vert
    ${CMAKE_SOURCE_DIR}/resources/framework/*.frag
)

# Add your source files
file(GLOB SOURCES "*.cpp")

# Add library
add_library(${PROJECT_NAME} ${SOURCES} ${SHADER_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES} assimp)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${assimp_INCLUDE_DIRS} include )
