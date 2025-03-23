
#include "HTTPClient.hpp"
#include <curl/curl.h>
#include <stdexcept>

//------------------------------------------------------------------------------------

class HTTPClient::HTTPClientImpl {

public: // Constructor, Destructor

    HTTPClientImpl(std::string const &apiKey);
    ~HTTPClientImpl();

public: // Public methods

    std::string performRequest(std::string const &url, std::string const &method, std::string const &proxy = "", int32_t timeout = 60);

private: // Private methods

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

private: // Private variables

    CURL* _curl = nullptr;
    struct curl_slist* _default_headers = nullptr;

};

//------------------------------------------------------------------------------------

HTTPClient::HTTPClientImpl::HTTPClientImpl(std::string const &apiKey) {
    _curl = curl_easy_init();
    if (!_curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    _default_headers = nullptr;
    _default_headers = curl_slist_append(_default_headers, "Content-Type: application/x-www-form-urlencoded");
    _default_headers = curl_slist_append(_default_headers, "User-Agent: binance-futures-connector-cpp/1.0");
    _default_headers = curl_slist_append(_default_headers, ("X-MBX-APIKEY: " + apiKey).c_str());
}

//------------------------------------------------------------------------------------

HTTPClient::HTTPClientImpl::~HTTPClientImpl() {
    if (_curl) {
        curl_easy_cleanup(_curl);
    }
    if (_default_headers) {
        curl_slist_free_all(_default_headers);
    }
}

//------------------------------------------------------------------------------------

std::string HTTPClient::HTTPClientImpl::performRequest(std::string const &url, std::string const &method, std::string const &proxy, int32_t timeout) {
    std::string response;

    curl_easy_reset(_curl);
    curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &response);

    if (!proxy.empty()) {
        curl_easy_setopt(_curl, CURLOPT_PROXY, proxy.c_str());
    }
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT, static_cast<long>(timeout));

    if (method == "POST") {
        curl_easy_setopt(_curl, CURLOPT_POST, 1L);
    } 
    else if (method == "PUT") {
        curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, "PUT");
    }
    else if (method == "DELETE") {
        curl_easy_setopt(_curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    }
    else if (method != "GET") {
        throw std::runtime_error("Unsupported HTTP method: " + method);
    }

    if (_default_headers) {
        curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _default_headers);
    }

    CURLcode res = curl_easy_perform(_curl);
    if (res != CURLE_OK) {
        throw std::runtime_error(curl_easy_strerror(res));
    }

    return response;
}

//------------------------------------------------------------------------------------

size_t HTTPClient::HTTPClientImpl::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

//------------------------------------------------------------------------------------

HTTPClient::HTTPClient(std::string const &apiKey) : _impl(std::make_unique<HTTPClientImpl>(apiKey)) {}
HTTPClient::~HTTPClient() = default;

//------------------------------------------------------------------------------------

std::string HTTPClient::get(std::string const &url, int32_t const timeout, std::string const &proxies) const {
    return _impl->performRequest(url, "GET", proxies, timeout);
}

//------------------------------------------------------------------------------------

std::string HTTPClient::post(std::string const &url, int32_t const timeout, std::string const &proxies) const {
    return _impl->performRequest(url, "POST", proxies, timeout);
}

//------------------------------------------------------------------------------------

std::string HTTPClient::put(std::string const &url, int32_t const timeout, std::string const &proxies) const {
    return _impl->performRequest(url, "PUT", proxies, timeout);
}

//------------------------------------------------------------------------------------

std::string HTTPClient::del(std::string const &url, int32_t const timeout, std::string const &proxies) const {
    return _impl->performRequest(url, "DELETE", proxies, timeout);
}

//------------------------------------------------------------------------------------
