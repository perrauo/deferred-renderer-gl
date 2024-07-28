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
# Let the shader file show up in the project
add_library(${TARGET_NAME} SHARED ${SOURCES} ${SHADER_FILES})

# Link libraries
target_link_libraries(${TARGET_NAME} PUBLIC ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LIBRARIES} PRIVATE assimp assimp::assimp)

# Include directories
target_include_directories(${TARGET_NAME} PRIVATE ${assimp_INCLUDE_DIRS} include )

set_target_properties(${TARGET_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/bin)


# Copy files to build directory
copy_files(${TARGET_NAME} ${ENV_FILES} ${SHADER_FILES})

if(GLEW_FOUND)
  message("GLEW Libraries: ${GLEW_LIBRARIES}")
  file(COPY ${GLEW_LIBRARIES} DESTINATION ${CMAKE_BINARY_DIR}/bin)
endif()