add_library(openssllib STATIC
    authentication.cpp
)
target_link_libraries(openssllib PRIVATE OpenSSL::SSL OpenSSL::Crypto)

add_library(curllib STATIC
    HTTPClient.cpp
)
target_link_libraries(curllib PRIVATE CURL::libcurl)

add_library(utils STATIC
    utils.cpp
)
target_link_libraries(utils PUBLIC simdjson::simdjson)