cmake_minimum_required(VERSION 3.5.2)

set(ENV{CMAKE_EXPORT_COMPILE_COMMANDS} TRUE)

project(Chess LANGUAGES C)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/helpers_c.cmake)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(_INCLUDE_DIR ${_BASE_DIR}/include)
set(_SOURCE_DIR ${_BASE_DIR}/src)

add_executable(
    ${PROJECT_NAME}
        ${_INCLUDE_DIR}/common/CommonDefines.h
        ${_INCLUDE_DIR}/common/TimerDefines.h
        ${_INCLUDE_DIR}/engine/Engine.h
        ${_INCLUDE_DIR}/engine/config/EngineConfig.h
        ${_INCLUDE_DIR}/engine/EngineConfigLoader.h
        ${_INCLUDE_DIR}/game/config/GameCfg.h
        ${_INCLUDE_DIR}/game/Game.h
        ${_INCLUDE_DIR}/game/entities/Hero.h
        ${_INCLUDE_DIR}/game/entities/Wheel.h
        ${_INCLUDE_DIR}/game/entities/buttons/WheelButton.h
        ${_INCLUDE_DIR}/game/proxies/GameInterface.h


        ${_SOURCE_DIR}/main.c
        ${_SOURCE_DIR}/engine/Engine.c
        ${_SOURCE_DIR}/engine/EngineConfigLoader.c
        ${_SOURCE_DIR}/game/Game.c
        ${_SOURCE_DIR}/game/entities/Hero.c
        ${_SOURCE_DIR}/game/entities/Wheel.c
        ${_SOURCE_DIR}/game/entities/buttons/WheelButton.c
)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})
#enable_target_c_sanitizer(${PROJECT_NAME} "address")

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            ${_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PRIVATE
            manager_utils
)

add_subdirectory(utils)
add_subdirectory(sdl_utils)
add_subdirectory(manager_utils)

if(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(
        ${PROJECT_NAME}
            PRIVATE
                -DRELEASE_BUILD=1   
    )
    add_custom_command( 
        TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/resources/
                $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/
    )
endif()