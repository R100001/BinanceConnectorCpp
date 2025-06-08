add_library(umfutures
    account.cpp
    convert.cpp
    market_data.cpp
    portfolio_margin_endpoints.cpp
    trade.cpp
    websocket_connection.cpp
)

target_include_directories(umfutures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(umfutures PUBLIC api)