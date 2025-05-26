
#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

//------------------------------------------------------------------------------------

#include <memory>
#include <string_view>

//------------------------------------------------------------------------------------

class HTTPClient {

private: // Constants

    static constexpr std::string_view REST_API_URL = "https://fapi.binance.com";
    static constexpr std::string_view REST_API_TESTNET_URL = "https://testnet.binancefuture.com";

public:
    HTTPClient(std::string_view api_key);
    ~HTTPClient();

    std::string get(std::string_view const endpoint, int32_t const timeout = 60, std::string_view const proxy = "") const;
    std::string post(std::string_view const endpoint, int32_t const timeout = 60, std::string_view const proxy = "") const;
    std::string put(std::string_view const endpoint, int32_t const timeout = 60, std::string_view const proxy = "") const;
    std::string del(std::string_view const endpoint, int32_t const timeout = 60, std::string_view const proxy = "") const;

private:
    class HTTPClientImpl;
    std::unique_ptr<HTTPClientImpl> _impl;
};

//------------------------------------------------------------------------------------

#endif // HTTP_CLIENT_HPP

//------------------------------------------------------------------------------------
