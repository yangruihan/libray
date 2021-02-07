set(PROJ_NAME ray)

project(${PROJ_NAME})

file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c")

file(GLOB HEADERS 
    "${PROJECT_SOURCE_DIR}/src/*.h")

# set output path
if (WIN32)
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
else (WIN32)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug")
    else(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Release")
    endif(CMAKE_BUILD_TYPE MATCHES "Debug")
endif (WIN32)

include_directories(${ROOT_SOURCE_DIR}/libray/src)

add_definitions(-DLIBRAY_DYNAMIC_LINK)

add_executable(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS}
)

target_link_libraries(
    ${PROJ_NAME}
    libray
)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug/scripts")

    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/scripts" "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug/scripts")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Release/scripts")

    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/scripts" "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Release/scripts")
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

if (UseVSCode)
    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${ROOT_SOURCE_DIR}/scripts")

    add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/scripts" "${ROOT_SOURCE_DIR}/scripts")
endif (UseVSCode)