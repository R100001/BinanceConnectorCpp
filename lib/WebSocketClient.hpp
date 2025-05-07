
//------------------------------------------------------------------------------------

#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <string>
#include <memory>
#include <chrono>
#include <functional>

//------------------------------------------------------------------------------------

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace ws = beast::websocket;
namespace ssl = net::ssl;

class WebSocketClient {
public:
    WebSocketClient(net::io_context &ioc, net::ssl::context &ctx, 
                    std::string_view host, std::string_view port,
                    std::chrono::seconds ping_interval,
                    std::chrono::milliseconds initial_reconnect_delay = std::chrono::milliseconds(1000),
                    std::chrono::milliseconds max_reconnect_delay = std::chrono::milliseconds(60000));
    virtual ~WebSocketClient();

    void connect(std::string_view target);
    void send(std::string_view message);
    void close();
    void run();

protected:
    virtual void on_message(std::string_view message) = 0;
    virtual void on_error(beast::error_code ec) = 0;

private:
    void do_connect();
    void do_read();
    void do_reconnect();
    void start_ping();

    void reset_stream(std::function<void()> on_complete = nullptr);

    net::io_context& _ioc;
    net::ssl::context& _ssl_ctx;
    tcp::resolver _resolver;
    std::unique_ptr<ws::stream<ssl::stream<beast::tcp_stream>>> _wss;
    std::string _host, _port, _endpoint;
    beast::flat_buffer _buffer;
    net::steady_timer _reconnect_timer;
    net::steady_timer _ping_timer;
    std::chrono::seconds _ping_interval;

    bool _target_changed = false;

    std::chrono::milliseconds _initial_reconnect_delay;
    std::chrono::milliseconds _max_reconnect_delay;
    std::chrono::milliseconds _current_reconnect_delay;
};

//------------------------------------------------------------------------------------

#endif // WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------
