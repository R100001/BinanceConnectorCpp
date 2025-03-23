
add_library(umfutures market_data.cpp convert.cpp trade.cpp account.cpp)

target_include_directories(umfutures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(umfutures PRIVATE derivativestrading)