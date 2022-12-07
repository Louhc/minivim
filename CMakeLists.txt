cmake_minimum_required(VERSION 3.16)
project(minivim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SRC_LIST minivim.cpp minivim.h basic.cpp operations.cpp normal_mode.cpp insert_mode.cpp command_mode.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})
