
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

# set output path
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
else(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
endif(CMAKE_BUILD_TYPE MATCHES "Debug")

include_directories(${ROOT_SOURCE_DIR}/libray/src)

add_library(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS}
)

target_link_libraries(
    ${PROJ_NAME}
    Lua
    SDL2
)
