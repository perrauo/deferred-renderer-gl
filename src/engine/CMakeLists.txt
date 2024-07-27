project(Engine)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SHADER_FILES
    ${CMAKE_SOURCE_DIR}/resources/engine/*.vert
    ${CMAKE_SOURCE_DIR}/resources/engine/*.frag
)

# Add your source files
file(GLOB SOURCES "*.cpp")

# Add library
add_library(${PROJECT_NAME} ${SOURCES} ${SHADER_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES} ${ASSIMP_LIBRARIES})
