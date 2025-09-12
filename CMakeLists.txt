cmake_minimum_required(VERSION 3.15)
project(connect_x)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(connect_x ${SOURCES}
        src/main.cpp
        src/npc/Difficulty.h
        src/npc/Difficulty.cpp
        src/player/LocalPlayer.cpp
        src/player/LocalPlayer.h
        src/player/textStyle.h
        include/connect-x/participants.h
)
        # src/game/NPCPlayer.cpp
        # src/game/NPCPlayer.h)

target_include_directories(connect_x PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

# Add warning flags only for GNU and Clang compilers
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(connect_x PRIVATE -Wall -Wextra)
endif()
