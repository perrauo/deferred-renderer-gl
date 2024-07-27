project(Game)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SHADER_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/*.vert
    ${CMAKE_SOURCE_DIR}/resources/game/*.frag
)

file(GLOB_RECURSE CONFIG_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/*.json
)

# Add all files in the environment directory
file(GLOB_RECURSE ENVIRONMENT_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/environment/*
)

# Add your source files
file(GLOB SOURCES "*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${SHADER_FILES} ${ENVIRONMENT_FILES} ${CONFIG_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} Framework ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES} assimp)

target_include_directories(${PROJECT_NAME} PRIVATE include ${CMAKE_CURRENT_SOURCE_DIR}/src/framework)

# Create a source group for sponza resources
source_group("Resources" FILES ${ENVIRONMENT_FILES} ${SHADER_FILES} ${CONFIG_FILES})

# Copy env directory to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resources/game/environment $<TARGET_FILE_DIR:${PROJECT_NAME}>/environment)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/resources/game/entities $<TARGET_FILE_DIR:${PROJECT_NAME}>/entities)

# Copy shader files to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${SHADER_FILES} ${CMAKE_BINARY_DIR}/shaders)

# Copy config files to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CONFIG_FILES} ${CMAKE_BINARY_DIR}/config)
