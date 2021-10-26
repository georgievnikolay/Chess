cmake_minimum_required(VERSION 3.5.2)

project(manager_utils LANGUAGES C)

set(_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_HEADERS_DIR ${_INCLUDE_DIR}/manager_utils)
set(_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME} 
        STATIC
        ${_HEADERS_DIR}/common/DebugConsole.h
        ${_HEADERS_DIR}/managers/ManagerHandler.h
        ${_HEADERS_DIR}/managers/DrawMgr.h
        ${_HEADERS_DIR}/managers/RsrcMgr.h
        ${_HEADERS_DIR}/managers/TimerMgr.h
        ${_HEADERS_DIR}/managers/config/RsrcMgrCfg.h
        ${_HEADERS_DIR}/managers/config/DrawMgrCfg.h
        ${_HEADERS_DIR}/managers/config/ManagerHandlerCfg.h
        ${_HEADERS_DIR}/drawing/Widget.h
        ${_HEADERS_DIR}/drawing/Image.h
        ${_HEADERS_DIR}/drawing/Text.h
        ${_HEADERS_DIR}/input/Button.h
        ${_HEADERS_DIR}/time/TimerData.h
        ${_HEADERS_DIR}/time/TimerClient.h

        ${_SOURCE_DIR}/common/DebugConsole.c
        ${_SOURCE_DIR}/managers/ManagerHandler.c
        ${_SOURCE_DIR}/managers/DrawMgr.c
        ${_SOURCE_DIR}/managers/RsrcMgr.c
        ${_SOURCE_DIR}/managers/TimerMgr.c
        ${_SOURCE_DIR}/drawing/Widget.c
        ${_SOURCE_DIR}/drawing/Image.c
        ${_SOURCE_DIR}/drawing/Text.c
        ${_SOURCE_DIR}/input/Button.c
        ${_SOURCE_DIR}/time/TimerData.c
        ${_SOURCE_DIR}/time/TimerClient.c
)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
        ${_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PUBLIC
            sdl_utils   
)