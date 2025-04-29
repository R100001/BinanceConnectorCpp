
//------------------------------------------------------------------------------------

#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <chrono>

//------------------------------------------------------------------------------------

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace ws = beast::websocket;

class WebSocketClient {
public:
    WebSocketClient(net::io_context& ioc, const std::string& host, const std::string& port);
    virtual ~WebSocketClient();

    void connect();
    void send(const std::string& message);
    void close();
    void run();

protected:
    // Pure virtual functions for derived classes to implement
    // on_message: Process incoming WebSocket messages (e.g., parse JSON)
    virtual void on_message(const std::string& message) = 0;
    // on_error: Handle errors (e.g., connection failures)
    virtual void on_error(beast::error_code ec) = 0;

private:
    void do_connect();
    void do_read();
    void do_reconnect();
    void start_ping();

    net::io_context& ioc_;
    tcp::resolver resolver_;
    ws::stream<tcp::socket> ws_;
    std::string host_, port_;
    beast::flat_buffer buffer_;
    net::steady_timer reconnect_timer_;
    net::steady_timer ping_timer_;
};

//------------------------------------------------------------------------------------

#endif // WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------
