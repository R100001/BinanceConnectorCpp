
//---------------------------------------------------------------------------------------

#include "WebSocketClient.hpp"

//---------------------------------------------------------------------------------------

namespace net    = boost::asio;
using tcp        = net::ip::tcp;
namespace beast  = boost::beast;
namespace ws     = beast::websocket;

//---------------------------------------------------------------------------------------

WebSocketClient::WebSocketClient(net::io_context &ioc,
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
      _target_changed(false),
      _initial_reconnect_delay(initial_reconnect_delay),
      _max_reconnect_delay(max_reconnect_delay),
      _current_reconnect_delay(initial_reconnect_delay)
{
    _wss = std::make_unique<ws::stream<ssl::stream<beast::tcp_stream>>>(
        net::make_strand(_ioc), _ssl_ctx);
}

//---------------------------------------------------------------------------------------

WebSocketClient::~WebSocketClient() {
    close();
}

//---------------------------------------------------------------------------------------

void WebSocketClient::connect(std::string_view target) {
    _endpoint = target;
    if (_target_changed) {
        reset_stream();
    }
    do_connect();
    _target_changed = true;
}

//---------------------------------------------------------------------------------------

void WebSocketClient::send(std::string_view message) {
    _wss->async_write(net::buffer(message),
        [this](beast::error_code ec, std::size_t) {
            if (ec) on_error(ec);
        });
}

//---------------------------------------------------------------------------------------

void WebSocketClient::close() {
    if (_wss && _wss->is_open()) {
        _wss->async_close(ws::close_code::normal,
            [this](beast::error_code ec) {
                if (ec) on_error(ec);
            });
    }
}

//---------------------------------------------------------------------------------------

void WebSocketClient::run() {
    _ioc.run();
}

//---------------------------------------------------------------------------------------

void WebSocketClient::do_connect() {

    _resolver.async_resolve(
        _host,
        _port,
        tcp::resolver::basic_resolver::numeric_service,
        [this](beast::error_code ec, tcp::resolver::results_type results) {
            if (ec) {
                on_error(ec);
                reset_stream([this]() { do_reconnect(); });
                return;
            }
            _wss->next_layer().next_layer().async_connect(
                results,
                [this](beast::error_code ec, tcp::endpoint ep) {
                    if (ec) {
                        on_error(ec);
                        reset_stream([this]() { do_reconnect(); });
                        return;
                    }
                    _wss->next_layer().handshake(ssl::stream_base::client, ec);
                    if (ec) {
                        on_error(ec);
                        reset_stream([this]() { do_reconnect(); });
                        return;
                    }
                    _wss->async_handshake(_host, _endpoint,
                        [this](beast::error_code ec) {
                            if (ec) {
                                on_error(ec);
                                reset_stream([this]() { do_reconnect(); });
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
    _wss->async_read(_buffer,
        [this](beast::error_code ec, std::size_t) {
            if (!ec) {
                std::string message = beast::buffers_to_string(_buffer.data());
                _buffer.clear();
                on_message(message);
                do_read();
            } else {
                on_error(ec);
                reset_stream([this]() { do_reconnect(); });
            }
        });
}

//---------------------------------------------------------------------------------------

void WebSocketClient::do_reconnect() {

    _current_reconnect_delay = std::min(_current_reconnect_delay * 2, _max_reconnect_delay);
    _reconnect_timer.expires_after(_current_reconnect_delay);
    _reconnect_timer.async_wait([this](beast::error_code ec) {
        if (!ec) {
            reset_stream([this]() { do_connect(); });
        }
    });
}

//---------------------------------------------------------------------------------------

void WebSocketClient::start_ping() {
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

void WebSocketClient::reset_stream(std::function<void()> on_complete) {
    if (_wss && _wss->is_open()) {
        _wss->async_close(ws::close_code::normal,
            [this, on_complete](beast::error_code ec) {
                if (ec) on_error(ec);
                _wss = std::make_unique<ws::stream<ssl::stream<beast::tcp_stream>>>(
                    net::make_strand(_ioc), _ssl_ctx);
                if (on_complete) on_complete();
            });
    } else {
        _wss = std::make_unique<ws::stream<ssl::stream<beast::tcp_stream>>>(
            net::make_strand(_ioc), _ssl_ctx);
        if (on_complete) on_complete();
    }
}