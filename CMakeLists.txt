cmake_minimum_required(VERSION 3.10)
project(MinecraftCLILauncher)

set(CMAKE_CXX_STANDARD 17)

add_executable(MinecraftCLILauncher
    main.cpp
    MinecraftLauncher.cpp
    MinecraftLauncher.h
    utils.cpp
    utils.h
)
