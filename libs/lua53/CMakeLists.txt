aux_source_directory(./src SRC_FILES)

set(PROJ_NAME Lua)

project(${PROJ_NAME})

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")

source_group("Headers" FILES ${HEADERS})

# set output path
if (WIN32)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
    else(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/${ROOT_PROJ_NAME}")
    endif(CMAKE_BUILD_TYPE MATCHES "Debug")
else (WIN32)
    if (CMAKE_BUILD_TYPE MATCHES "Debug")
        set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/Debug/${ROOT_PROJ_NAME}")
    else(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(EXECUTABLE_OUTPUT_PATH "${ROOT_SOURCE_DIR}/bin/Release/${ROOT_PROJ_NAME}")
    endif(CMAKE_BUILD_TYPE MATCHES "Debug")
endif (WIN32)

add_library(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS}
)

target_link_libraries(
    ${PROJ_NAME}
)
