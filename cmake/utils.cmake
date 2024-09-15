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

function(exclude_hidden_dirs input_dirs output_dirs)
    set(filtered_list "")
    foreach(dir ${input_dirs})
        if(NOT dir MATCHES "/\\.[^/]+/")
            list(APPEND filtered_list ${dir})
        endif()
    endforeach()
    set(${output_dirs} ${filtered_list} PARENT_SCOPE)
endfunction()