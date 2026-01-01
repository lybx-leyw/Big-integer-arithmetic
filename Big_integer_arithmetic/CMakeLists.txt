cmake_minimum_required(VERSION 3.10)

project(MyDarknet C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3") 
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zi /Od /DDEBUG") 
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /DNDEBUG")   
    endif()
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -DDEBUG")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG")
    endif()
endif()

file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "include/*.h")

message(STATUS "Found source files: ${SOURCES}")
message(STATUS "Found header files: ${HEADERS}")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory!")
endif()

add_executable(my_program ${SOURCES})

target_include_directories(my_program PRIVATE include)