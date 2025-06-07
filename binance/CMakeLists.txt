add_subdirectory(lib)
add_subdirectory(derivatives_trading)

add_library(api STATIC
    api.cpp
)

target_include_directories(api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(api PRIVATE openssllib utils Boost::system OpenSSL::SSL OpenSSL::Crypto websocketlib)
target_link_libraries(api PUBLIC simdjson::simdjson)