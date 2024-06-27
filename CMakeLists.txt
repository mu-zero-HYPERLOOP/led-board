######################################################################
# @author      : karl (karlsasssie@gmail.com)
# @file        : CMakeLists
# @created     : Wednesday June 26, 2024 15:39:05 CEST
######################################################################

cmake_minimum_required(VERSION 3.5)
project(led-board CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  mock/can.cpp
  mock/print.cpp
  mock/led_board.cpp
  src/canzero/canzero.cpp
  src/handle_heartbeat.cpp
  src/fsm/fsm.cpp
  src/fsm/states/startup.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src/ mock/)

