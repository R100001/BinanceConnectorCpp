cmake_minimum_required(VERSION 3.25)
project(BinanceConnectorCpp LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include Conan toolchain
if(EXISTS ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
    include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
endif()

# Find dependencies
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(simdjson REQUIRED)

# Subdirectories
add_subdirectory(lib)
add_subdirectory(binance)

# API library
add_library(api STATIC
    api.cpp
)
target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(api PRIVATE openssllib utils)
target_link_libraries(api PUBLIC simdjson::simdjson)

# Main executable
add_executable(BinanceConnectorCpp main.cpp)

# Updated to use httplib instead of curllib
target_link_libraries(BinanceConnectorCpp PRIVATE
    openssllib
    httplib
    websocketlib
    api
    utils
    umfutures
    simdjson::simdjson
)