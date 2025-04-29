
#include "WebSocketClient.hpp"

//---------------------------------------------------------------------------------------

// Define namespaces for brevity
namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace ws = beast::websocket;

//---------------------------------------------------------------------------------------

WebSocketClient::WebSocketClient(net::io_context& ioc, const std::string& host, const std::string& port)
    : ioc_(ioc),
        resolver_(ioc),
        ws_(ioc),
        host_(host),
        port_(port),
        reconnect_timer_(ioc),
        ping_timer_(ioc) {}

//---------------------------------------------------------------------------------------

// Virtual destructor for proper cleanup in derived classes
WebSocketClient::~WebSocketClient() {
    close();
}

//---------------------------------------------------------------------------------------

// Start connecting to the WebSocket server
void WebSocketClient::connect() {
    do_connect();
}

//---------------------------------------------------------------------------------------

// Send a message to the server (e.g., subscription request)
void WebSocketClient::send(const std::string& message) {
    ws_.async_write(net::buffer(message),
        [this](beast::error_code ec, std::size_t /*bytes_transferred*/) {
            if (ec) {
                on_error(ec);
            }
        });
}

//---------------------------------------------------------------------------------------

// Close the WebSocket connection gracefully
void WebSocketClient::close() {
    if (ws_.is_open()) {
        ws_.async_close(ws::close_code::normal,
            [this](beast::error_code ec) {
                if (ec) {
                    on_error(ec);
                }
            });
    }
}

//---------------------------------------------------------------------------------------

// Run the I/O context to process asynchronous operations
// Typically called in main() or a dedicated thread
void WebSocketClient::run() {
    ioc_.run();
}

//---------------------------------------------------------------------------------------

// Perform asynchronous connection steps
void WebSocketClient::do_connect() {
    // Step 1: Resolve host and port to IP endpoints
    resolver_.async_resolve(host_, port_,
        [this](beast::error_code ec, tcp::resolver::results_type results) {
            if (ec) {
                on_error(ec);
                do_reconnect();
                return;
            }
            // Step 2: Connect the TCP socket
            net::async_connect(ws_.next_layer(), results,
                [this](beast::error_code ec, const tcp::endpoint& /*endpoint*/) {
                    if (ec) {
                        on_error(ec);
                        do_reconnect();
                        return;
                    }
                    // Step 3: Perform WebSocket handshake
                    ws_.async_handshake(host_, "/ws",
                        [this](beast::error_code ec) {
                            if (ec) {
                                on_error(ec);
                                do_reconnect();
                                return;
                            }
                            // Connection established: start pinging and reading
                            start_ping();
                            do_read();
                        });
                });
        });
}

//---------------------------------------------------------------------------------------

// Continuously read incoming messages
void WebSocketClient::do_read() {
    ws_.async_read(buffer_,
        [this](beast::error_code ec, std::size_t /*bytes_transferred*/) {
            if (!ec) {
                // Convert buffer to string and pass to derived class
                std::string message = beast::buffers_to_string(buffer_.data());
                buffer_.clear();
                on_message(message);
                do_read(); // Continue reading
            } else {
                on_error(ec);
                do_reconnect();
            }
        });
}

//---------------------------------------------------------------------------------------

// Attempt to reconnect after a failure
void WebSocketClient::do_reconnect() {
    // Close the socket to reset state
    ws_.next_layer().close();
    // Wait 5 seconds before retrying (can be extended to exponential backoff)
    reconnect_timer_.expires_after(std::chrono::seconds(5));
    reconnect_timer_.async_wait([this](beast::error_code ec) {
        if (!ec) {
            do_connect();
        }
    });
}

//---------------------------------------------------------------------------------------

// Send periodic pings to keep the connection alive
void WebSocketClient::start_ping() {
    // Ping every 30 seconds (adjustable per exchange)
    ping_timer_.expires_after(std::chrono::seconds(30));
    ping_timer_.async_wait([this](beast::error_code ec) {
        if (ec) {
            // Timer canceled (e.g., during shutdown)
            return;
        }
        ws_.async_ping({},
            [this](beast::error_code ec) {
                if (ec) {
                    on_error(ec);
                }
                start_ping(); // Schedule next ping
            });
    });
}

//---------------------------------------------------------------------------------------
