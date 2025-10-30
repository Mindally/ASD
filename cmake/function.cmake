function(create_project_lib TARGET)
    file(GLOB TARGET_SRC "*.c*")
    file(GLOB TARGET_HD "*.h*")
    
    add_library(${TARGET} STATIC ${TARGET_SRC} ${TARGET_HD})
    
    if(ARGC GREATER 1)
        set(TARGET_FOLDER "${ARGV1}")
    else()
        file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
        set(TARGET_FOLDER "${REL_PATH}")
    endif()
    
    set_property(TARGET ${TARGET} PROPERTY FOLDER "${TARGET_FOLDER}")
    
    get_property(INCLUDE_DIRS GLOBAL PROPERTY INC_DIR)
    get_property(LIB_LIST GLOBAL PROPERTY LIBS_P)
    list(APPEND LIB_LIST ${TARGET})
    list(APPEND INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
    set_property(GLOBAL PROPERTY INC_DIR ${INCLUDE_DIRS})
    set_property(GLOBAL PROPERTY LIBS_P ${LIB_LIST}) 
endfunction()

function(create_executable_project TARGET)
    file(GLOB TARGET_SRC "*.c*")
    file(GLOB TARGET_HD "*.h*")
    
    add_executable(${TARGET} ${TARGET_SRC} ${TARGET_HD})

    if(ARGC GREATER 1)
        set(TARGET_FOLDER "${ARGV1}")
    else()
        set(TARGET_FOLDER "executables")
    endif()
    
    set_property(TARGET ${TARGET} PROPERTY FOLDER "${TARGET_FOLDER}")

    get_property(INCLUDE_DIRS GLOBAL PROPERTY INC_DIR)
    target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRS})
    get_property(LIB_LIST GLOBAL PROPERTY LIBS_P)
    target_link_libraries(${TARGET} ${LIB_LIST})    
endfunction()

function(add_depend TARGET LIB INCLUDE_DIR)
    target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIR})
    target_link_libraries(${TARGET} ${LIB}) 
endfunction()

function(add_gtest test_name test_source)
    add_executable(${test_name} ${test_source})
    target_include_directories(${test_name} PUBLIC ${CMAKE_SOURCE_DIR})
    target_link_libraries(${test_name} gtest gtest_main)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()