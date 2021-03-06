cmake_minimum_required(VERSION 3.10)

project(TIMEATTACK
  VERSION 0.1.0
)

include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vendor/gf-box2d/modules")

find_package(gf REQUIRED)
find_package(box2d REQUIRED)

set(TIMEATTACK_DATADIR "${CMAKE_INSTALL_FULL_DATAROOTDIR}/games/timeattack")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/code/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(ENABLE_ASAN OFF)

if (ENABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address ")
endif (ENABLE_ASAN)

if(NOT MSVC)
  add_definitions(-Wall -Wextra -g -pedantic)
endif()

# app

add_executable(timeattack
  code/timeattack.cc
  code/bits/BackEntity.cc
  code/bits/CarChoiceEntity.cc
  code/bits/CarChoiceScene.cc
  code/bits/CarModel.cc
  code/bits/CarEntity.cc
  code/bits/CheckeredEntity.cc
  code/bits/ChronoEntity.cc
  code/bits/ChronoModel.cc
  code/bits/ContinueEntity.cc
  code/bits/CountdownEntity.cc
  code/bits/CountdownScene.cc
  code/bits/CreditEntity.cc
  code/bits/CreditScene.cc
  code/bits/FinishScene.cc
  code/bits/HelpEntity.cc
  code/bits/HelpScene.cc
  code/bits/IntroScene.cc
  code/bits/MenuEntity.cc
  code/bits/MenuScene.cc
  code/bits/MouseTracker.cc
  code/bits/MouseParticlesEntity.cc
  code/bits/PauseEntity.cc
  code/bits/PauseScene.cc
  code/bits/ProgressEntity.cc
  code/bits/RaceChoiceEntity.cc
  code/bits/RaceChoiceScene.cc
  code/bits/RaceScene.cc
  code/bits/ResultScene.cc
  code/bits/ResultEntity.cc
  code/bits/SkidmarkEntity.cc
  code/bits/StageEntity.cc
  code/bits/StageLimit.cc
  code/bits/StageScene.cc
  code/bits/TilesetInfo.cc
  code/bits/TimeAttack.cc
  code/bits/TimeAttackData.cc
  code/bits/TimeAttackState.cc
  code/bits/TimerEntity.cc
  code/bits/TimerModel.cc
  code/bits/TrafficEntity.cc

  vendor/gf-box2d/gfb2d/PhysicsModel.cc
  vendor/gf-box2d/gfb2d/PhysicsDebugger.cc
)

target_include_directories(timeattack
  PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/code
#     ${CMAKE_CURRENT_SOURCE_DIR}/code/bits
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/gf-box2d"
)

target_link_libraries(timeattack
  PRIVATE
    gf::graphics
    box2d::box2d
)

install(
  TARGETS timeattack
  RUNTIME DESTINATION bin
)

# data

install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/timeattack"
  DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/games"
)
