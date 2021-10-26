cmake_minimum_required(VERSION 3.5.2)

project(sdl_utils LANGUAGES C)

set(_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(_HEADERS_DIR ${_INCLUDE_DIR}/${PROJECT_NAME})
set(_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(
    ${PROJECT_NAME}
        STATIC
        ${_HEADERS_DIR}/config/MonitorWindowCfg.h
        ${_HEADERS_DIR}/config/ImageContainerCfg.h
        ${_HEADERS_DIR}/config/TextContainerCfg.h
        ${_HEADERS_DIR}/SDLLoader.h
        ${_HEADERS_DIR}/MonitorWindow.h
        ${_HEADERS_DIR}/Texture.h
        ${_HEADERS_DIR}/InputEvent.h
        ${_HEADERS_DIR}/Renderer.h
        ${_HEADERS_DIR}/containers/ImageContainer.h
        ${_HEADERS_DIR}/containers/TextContainer.h



        ${_SOURCE_DIR}/SDLLoader.c
        ${_SOURCE_DIR}/MonitorWindow.c
        ${_SOURCE_DIR}/Texture.c
        ${_SOURCE_DIR}/InputEvent.c
        ${_SOURCE_DIR}/Renderer.c
        ${_SOURCE_DIR}/containers/ImageContainer.c
        ${_SOURCE_DIR}/containers/TextContainer.c
        ${_SOURCE_DIR}/config/ImageContainerCfg.c
        ${_SOURCE_DIR}/config/TextContainerCfg.c
    
)

set_target_c_standard(${PROJECT_NAME} 11)
enable_target_c_warnings(${PROJECT_NAME})

if(UNIX)
    set(SDL2_image_name SDL2_image)
    set(SDL2_ttf_name SDL2_ttf)
    set(SDL2_mixer_name SDL2_mixer)
elseif(WIN32)
    set(SDL2_image_name SDL2_IMAGE)
    set(SDL2_ttf_name SDL2_TTF)
    set(SDL2_mixer_name SDL2_MIXER)
else()
    #macOS
    message("Error, unsupported OS")
endif()

find_package(SDL2 REQUIRED)
find_package(${SDL2_image_name} REQUIRED)
find_package(${SDL2_ttf_name} REQUIRED)
find_package(${SDL2_mixer_name} REQUIRED)

target_include_directories(
    ${PROJECT_NAME}
        PUBLIC
            ${_INCLUDE_DIR}
        PRIVATE
            ${SDL_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
            ${SDL2_TTF_INCLUDE_DIR}
            ${SDL2_MIXER_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        PUBLIC
            utils
        PRIVATE
            ${SDL2_LIBRARY}
            ${SDL2_IMAGE_LIBRARY}
            ${SDL2_TTF_LIBRARY}
            ${SDL2_MIXER_LIBRARY}
)
