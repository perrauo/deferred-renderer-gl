set(TARGET_NAME "GhostGameFramework")

# Add a definition for GHOSTGAME_FRAMEWORK_EXPORTS when building this library
add_definitions(-DGHOSTGAME_FRAMEWORK_EXPORTS)

file(GLOB_RECURSE SHADER_FILES
    ${CMAKE_SOURCE_DIR}/resources/framework/*.vert
    ${CMAKE_SOURCE_DIR}/resources/framework/*.frag
)

# Add your source files
file(GLOB SOURCES "*.cpp")

source_group("Resources" FILES ${SHADER_FILES})

# Add library
add_library(${TARGET_NAME} SHARED ${SOURCES})

# Link libraries
target_link_libraries(${TARGET_NAME} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES} assimp)

# Include directories
target_include_directories(${TARGET_NAME} PRIVATE ${assimp_INCLUDE_DIRS} include )

# Set the output directory for the library to the bin folder at the root of the repository
set_target_properties(${TARGET_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

function(copy_files TARGET)
    foreach(FILE ${ARGN})
        file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${FILE})
        get_filename_component(DIR ${REL_PATH} DIRECTORY)
        add_custom_command(TARGET ${TARGET} POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${TARGET}>/${DIR}
                           COMMAND ${CMAKE_COMMAND} -E copy
                           ${FILE} $<TARGET_FILE_DIR:${TARGET}>/${DIR})
    endforeach()
endfunction()


# Copy files to build directory
copy_files(${TARGET_NAME} ${ENV_FILES} ${SHADER_FILES})