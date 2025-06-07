cmake_minimum_required(VERSION 3.25)
project(BinanceConnectorCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(EXISTS ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
    include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
endif()

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(simdjson REQUIRED)

add_subdirectory(binance)
add_subdirectory(Catch)

add_executable(BinanceConnectorCpp main.cpp)

target_link_libraries(BinanceConnectorCpp PRIVATE
    openssllib
    httplib
    websocketlib
    api
    utils
    umfutures
    simdjson::simdjson
)