project(GhostGame)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE ENEMY_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.vert
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.frag
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.jpg
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.jpeg
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.png
    ${CMAKE_SOURCE_DIR}/resources/game/entities/enemy/*.dae
)

# Add all files in the environment directory
file(GLOB_RECURSE ENV_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/environment/*.dae
    ${CMAKE_SOURCE_DIR}/resources/game/environment/*.dds
)

file(GLOB_RECURSE CONFIG_FILES
    ${CMAKE_SOURCE_DIR}/resources/game/configs/*.json
)

# Add your source files
file(GLOB SOURCES "*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} GhostGameFramework ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES} assimp)

target_include_directories(${PROJECT_NAME} PRIVATE include ${CMAKE_CURRENT_SOURCE_DIR}/src/framework)

# Create a source group for sponza resources
source_group("Resources" FILES ${ENV_FILES} ${SHADER_FILES} ${CONFIG_FILES})

# Set the output directory for the binary to the bin folder at the root of the repository
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Function to copy files preserving relative paths
function(copy_files TARGET FILES)
    foreach(FILE ${FILES})
        file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${FILE})
        get_filename_component(DIR ${REL_PATH} DIRECTORY)
        add_custom_command(TARGET ${TARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy
                           ${FILE} $<TARGET_FILE_DIR:${TARGET}>/${DIR})
    endforeach()
endfunction()

# Copy files to build directory
copy_files(${PROJECT_NAME} ${ENV_FILES})
copy_files(${PROJECT_NAME} ${ENEMY_FILES})
copy_files(${PROJECT_NAME} ${CONFIG_FILES})
