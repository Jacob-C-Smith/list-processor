# Need CMake 3.16.0
cmake_minimum_required (VERSION 3.16.0)

# This is the name of the repository
project ("list-processor")

# Build sync with semaphore
add_compile_definitions(BUILD_SYNC_WITH_SEMAPHORE)

# Build sync with monitor
add_compile_definitions(BUILD_SYNC_WITH_MONITOR)

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode`
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif ()

add_compile_options(-gdwarf-4 -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference)

# Find the hash cache module
if ( NOT "${HAS_HASH_CACHE}")

    # Add the hash cache directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/hash-cache ${CMAKE_SOURCE_DIR}/build/hash-cache)

    # Let any parent project know that this project has hash cache
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_HASH_CACHE true PARENT_SCOPE)
        set(HASH_CACHE_INCLUDE_DIR ${HASH_CACHE_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the array module
if ( NOT "${HAS_ARRAY}")
    
    # Add the array directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/array ${CMAKE_SOURCE_DIR}/build/array)

    # Let any parent project know that this project has array
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_ARRAY true PARENT_SCOPE)
        set(ARRAY_INCLUDE_DIR ${ARRAY_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the dict module
if ( NOT "${HAS_DICT}")
    
    # Add the dict directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/dict ${CMAKE_SOURCE_DIR}/build/dict)

    # Let any parent project know that this project has dict
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_DICT true PARENT_SCOPE)
        set(DICT_INCLUDE_DIR ${DICT_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the log module
if ( NOT "${HAS_LOG}")

    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the json module
if ( NOT "${HAS_JSON}")

    # Add the json directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/json ${CMAKE_SOURCE_DIR}/build/json)

    # Let any parent project know that this project has json
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_JSON true PARENT_SCOPE)
        set(JSON_INCLUDE_DIR ${JSON_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the node module
if ( NOT "${HAS_NODE}")

    # Add the node directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/node ${CMAKE_SOURCE_DIR}/build/node)

    # Let any parent project know that this project has node
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_NODE true PARENT_SCOPE)
        set(NODE_INCLUDE_DIR ${NODE_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the parallel module
if ( NOT "${HAS_PARALLEL}")

    # Add the parallel directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/parallel ${CMAKE_SOURCE_DIR}/build/parallel)

    # Let any parent project know that this project has parallel
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_PARALLEL true PARENT_SCOPE)
        set(PARALLEL_INCLUDE_DIR ${PARALLEL_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Set the list processor module
if ( NOT "${HAS_LIST_PROCESSOR}")

    # Log
    message("[list processor] Adding list processor project")

    # Set the list processor include
    set(LIST_PROCESSOR_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the list processor project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LIST_PROCESSOR true PARENT_SCOPE)
        set(LIST_PROCESSOR_INCLUDE_DIR ${LIST_PROCESSOR_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()


# Add source to this project's executable.
add_executable (lexer "lexer.c")
add_dependencies(lexer json)
target_include_directories(lexer PUBLIC ${LIST_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(lexer parallel node json array dict sync)

add_executable (syntax "syntax.c")
add_dependencies(syntax json)
target_include_directories(syntax PUBLIC ${LIST_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(syntax parallel node json array dict sync)

add_executable (interpreter "interpreter.c")
add_dependencies(interpreter list_processor parallel node json array dict sync)
target_include_directories(interpreter PUBLIC ${LIST_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(interpreter list_processor parallel node json array dict sync)

add_library (my_module SHARED "my_module.c" )
add_dependencies(my_module list_processor parallel node json array dict sync)
target_include_directories(my_module PUBLIC ${LIST_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(my_module PRIVATE list_processor parallel node json array dict sync)

add_library (list_processor SHARED "list_processor.c" "module/main.c" "module/arithmetic.c" "module/logic.c" "module/relational.c" "module/control.c" "module/string.c" "module/io.c" "module/module.c" "module/env.c")
add_dependencies(list_processor parallel node json array dict sync)
target_include_directories(list_processor PUBLIC ${LIST_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(list_processor PRIVATE parallel node json array dict sync)

# Add source to project's util
add_executable (lexer_pretty_print "lexer_pretty_printer.c")
add_dependencies(lexer_pretty_print json)
target_include_directories(lexer_pretty_print PUBLIC ${LIST_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(lexer_pretty_print parallel node json array dict sync)
