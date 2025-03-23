
add_library(derivativestrading derivatives_trading.cpp)

target_include_directories(derivativestrading PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(derivativestrading PUBLIC api)

add_subdirectory(um_futures)