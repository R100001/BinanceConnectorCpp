
#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

//------------------------------------------------------------------------------------

#include <memory>
#include <string>
#include <vector>

//------------------------------------------------------------------------------------

class HTTPClient {
public:
    HTTPClient(std::string const &apiKey);
    ~HTTPClient();

    std::string get(std::string const &url, int32_t const timeout = 60, std::string const &proxy = "") const;
    std::string post(std::string const &url, int32_t const timeout = 60, std::string const &proxy = "") const;
    std::string put(std::string const &url, int32_t const timeout = 60, std::string const &proxy = "") const;
    std::string del(std::string const &url, int32_t const timeout = 60, std::string const &proxy = "") const;

private:
    class HTTPClientImpl;
    std::unique_ptr<HTTPClientImpl> _impl;
};

//------------------------------------------------------------------------------------

#endif // HTTP_CLIENT_HPP

//------------------------------------------------------------------------------------
