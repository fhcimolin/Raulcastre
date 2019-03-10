#------------------------------------------------------------------------------
# Setup project
#------------------------------------------------------------------------------
# Project name and build-system
cmake_minimum_required(VERSION 3.11)
project(raulcastre CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add warning flags for g++
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Werror")
endif()

# Show profile and compilation flags
message("Profile: ${CMAKE_BUILD_TYPE}")
message("         Default Flags  ->  ${CMAKE_CXX_FLAGS}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("         Debug flags    -> ${CMAKE_CXX_FLAGS_DEBUG}")
else()
    message("         Release flags  -> ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

#------------------------------------------------------------------------------
# External Libraries
#------------------------------------------------------------------------------
# SDL 1.2
find_package(SDL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if(SDL_FOUND)
    message(STATUS "SDL found!")
    message("       Include  -> \"${SDL_INCLUDE_DIR}\"")
    message("       Libs     -> \"${SDL_LIBRARY}\"")
else()
    message(FATAL_ERROR "Failed to find SDL. Do you have and SDLFind.cmake?")
endif()

#------------------------------------------------------------------------------
# Local sources
#------------------------------------------------------------------------------
add_subdirectory(src)
