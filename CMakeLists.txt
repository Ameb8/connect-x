cmake_minimum_required(VERSION 3.13)

project(engine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist)

# Source and header paths
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/src
)

file(GLOB_RECURSE ENGINE_SOURCES
        engine/src/*.cpp
)

# Create the executable target
add_executable(game_module ${ENGINE_SOURCES})

# Set C++ standard
set_target_properties(game_module PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
)

# Detect Emscripten and apply WASM-specific flags
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    message(STATUS "Building with Emscripten (WebAssembly)")

    set_target_properties(game_module PROPERTIES
            OUTPUT_NAME "game_module"
            SUFFIX ".js"
    )

    target_compile_options(game_module PRIVATE
            -s WASM=1
            -s MODULARIZE=1
            -s EXPORT_NAME="createModule"
            -s ALLOW_MEMORY_GROWTH=1
            -s ENVIRONMENT=web
            -O2
    )
else()
    message(STATUS "Building native")
    set_target_properties(game_module PROPERTIES
            OUTPUT_NAME "game_module_native"
    )
    target_compile_options(game_module PRIVATE
            -Wall
            -Wextra
            -O3
    )
endif()
