
set(PROJ_NAME libray)

project(${PROJ_NAME})

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/common/*.c"
    "${PROJECT_SOURCE_DIR}/src/graphics/*.c"
    "${PROJECT_SOURCE_DIR}/src/timer/*.c")

file(GLOB HEADERS 
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/common/*.h"
    "${PROJECT_SOURCE_DIR}/src/graphics/*.h"
    "${PROJECT_SOURCE_DIR}/src/timer/*.h")

source_group("Headers" FILES ${HEADERS})

include_directories(${ROOT_SOURCE_DIR}/libray/src)

add_definitions(-DLIBRAY_BUILD)
add_definitions(-DLIBRAY_DYNAMIC_LINK)

if (WIN32)
    #link_directories("${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug")

    add_library(
        ${PROJ_NAME}
        SHARED
        ${SRC_FILES}
        ${HEADERS}
    )

    # Find OpenGL
    find_package(OpenGL REQUIRED)

    target_link_libraries(
        ${PROJ_NAME}
        Lua
        SDL2
        SDL_gpu
        opengl32
    )

    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/Debug/libray.dll" "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug/libray.dll")
    else (CMAKE_BUILD_TYPE MATCHES "Debug")
        add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "./build/Release/libray.dll" "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Release/libray.dll")
    endif (CMAKE_BUILD_TYPE MATCHES "Debug")

else (WIN32)
    add_library(
        ${PROJ_NAME}
        STATIC
        ${SRC_FILES}
        ${HEADERS}
    )

    # Find OpenGL
    find_library(OpenGL OpenGL)
    if (NOT OpenGL)
        message(FATAL_ERROR "OpenGL")
    endif()
    
    target_link_libraries(
        ${PROJ_NAME}
        Lua
        SDL2
        SDL_gpu
        ${OpenGL}
    )
endif (WIN32)
