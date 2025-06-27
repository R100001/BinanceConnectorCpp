add_subdirectory(lib)
add_subdirectory(derivatives_trading)

add_library(api STATIC
    api.cpp
)

target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} lib derivatives_trading um_futures)
target_link_libraries(api PRIVATE openssllib Boost::system OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(api PUBLIC simdjson::simdjson utils umfutures httplib websocketlib)