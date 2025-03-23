cmake_minimum_required(VERSION 3.25)
project(BinanceConnectorCpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(simdjson REQUIRED)

add_subdirectory(lib)
add_subdirectory(binance)

add_library(api STATIC
    api.cpp
)
target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(api PRIVATE openssllib utils)
target_link_libraries(api PUBLIC simdjson::simdjson)

add_executable(BinanceConnectorCpp main.cpp)

target_link_libraries(BinanceConnectorCpp PRIVATE openssllib curllib api utils derivativestrading umfutures simdjson::simdjson)