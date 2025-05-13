
//---------------------------------------------------------------------------------------

#include "WebSocketClient.hpp"

#include <iostream>

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>

//------------------------------------------------------------------------------------

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace ws = beast::websocket;
namespace ssl = net::ssl;

//------------------------------------------------------------------------------------

class WebSocketClientImpl {

private: // Constants
    constexpr static uint64_t default_initial_reconnect_delay = 1000;
    constexpr static uint64_t default_max_reconnect_delay = 60000;

public:
    WebSocketClientImpl(net::io_context &ioc, net::ssl::context &ctx, 
                    std::string_view host, std::string_view port = "443",
                    std::chrono::seconds ping_interval = std::chrono::seconds(0),
                    std::chrono::milliseconds initial_reconnect_delay = std::chrono::milliseconds(default_initial_reconnect_delay),
                    std::chrono::milliseconds max_reconnect_delay = std::chrono::milliseconds(default_max_reconnect_delay));
    ~WebSocketClientImpl();

    WebSocketClientImpl(const WebSocketClientImpl&) = delete;
    WebSocketClientImpl(WebSocketClientImpl&&) = delete;
    WebSocketClientImpl& operator=(const WebSocketClientImpl&) = delete;
    WebSocketClientImpl& operator=(WebSocketClientImpl&&) = delete;

    void connect(std::string_view target);
    void send(std::string_view message);
    void close();
    void run();

    void on_message(std::string_view message);
    void on_error(beast::error_code ec);

private:
    void do_connect();
    void do_read();
    void do_reconnect();
    void start_ping();

    net::io_context& _ioc;
    net::ssl::context& _ssl_ctx;
    tcp::resolver _resolver;
    std::unique_ptr<ws::stream<ssl::stream<beast::tcp_stream>>> _wss;
    std::string _host, _port, _endpoint;
    beast::flat_buffer _buffer;
    net::steady_timer _reconnect_timer;
    net::steady_timer _ping_timer;
    std::chrono::seconds _ping_interval;

    std::chrono::milliseconds _initial_reconnect_delay;
    std::chrono::milliseconds _max_reconnect_delay;
    std::chrono::milliseconds _current_reconnect_delay;
}; // class WebSocketClientImpl

//---------------------------------------------------------------------------------------

namespace net    = boost::asio;
using tcp        = net::ip::tcp;
namespace beast  = boost::beast;
namespace ws     = beast::websocket;

//---------------------------------------------------------------------------------------

WebSocketClientImpl::WebSocketClientImpl(net::io_context &ioc,
                                 net::ssl::context &ctx,
                                 std::string_view host,
                                 std::string_view port,
                                 std::chrono::seconds ping_interval,
                                 std::chrono::milliseconds initial_reconnect_delay,
                                 std::chrono::milliseconds max_reconnect_delay)
    : _ioc(ioc),
      _ssl_ctx(ctx),
      _resolver(ioc),
      _host(host),
      _port(port),
      _reconnect_timer(ioc),
      _ping_timer(ioc),
      _ping_interval(ping_interval),
      _initial_reconnect_delay(initial_reconnect_delay),
      _max_reconnect_delay(max_reconnect_delay),
      _current_reconnect_delay(initial_reconnect_delay)
{
    _wss = std::make_unique<ws::stream<ssl::stream<beast::tcp_stream>>>(
        net::make_strand(_ioc), _ssl_ctx);
}

//---------------------------------------------------------------------------------------

WebSocketClientImpl::~WebSocketClientImpl() {
    close();
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::connect(std::string_view target) {
    do_connect();
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::send(std::string_view message) {
    _wss->async_write(net::buffer(message),
        [this](beast::error_code ec, std::size_t) {
            if (ec) on_error(ec);
        });
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::close() {
    if (_wss && _wss->is_open()) {
        _wss->async_close(ws::close_code::normal,
            [this](beast::error_code ec) {
                if (ec) on_error(ec);
            });
    }
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::run() {
    _ioc.run();
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::on_message(std::string_view message) {
    std::cout << "Received message:\n" << message << std::endl;
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::on_error(beast::error_code ec) {
    std::cerr << "Error:\n" << ec.message() << std::endl;
    if (ec == ws::error::closed) {
        std::cout << "Connection closed." << std::endl;
    } else {
        std::cerr << "Unexpected error: " << ec.message() << std::endl;
    }
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::do_connect() {

    _wss->control_callback(
        [this](ws::frame_type type, beast::string_view payload) {
            if (type == ws::frame_type::ping) {
                ws::ping_data const ping_payload(payload.data(), payload.size());
                _wss->async_pong(ping_payload, [this](beast::error_code ec) { if (ec) on_error(ec); });
            }
        });

    _resolver.async_resolve(
        _host,
        _port,
        tcp::resolver::basic_resolver::numeric_service,
        [this](beast::error_code ec, tcp::resolver::results_type results) {
            if (ec) {
                on_error(ec);
                do_reconnect();
                return;
            }
            _wss->next_layer().next_layer().async_connect(results,
                [this](beast::error_code ec, tcp::endpoint ep) {
                    if (ec) {
                        on_error(ec);
                        do_reconnect();
                        return;
                    }
                    _wss->next_layer().handshake(ssl::stream_base::client, ec);
                    if (ec) {
                        on_error(ec);
                        do_reconnect();
                        return;
                    }
                    _wss->async_handshake(_host, _endpoint,
                        [this](beast::error_code ec) {
                            if (ec) {
                                on_error(ec);
                                do_reconnect();
                                return;
                            }
                            _current_reconnect_delay = _initial_reconnect_delay;
                            if(_ping_interval > std::chrono::seconds(0)) start_ping();
                            do_read();
                        });
                });
        });
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::do_read() {
    _wss->async_read(_buffer,
        [this](beast::error_code ec, std::size_t) {
            if (!ec) {
                std::string const message = beast::buffers_to_string(_buffer.data());
                _buffer.clear();
                on_message(message);
                do_read();
            } else {
                on_error(ec);
                do_reconnect();
            }
        });
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::do_reconnect() {
    _current_reconnect_delay = std::min(_current_reconnect_delay * 2, _max_reconnect_delay);
    _reconnect_timer.expires_after(_current_reconnect_delay);
    _reconnect_timer.async_wait([this](beast::error_code ec) { if (!ec) do_connect(); });
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::start_ping() {
    _ping_timer.expires_after(_ping_interval);
    _ping_timer.async_wait([this](beast::error_code ec) {
        if (ec) return;
        _wss->async_ping({},
            [this](beast::error_code ec) {
                if (ec) on_error(ec);
                start_ping();
            });
    });
}

//---------------------------------------------------------------------------------------

