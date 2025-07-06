cmake_minimum_required(VERSION 3.10)
project(MinecraftCLILauncher)

set(CMAKE_CXX_STANDARD 17)

# find_package(CURL REQUIRED)

add_executable(MinecraftCLILauncher
    main.cpp
    MinecraftLauncher.cpp
    MinecraftLauncher.h
    utils.cpp
    utils.h
)

# target_link_libraries(MinecraftCLILauncher PRIVATE CURL::libcurl)