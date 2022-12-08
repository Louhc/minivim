cmake_minimum_required(VERSION 3.16)
project(minivim VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SRC_LIST src/minivim.cpp src/basic.cpp src/operations.cpp src/normal_mode.cpp src/insert_mode.cpp src/command_mode.cpp)

<<<<<<< HEAD
set(EXECUTABLE_OUTPUT_PATH ../bin)
=======
set(EXECUTABLE_OUTPUT_PATH bin)
>>>>>>> 067a41fc6e69b6a7351cc95cb86443b4eb9e36bf

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})
