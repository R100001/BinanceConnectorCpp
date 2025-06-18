
#include "http_client.hpp"

#include <stdexcept>
#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

struct Url {
    std::string_view protocol;
    std::string_view host;
    std::string_view port;
    std::string_view target;
};

static Url parse_url(std::string_view url, std::string_view target) {
    size_t const protocol_end = url.find("://");
    if (protocol_end == std::string_view::npos) {
        throw std::invalid_argument("Invalid URL: no protocol specified");
    }
    std::string_view protocol = url.substr(0, protocol_end);
    size_t const host_start = protocol_end + 3;
    std::string_view host_port = url.substr(host_start);
    size_t const port_sep = host_port.find(':');
    std::string_view host;
    std::string_view port;
    if (port_sep != std::string_view::npos) {
        host = host_port.substr(0, port_sep);
        port = host_port.substr(port_sep + 1);
    } else {
        host = host_port;
        port = (protocol == "https") ? "443" : "80";
    }
    return {protocol, host, port, target};
}

class HTTPClient::HTTPClientImpl {
public:
    HTTPClientImpl(std::string_view const apiKey) {
        _default_headers.set(boost::beast::http::field::content_type, 
                            "application/x-www-form-urlencoded");
        _default_headers.set(boost::beast::http::field::user_agent, 
                            "binance-futures-connector-cpp/1.0");
        _default_headers.insert("X-MBX-APIKEY", apiKey);
    }

    std::string performRequest(std::string_view const url, std::string_view const endpoint, std::string_view const method, 
                               int32_t const timeout = 60, std::string_view const proxy = "") {

        Url const parsed_url = parse_url(url, endpoint);
        std::cout << "Parsed URL: " << parsed_url.protocol << " "
                  << parsed_url.host << " " << parsed_url.port << " " << parsed_url.target << "\n";

        boost::asio::io_context ioc;
        boost::asio::ip::tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(parsed_url.host, parsed_url.port);

        boost::beast::http::request<boost::beast::http::string_body> req;
        if (method == "GET") {
            req.method(boost::beast::http::verb::get);
        } else if (method == "POST") {
            req.method(boost::beast::http::verb::post);
        } else if (method == "PUT") {
            req.method(boost::beast::http::verb::put);
        } else if (method == "DELETE") {
            req.method(boost::beast::http::verb::delete_);
        } else {
            throw std::runtime_error("Unsupported HTTP method: " + std::string(method));
        }
        req.target(parsed_url.target);
        req.version(11);
        req.set(boost::beast::http::field::host, parsed_url.host);

        for (const auto& header : _default_headers) {
            req.set(header.name_string(), header.value());
        }

        if (parsed_url.protocol == "https") {
            boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv12_client);
            ctx.set_verify_mode(boost::asio::ssl::verify_none);

            boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc, ctx);
            boost::beast::get_lowest_layer(stream).connect(results);
            stream.handshake(boost::asio::ssl::stream_base::client);

            boost::beast::http::write(stream, req);
            boost::beast::flat_buffer buffer;
            boost::beast::http::response<boost::beast::http::string_body> res;
            boost::beast::http::read(stream, buffer, res);

            boost::beast::error_code ec;
            stream.shutdown(ec);
            return res.body();
        } else {
            boost::beast::tcp_stream stream(ioc);
            stream.connect(results);

            boost::beast::http::write(stream, req);
            boost::beast::flat_buffer buffer;
            boost::beast::http::response<boost::beast::http::string_body> res;
            boost::beast::http::read(stream, buffer, res);

            stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);
            return res.body();
        }
    }

private:
    boost::beast::http::fields _default_headers;
};

HTTPClient::HTTPClient(std::string_view hmac_api_key) 
    : _impl(std::make_unique<HTTPClientImpl>(hmac_api_key)) {}

HTTPClient::~HTTPClient() = default;

std::string HTTPClient::get(std::string_view const endpoint, int32_t const timeout, 
                           std::string_view const proxies) const {
    return _impl->performRequest(HTTPClient::REST_API_URL, endpoint, "GET", timeout, proxies);
}

std::string HTTPClient::post(std::string_view const endpoint, int32_t const timeout, 
                            std::string_view const proxies) const {
    return _impl->performRequest(HTTPClient::REST_API_URL, endpoint, "POST", timeout, proxies);
}

std::string HTTPClient::put(std::string_view const endpoint, int32_t const timeout, 
                           std::string_view const proxies) const {
    return _impl->performRequest(HTTPClient::REST_API_URL, endpoint, "PUT", timeout, proxies);
}

std::string HTTPClient::del(std::string_view const endpoint, int32_t const timeout, 
                           std::string_view const proxies) const {
    return _impl->performRequest(HTTPClient::REST_API_URL, endpoint, "DELETE", timeout, proxies);
}