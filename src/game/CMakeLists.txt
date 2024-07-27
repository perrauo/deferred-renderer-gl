project(Game)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SHADER_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/*.vert
    ${CMAKE_SOURCE_DIR}/resources/game/*.frag
)

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SHADER_FILES})

# Add your source files
file(GLOB SOURCES "*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${SHADER_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} Engine ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES})
