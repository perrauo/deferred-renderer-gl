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

# Add all files in the sponza directory
file(GLOB_RECURSE SPONZA_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/environment/*
)

# Add your source files
file(GLOB SOURCES "*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${SHADER_FILES} ${SPONZA_FILES} ${CONFIG_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} Framework)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Create a source group for sponza resources
source_group("Resources" FILES ${SPONZA_FILES} ${SHADER_FILES} ${CONFIG_FILES})

# Copy sponza directory to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resources/game/sponza $<TARGET_FILE_DIR:${PROJECT_NAME}>/sponza)

# Copy shader files to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resources/game ${CMAKE_BINARY_DIR}/shaders
                   FILES_MATCHING PATTERN "*.vert" PATTERN "*.frag")

# Copy config files to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resources/game ${CMAKE_BINARY_DIR}/config
                   FILES_MATCHING PATTERN "*.json")
