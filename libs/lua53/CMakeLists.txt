aux_source_directory(./src SRC_FILES)

set(PROJ_NAME Lua)

project(${PROJ_NAME})

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")

source_group("Headers" FILES ${HEADERS})

add_library(
    ${PROJ_NAME}
    ${SRC_FILES}
    ${HEADERS}
)

target_link_libraries(
    ${PROJ_NAME}
)
