aux_source_directory(./src SRC_FILES)

set(PROJ_NAME ray)

project(${PROJ_NAME})

file(GLOB HEADERS "./*.h")

source_group("Headers" FILES ${HEADERS_PLUS})
source_group("Headers" FILES ${HEADERS})

# set output path
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

add_executable(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS_PLUS}
    ${HEADERS}
)

target_link_libraries(
    ${PROJ_NAME}
    Lua
    SDL2
)

add_custom_command(TARGET ${PROJ_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/scripts" "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}/Debug/scripts")