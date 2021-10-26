cmake_minimum_required(VERSION 3.5.2)

project(utils LANGUAGES C)

set(_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_HEADERS_DIR ${_INCLUDE_DIR}/utils)
set(_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME} STATIC
        ${_HEADERS_DIR}/Log.h
        ${_HEADERS_DIR}/ErrorCodes.h
        ${_HEADERS_DIR}/containers/Vector.h
        ${_HEADERS_DIR}/drawing/Point.h
        ${_HEADERS_DIR}/drawing/Rectangle.h
        ${_HEADERS_DIR}/drawing/Color.h
        ${_HEADERS_DIR}/drawing/DrawParams.h
        ${_HEADERS_DIR}/input/EventDefines.h
        ${_HEADERS_DIR}/time/Time.h
        ${_HEADERS_DIR}/thread/Thread.h

        ${_SOURCE_DIR}/containers/Vector.c
        ${_SOURCE_DIR}/drawing/Point.c
        ${_SOURCE_DIR}/drawing/Rectangle.c
        ${_SOURCE_DIR}/drawing/Color.c
        ${_SOURCE_DIR}/drawing/DrawParams.c
        ${_SOURCE_DIR}/time/Time.c
        ${_SOURCE_DIR}/thread/Thread.c
)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
        ${_INCLUDE_DIR}
)

target_compile_definitions(
    ${PROJECT_NAME}
        PRIVATE
        _DEFAULT_SOURCE=1
)