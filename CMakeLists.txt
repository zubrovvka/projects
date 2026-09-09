cmake_minimum_required(VERSION 3.16)
project(university-cpp-projects LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra)
endif()

option(BUILD_PALETTE_EXTRACTOR "Build the Qt palette-extractor app (requires Qt 5 or 6)" OFF)

add_subdirectory(algorithms-and-data-structures)

if(BUILD_PALETTE_EXTRACTOR)
    add_subdirectory(palette-extractor/src)
endif()
