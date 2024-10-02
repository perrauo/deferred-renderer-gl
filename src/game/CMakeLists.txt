set(TARGET_NAME "ExperimentDemo")

file(GLOB_RECURSE ENEMY_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.vert
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.frag
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.jpg
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.jpeg
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.png
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.dae
)
file(GLOB_RECURSE ENEMY_SHADER_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.vert
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.frag
)
exclude_hidden_dirs("${ENEMY_SHADER_FILES}" ENEMY_SHADER_FILES)

# Add all files in the environment directory
file(GLOB_RECURSE ENV_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/environment/*.dae
    ${CMAKE_SOURCE_DIR}/resources/game/environment/*.dds
    ${CMAKE_SOURCE_DIR}/resources/game/environment/*.ktx
)

file(GLOB_RECURSE CONFIG_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/*.json
)

# Add your source files
file(GLOB SOURCES "*.cpp")

# Add executable
add_executable(${TARGET_NAME} ${SOURCES} ${ENEMY_SHADER_FILES} ${CONFIG_FILES})

# Link libraries
target_link_libraries(${TARGET_NAME} ExperimentFramework ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} assimp)


target_include_directories(${TARGET_NAME} PRIVATE include ${CMAKE_CURRENT_SOURCE_DIR}/src/framework)

# Create a source group for sponza resources
source_group("Resources" FILES ${ENV_FILES} ${ENEMY_FILES} ${CONFIG_FILES})

set_target_properties(
    ${TARGET_NAME} 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/bin)

copy_files(${TARGET_NAME} ${ENV_FILES} ${ENEMY_FILES} ${CONFIG_FILES})

