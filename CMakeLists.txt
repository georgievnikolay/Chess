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
        
        ${_INCLUDE_DIR}/game/proxies/GameProxy.h
        ${_INCLUDE_DIR}/game/proxies/GameBoardProxy.h
        ${_INCLUDE_DIR}/game/proxies/PiecePromotionPanelProxy.h
        ${_INCLUDE_DIR}/game/config/GameCfg.h
        ${_INCLUDE_DIR}/game/config/GameLogicCfg.h
        ${_INCLUDE_DIR}/game/config/GameButtonCfg.h
        ${_INCLUDE_DIR}/game/config/GameStatePanelCfg.h
        ${_INCLUDE_DIR}/game/config/PieceHandlerCfg.h
        ${_INCLUDE_DIR}/game/config/PiecePromotionPanelCfg.h
        ${_INCLUDE_DIR}/game/config/PiecePromotionButtonCfg.h
        ${_INCLUDE_DIR}/game/defines/ChessDefines.h
        ${_INCLUDE_DIR}/game/defines/GameDefines.h
        ${_INCLUDE_DIR}/game/defines/GameLogicDefines.h
        ${_INCLUDE_DIR}/game/defines/ChessStructs.h
        ${_INCLUDE_DIR}/game/entities/PiecePromotionPanel.h
        ${_INCLUDE_DIR}/game/entities/GameStatePanel.h
        ${_INCLUDE_DIR}/game/entities/board/GameBoard.h
        ${_INCLUDE_DIR}/game/entities/board/MoveSelector.h
        ${_INCLUDE_DIR}/game/entities/buttons/PiecePromotionButton.h
        ${_INCLUDE_DIR}/game/entities/buttons/GameButton.h
        ${_INCLUDE_DIR}/game/entities/pieces/PieceHandler.h
        ${_INCLUDE_DIR}/game/entities/pieces/PieceHandlerHelper.h
        ${_INCLUDE_DIR}/game/entities/pieces/PieceHandlerPopulator.h
        ${_INCLUDE_DIR}/game/entities/pieces/ChessPieceResolver.h
        ${_INCLUDE_DIR}/game/entities/pieces/types/ChessPiece.h
        ${_INCLUDE_DIR}/game/entities/pieces/types/Rook.h
        ${_INCLUDE_DIR}/game/entities/pieces/types/Pawn.h
        ${_INCLUDE_DIR}/game/entities/pieces/types/Bishop.h
        ${_INCLUDE_DIR}/game/entities/pieces/types/Queen.h
        ${_INCLUDE_DIR}/game/entities/pieces/types/King.h
        ${_INCLUDE_DIR}/game/entities/pieces/types/Knight.h
        ${_INCLUDE_DIR}/game/logic/GameLogic.h
        ${_INCLUDE_DIR}/game/utils/BoardPos.h
        ${_INCLUDE_DIR}/game/utils/BoardUtils.h
        ${_INCLUDE_DIR}/game/utils/BoardMoveHelper.h
        ${_INCLUDE_DIR}/game/utils/SaveFile.h
        ${_INCLUDE_DIR}/game/Game.h


        ${_SOURCE_DIR}/main.c
        ${_SOURCE_DIR}/engine/Engine.c
        ${_SOURCE_DIR}/engine/EngineConfigLoader.c
        
        ${_SOURCE_DIR}/game/entities/PiecePromotionPanel.c
        ${_SOURCE_DIR}/game/entities/GameStatePanel.c
        ${_SOURCE_DIR}/game/entities/board/GameBoard.c
        ${_SOURCE_DIR}/game/entities/board/MoveSelector.c
        ${_SOURCE_DIR}/game/entities/buttons/PiecePromotionButton.c
        ${_SOURCE_DIR}/game/entities/buttons/GameButton.c
        ${_SOURCE_DIR}/game/entities/pieces/PieceHandler.c
        ${_SOURCE_DIR}/game/entities/pieces/PieceHandlerHelper.c
        ${_SOURCE_DIR}/game/entities/pieces/PieceHandlerPopulator.c
        ${_SOURCE_DIR}/game/entities/pieces/ChessPieceResolver.c
        ${_SOURCE_DIR}/game/entities/pieces/types/ChessPiece.c
        ${_SOURCE_DIR}/game/entities/pieces/types/Rook.c
        ${_SOURCE_DIR}/game/entities/pieces/types/Pawn.c
        ${_SOURCE_DIR}/game/entities/pieces/types/Bishop.c
        ${_SOURCE_DIR}/game/entities/pieces/types/Queen.c
        ${_SOURCE_DIR}/game/entities/pieces/types/King.c
        ${_SOURCE_DIR}/game/entities/pieces/types/Knight.c
        ${_SOURCE_DIR}/game/logic/GameLogic.c
        ${_SOURCE_DIR}/game/utils/BoardPos.c
        ${_SOURCE_DIR}/game/utils/BoardUtils.c
        ${_SOURCE_DIR}/game/utils/BoardMoveHelper.c
        ${_SOURCE_DIR}/game/utils/SaveFile.c
        ${_SOURCE_DIR}/game/Game.c

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