
#include "WebSocketClient.hpp"

//---------------------------------------------------------------------------------------

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace ws = beast::websocket;

//---------------------------------------------------------------------------------------

WebSocketClient::WebSocketClient(net::io_context& ioc,
                                 std::string_view host, std::string_view port,
                                 std::chrono::seconds ping_interval,
                                 std::chrono::milliseconds initial_reconnect_delay,
                                 std::chrono::milliseconds max_reconnect_delay)
    : _ioc(ioc),
        _resolver(ioc),
        _ws(ioc),
        _host(host),
        _port(port),
        _reconnect_timer(ioc),
        _ping_timer(ioc),
        _ping_interval(ping_interval),
        _target_changed(false),
        _initial_reconnect_delay(initial_reconnect_delay),
        _max_reconnect_delay(max_reconnect_delay),
        _current_reconnect_delay(initial_reconnect_delay)
        {}

//---------------------------------------------------------------------------------------

WebSocketClient::~WebSocketClient() {
    close();
}

//---------------------------------------------------------------------------------------

void WebSocketClient::connect(std::string_view target) {
    _endpoint = target;
    if (_target_changed) _ws.next_layer().close();
    do_connect();
    _target_changed = true;
}

//---------------------------------------------------------------------------------------

void WebSocketClient::send(std::string_view message) {
    _ws.async_write(net::buffer(message),
        [this](beast::error_code ec, std::size_t) {
            if (ec) {
                on_error(ec);
            }
        });
}

//---------------------------------------------------------------------------------------

void WebSocketClient::close() {
    if (_ws.is_open()) {
        _ws.async_close(ws::close_code::normal,
            [this](beast::error_code ec) {
                if (ec) {
                    on_error(ec);
                }
            });
    }
}

//---------------------------------------------------------------------------------------

void WebSocketClient::run() {
    _ioc.run();
}

//---------------------------------------------------------------------------------------

void WebSocketClient::do_connect() {
    _resolver.async_resolve(_host, _port,
        [this](beast::error_code ec, tcp::resolver::results_type results) {
            if (ec) {
                on_error(ec);
                do_reconnect();
                return;
            }
            net::async_connect(_ws.next_layer(), results,
                [this](beast::error_code ec, const tcp::endpoint&) {
                    if (ec) {
                        on_error(ec);
                        do_reconnect();
                        return;
                    }
                    _ws.async_handshake(_host, _endpoint,
                        [this](beast::error_code ec) {
                            if (ec) {
                                on_error(ec);
                                do_reconnect();
                                return;
                            }
                            _current_reconnect_delay = _initial_reconnect_delay;
                            start_ping();
                            do_read();
                        });
                });
        });
}

//---------------------------------------------------------------------------------------

void WebSocketClient::do_read() {
    _ws.async_read(_buffer,
        [this](beast::error_code ec, std::size_t ) {
            if (!ec) {
                std::string message = beast::buffers_to_string(_buffer.data());
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

void WebSocketClient::do_reconnect() {
    _ws.next_layer().close();

    _current_reconnect_delay = std::min(_current_reconnect_delay * 2, _max_reconnect_delay);
    _reconnect_timer.expires_after(_current_reconnect_delay);
    _reconnect_timer.async_wait([this](beast::error_code ec) {
        if (!ec) {
            do_connect();
        }
    });
}

//---------------------------------------------------------------------------------------

void WebSocketClient::start_ping() {
    _ping_timer.expires_after(_ping_interval);
    _ping_timer.async_wait([this](beast::error_code ec) {
        if (ec) {
            return;
        }
        _ws.async_ping({},
            [this](beast::error_code ec) {
                if (ec) {
                    on_error(ec);
                }
                start_ping();
            });
    });
}

//---------------------------------------------------------------------------------------
