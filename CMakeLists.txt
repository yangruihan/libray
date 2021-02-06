cmake_minimum_required(VERSION 3.1)

set(ROOT_PROJ_NAME Ray)

project(${ROOT_PROJ_NAME})

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

option(DEBUG "Debug Version" on)

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "Debug: ${DEBUG}")

if(DEBUG)
    add_definitions(-DDEBUG)    
endif(DEBUG)

set(ROOT_SOURCE_DIR ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/libs/SDL2/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/sdl-gpu/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/lua53/src)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# set variables
set(SDL2_INCLUDE_DIR ${ROOT_SOURCE_DIR}/libs/SDL2/include)
set(SDL2_LIBRARY SDL2)
set(SDL2MAIN_LIBRARY SDL2main)

add_subdirectory(libs/lua53)
add_subdirectory(libs/SDL2)
add_subdirectory(libs/sdl-gpu)
add_subdirectory(libray)
add_subdirectory(ray)
