cmake_minimum_required(VERSION 4.2)
project(FLTracker)

set(CMAKE_CXX_STANDARD 20)

add_executable(FLTracker main.cpp libs/miniaudio.c
        Channel.cpp
        Channel.h
        utils/utils.h)

target_include_directories(FLTracker PRIVATE libs)

# Windows necesita estas libs para audio
if(WIN32)
    target_link_libraries(FLTracker PRIVATE ole32 uuid winmm)
endif()

# Copia la carpeta samples junto al ejecutable
file(COPY samples DESTINATION ${CMAKE_BINARY_DIR})