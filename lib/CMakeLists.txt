add_library(openssllib STATIC
    authentication.cpp
)
target_link_libraries(openssllib PRIVATE OpenSSL::SSL OpenSSL::Crypto)

add_library(httplib STATIC
    HTTPClient.cpp
)
target_link_libraries(httplib PRIVATE Boost::system OpenSSL::SSL OpenSSL::Crypto)

add_library(utils STATIC
    utils.cpp
)
target_link_libraries(utils PUBLIC simdjson::simdjson)