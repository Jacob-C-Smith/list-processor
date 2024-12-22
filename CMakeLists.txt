# Need CMake 3.16.0
cmake_minimum_required (VERSION 3.16.0)

# This is the name of the repository
project ("stream processor")

# Build sync with semaphore
add_compile_definitions(BUILD_SYNC_WITH_SEMAPHORE)

# Build sync with monitor
add_compile_definitions(BUILD_SYNC_WITH_MONITOR)

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
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

# Set the stream processor module
if ( NOT "${HAS_STREAM_PROCESSOR}")

    # Log
    message("[stream processor] Adding stream processor project")

    # Set the stream processor include
    set(STREAM_PROCESSOR_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the stream processor project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_STREAM_PROCESSOR true PARENT_SCOPE)
        set(STREAM_PROCESSOR_INCLUDE_DIR ${STREAM_PROCESSOR_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()


# Add source to this project's executable.
add_executable (eddy_lexer "eddy_lexer.c")
add_dependencies(eddy_lexer json)
target_include_directories(eddy_lexer PUBLIC ${STREAM_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(eddy_lexer parallel node json array dict sync)

add_executable (eddy_syntax "eddy_syntax.c")
add_dependencies(eddy_syntax json)
target_include_directories(eddy_syntax PUBLIC ${STREAM_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(eddy_syntax parallel node json array dict sync)

add_executable (eddy_interpreter "eddy_interpreter.c")
add_dependencies(eddy_interpreter json)
target_include_directories(eddy_interpreter PUBLIC ${STREAM_PROCESSOR_INCLUDE_DIR} ${PARALLEL_INCLUDE_DIR} ${NODE_INCLUDE_DIR} ${JSON_INCLUDE_DIR} ${ARRAY_INCLUDE_DIR} ${DICT_INCLUDE_DIR})
target_link_libraries(eddy_interpreter parallel node json array dict sync)
