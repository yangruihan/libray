set(PROJ_NAME ray)

project(${PROJ_NAME})

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c")

file(GLOB HEADERS 
    "${PROJECT_SOURCE_DIR}/src/*.h")

# set output path
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

include_directories(${ROOT_SOURCE_DIR}/libray/src)

add_executable(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS}
)

if (NOT WIN32)
    # Find OpenGL
    find_library(OpenGL OpenGL)
    if (NOT OpenGL)
        message(FATAL_ERROR "OpenGL")
    endif()
    
    target_link_libraries(
        ${PROJ_NAME}
        libray
        ${OpenGL}
    )
else(NOT WIN32)
    # Find OpenGL
    find_package(OpenGL REQUIRED)

    target_link_libraries(
        ${PROJ_NAME}
        libray
        opengl32
    )
endif(NOT WIN32)

add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug/scripts")

if (DEBUG)
    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/scripts" "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug/scripts")
else(DEBUG)
    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/scripts" "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Release/scripts")
endif(DEBUG)