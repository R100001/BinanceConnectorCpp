
//---------------------------------------------------------------------------------------

#include "WebSocketClient.hpp"

#include <iostream>
#include <queue>

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>

#include "utils.hpp"

//------------------------------------------------------------------------------------

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace ws = beast::websocket;
namespace ssl = net::ssl;

//------------------------------------------------------------------------------------

#include <boost/asio.hpp>
#include <chrono>
#include <functional>
#include <memory>

class InvokeTimer : public std::enable_shared_from_this<InvokeTimer> {
public:
    using steady_timer = boost::asio::steady_timer;
    using Duration     = steady_timer::duration;
    using Callback     = std::function<void()>;

    explicit InvokeTimer(std::shared_ptr<net::io_context> ioc);
    ~InvokeTimer();

    void start(Duration d, Callback cb);
    void stop();

private:

    void tick();

private: // Members

    steady_timer _timer;
    Duration     _interval;
    Callback     _callback;
    bool         _running;
};

//------------------------------------------------------------------------------------

InvokeTimer::InvokeTimer(std::shared_ptr<net::io_context> ioc)
    : _timer(*ioc), _running(false) {}

//------------------------------------------------------------------------------------

InvokeTimer::~InvokeTimer() {
    stop();
}

//------------------------------------------------------------------------------------

void InvokeTimer::stop() {
    _running = false;
    _timer.cancel();
}

//------------------------------------------------------------------------------------

void InvokeTimer::start(Duration d, Callback cb) {
    _interval = d;
    _callback = std::move(cb);
    _running  = true;

    _timer.cancel();
    _timer.expires_after(_interval);
    _timer.async_wait([self = shared_from_this()](auto ec){
        if (!ec) self->tick();
    });
}

//------------------------------------------------------------------------------------

void InvokeTimer::tick() {
    if (!_running) return;

    _callback();

    _timer.expires_after(_interval);
    _timer.async_wait([self = shared_from_this()](auto ec){
        if (!ec) self->tick();
    });
}

//------------------------------------------------------------------------------------

class WebSocketClientImpl {

private: // Constants
    constexpr static uint64_t default_initial_reconnect_delay = 1000;
    constexpr static uint64_t default_max_reconnect_delay = 60000;

public:
    WebSocketClientImpl(std::shared_ptr<net::io_context> ioc, std::shared_ptr<net::ssl::context> ctx, 
                    std::string_view host, std::string_view port = "443",
                    std::chrono::milliseconds initial_reconnect_delay = std::chrono::milliseconds(default_initial_reconnect_delay),
                    std::chrono::milliseconds max_reconnect_delay = std::chrono::milliseconds(default_max_reconnect_delay));
    ~WebSocketClientImpl();

    void connect();
    void send(std::string_view message);
    void close();
    void run();

    void set_on_message_callback(std::function<void(std::string_view)> callback);
    void set_on_error_callback(std::function<void(std::string_view)> callback);

    void on_message(std::string_view message);
    void on_error(beast::error_code ec);

#if 0 // Until queues are ready
    bool any_message() const;
    bool any_error() const;

    std::string consume_message();
    std::string consume_error();

    std::optional<std::string> consume_message_safe();
    std::optional<std::string> consume_error_safe();

    void drop_all_messages();
    void drop_all_errors();
    void drop_all();
#endif

private: // Functions
    void do_connect();
    void do_read();
    void do_reconnect();

private: // Message Handlers
    MsgCallbackT _on_message_callback;
    ErrCallbackT _on_error_callback;

#if 0 // Until queues are ready
    std::queue<std::string> _message_queue;
    std::queue<std::string> _error_queue;
#endif

protected: // Members
    std::shared_ptr<net::io_context> _ioc;
    std::shared_ptr<net::ssl::context> _ssl_ctx;

private:
    tcp::resolver _resolver;
    std::unique_ptr<ws::stream<ssl::stream<beast::tcp_stream>>> _wss;
    std::string _host, _port, _endpoint;
    beast::flat_buffer _buffer;
    net::steady_timer _reconnect_timer;

    std::chrono::milliseconds _initial_reconnect_delay;
    std::chrono::milliseconds _max_reconnect_delay;
    std::chrono::milliseconds _current_reconnect_delay;

    boost::asio::executor_work_guard<net::io_context::executor_type> _work_guard;
    std::thread _ioc_worker;
}; // class WebSocketClientImpl

//---------------------------------------------------------------------------------------

namespace net    = boost::asio;
using tcp        = net::ip::tcp;
namespace beast  = boost::beast;
namespace ws     = beast::websocket;

//---------------------------------------------------------------------------------------
//----------------------------------WebSocketClientImpl----------------------------------
//---------------------------------------------------------------------------------------

WebSocketClientImpl::WebSocketClientImpl(std::shared_ptr<net::io_context> ioc,
                                         std::shared_ptr<net::ssl::context> ctx,
                                         std::string_view host,
                                         std::string_view port,
                                         std::chrono::milliseconds initial_reconnect_delay,
                                         std::chrono::milliseconds max_reconnect_delay)
    : _ioc(ioc),
      _ssl_ctx(ctx),
      _resolver(*ioc),
      _host(host),
      _port(port),
      _reconnect_timer(*ioc),
      _initial_reconnect_delay(initial_reconnect_delay),
      _max_reconnect_delay(max_reconnect_delay),
      _current_reconnect_delay(initial_reconnect_delay),
      _on_message_callback(nullptr),
      _on_error_callback(nullptr),
      _work_guard(boost::asio::make_work_guard(*_ioc)) {
    std::cout << "WebSocketClientImpl created for host: " << _host << " on port: " << _port << std::endl;
}

//---------------------------------------------------------------------------------------

WebSocketClientImpl::~WebSocketClientImpl() {
    close();
    _work_guard.reset();
    _ioc->stop();
    if (_ioc_worker.joinable()) {
        _ioc_worker.join();
    }
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::connect() {
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
    _ioc_worker = std::thread([this]() { _ioc->run(); });
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::set_on_message_callback(std::function<void(std::string_view)> callback) {
    _on_message_callback = std::move(callback);
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::set_on_error_callback(std::function<void(std::string_view)> callback) {
    _on_error_callback = std::move(callback);
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::on_message(std::string_view message) {
    if (_on_message_callback) {
        _on_message_callback(message);
    } 
#if 0 // Until queues are ready
    else {
        _message_queue.push(std::string(message));
    }
#endif
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::on_error(beast::error_code ec) {
    if (_on_error_callback) {
        _on_error_callback(ec.message());
    } 
#if 0 // Until queues are ready
    else {
        _error_queue.push(ec.message());
    }
#endif
}
#if 0 // Until queues are ready
//---------------------------------------------------------------------------------------

bool WebSocketClientImpl::any_message() const {
    return !_message_queue.empty();
}

//---------------------------------------------------------------------------------------

bool WebSocketClientImpl::any_error() const {
    return !_error_queue.empty();
}

//---------------------------------------------------------------------------------------

std::string WebSocketClientImpl::consume_message() {
    std::string message = std::move(_message_queue.front());
    _message_queue.pop();
    return message;
}

//---------------------------------------------------------------------------------------

std::string WebSocketClientImpl::consume_error() {
    std::string error = std::move(_error_queue.front());
    _error_queue.pop();
    return error;
}

//---------------------------------------------------------------------------------------

std::optional<std::string> WebSocketClientImpl::consume_message_safe() {
    if (any_message()) {
        return consume_message();
    }
    return std::nullopt;
}

//---------------------------------------------------------------------------------------

std::optional<std::string> WebSocketClientImpl::consume_error_safe() {
    if (any_error()) {
        return consume_error();
    }
    return std::nullopt;
}
#endif // Until queues are ready
//---------------------------------------------------------------------------------------

void WebSocketClientImpl::do_connect() {

    _wss = std::make_unique<ws::stream<ssl::stream<beast::tcp_stream>>>(
        net::make_strand(*_ioc), *_ssl_ctx);

    // SSL_set_tlsext_host_name(_wss->next_layer().native_handle(), _host.c_str());

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
                    _wss->next_layer().async_handshake(ssl::stream_base::client,
                        [this](beast::error_code ec) {
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
                                    do_read();
                                    _reconnect_timer.expires_after(std::chrono::hours(23));
                                    _reconnect_timer.async_wait(
                                        [this](beast::error_code ec) {
                                            if (!ec) {
                                                close();
                                            }
                                        });
                                });
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
#if 0 // Until queues are ready
//---------------------------------------------------------------------------------------

void WebSocketClientImpl::drop_all_messages() {
    while (!_message_queue.empty()) {
        _message_queue.pop();
    }
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::drop_all_errors() {
    while (!_error_queue.empty()) {
        _error_queue.pop();
    }
}

//---------------------------------------------------------------------------------------

void WebSocketClientImpl::drop_all() {
    drop_all_messages();
    drop_all_errors();
}
#endif // Until queues are ready
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//---------------------------------WebSocketAPIClient------------------------------------
//---------------------------------------------------------------------------------------

WebSocketAPIClient::WebSocketAPIClient() {

    std::shared_ptr<net::io_context> ioc = std::make_shared<net::io_context>();
    std::shared_ptr<net::ssl::context> ctx = std::make_shared<net::ssl::context>(net::ssl::context::tlsv12_client);
    ctx->set_verify_mode(net::ssl::verify_peer);
    ctx->set_default_verify_paths();
    
    _client = std::make_unique<WebSocketClientImpl>(std::move(ioc), std::move(ctx), WS_API_URL);
}

//---------------------------------------------------------------------------------------

WebSocketAPIClient::~WebSocketAPIClient() = default;

//---------------------------------------------------------------------------------------

void WebSocketAPIClient::connect() {
    _client->connect();
    _client->run();
}

//---------------------------------------------------------------------------------------

void WebSocketAPIClient::disconnect() {
    _client->close();
}

//---------------------------------------------------------------------------------------

void WebSocketAPIClient::send_message(std::string_view message) {
    _client->send(message);
}

//---------------------------------------------------------------------------------------

void WebSocketAPIClient::set_on_message_callback(MsgCallbackT callback) {
    _client->set_on_message_callback(std::move(callback));
}

//---------------------------------------------------------------------------------------

void WebSocketAPIClient::set_on_error_callback(ErrCallbackT callback) {
    _client->set_on_error_callback(std::move(callback));
}
#if 0 // Until queues are ready
//---------------------------------------------------------------------------------------

bool WebSocketAPIClient::any_message() const {
    return _client->any_message();
}

//---------------------------------------------------------------------------------------

bool WebSocketAPIClient::any_error() const {
    return _client->any_error();
}

//---------------------------------------------------------------------------------------

std::string WebSocketAPIClient::consume_message() {
    return _client->consume_message();
}

//---------------------------------------------------------------------------------------

std::string WebSocketAPIClient::consume_error() {
    return _client->consume_error();
}

//---------------------------------------------------------------------------------------

std::optional<std::string> WebSocketAPIClient::consume_message_safe() {
    return _client->consume_message_safe();
}

//---------------------------------------------------------------------------------------

std::optional<std::string> WebSocketAPIClient::consume_error_safe() {
    return _client->consume_error_safe();
}
#endif // Until queues are ready
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//----------------------------WebSocketMarketStreamsClient-------------------------------
//---------------------------------------------------------------------------------------

WebSocketMarketStreamsClient::WebSocketMarketStreamsClient() {

    std::shared_ptr<net::io_context> ioc = std::make_shared<net::io_context>();
    std::shared_ptr<net::ssl::context> ctx = std::make_shared<net::ssl::context>(net::ssl::context::tlsv12_client);
    ctx->set_verify_mode(net::ssl::verify_peer);
    ctx->set_default_verify_paths();

    _client = std::make_unique<WebSocketClientImpl>(std::move(ioc), std::move(ctx), WS_MARKET_STREAMS_COMBINED_STREAMS_URL);

    _client->connect();
    _client->run();
}

//---------------------------------------------------------------------------------------

WebSocketMarketStreamsClient::~WebSocketMarketStreamsClient() = default;

//---------------------------------------------------------------------------------------

void WebSocketMarketStreamsClient::subscribe_to_stream(std::string const &stream_name) {
    subscribe_to_stream(std::vector<std::string>{stream_name});
}

//---------------------------------------------------------------------------------------

void WebSocketMarketStreamsClient::subscribe_to_stream(std::vector<std::string> const &stream_names) {

    Parameters const params{
        {"method", "SUBSCRIBE"},
        {"params", stream_names},
        {"id", 1}
    };
    std::string const message = prepare_json_string(params);
    _client->send(message);
}

//---------------------------------------------------------------------------------------

void WebSocketMarketStreamsClient::unsubscribe_from_stream(std::string const &stream_name) {
    unsubscribe_from_stream(std::vector<std::string>{stream_name});
}

//---------------------------------------------------------------------------------------

void WebSocketMarketStreamsClient::unsubscribe_from_stream(std::vector<std::string> const &stream_names) {

    Parameters const params{
        {"method", "UNSUBSCRIBE"},
        {"params", stream_names},
        {"id", 2}
    };
    std::string const message = prepare_json_string(params);
    _client->send(message);
}

//---------------------------------------------------------------------------------------

void WebSocketMarketStreamsClient::set_on_message_callback_for_all_streams(MsgCallbackT callback) {
    _client->set_on_message_callback(std::move(callback));
}

//---------------------------------------------------------------------------------------

void WebSocketMarketStreamsClient::set_on_error_callback_for_all_streams(ErrCallbackT callback) {
    _client->set_on_error_callback(std::move(callback));
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//---------------------------WebSocketUserDataStreamsClient------------------------------
//---------------------------------------------------------------------------------------

WebSocketUserDataStreamsClient::WebSocketUserDataStreamsClient(std::string_view api_key)
    : _rest_api(HTTPClient(api_key)),
      _timer(nullptr),
      _on_message_callback(nullptr),
      _on_error_callback(nullptr) {}

//---------------------------------------------------------------------------------------

WebSocketUserDataStreamsClient::~WebSocketUserDataStreamsClient() = default;

//---------------------------------------------------------------------------------------

void WebSocketUserDataStreamsClient::start() {

    std::string const listen_key_json = _rest_api.post(LISTEN_KEY_ENDPOINT);
    std::string_view listen_key_json_view(listen_key_json);

    std::string_view listen_key = listen_key_json_view.substr(LISTEN_KEY_JSON_PREFIX_LENGTH, LISTEN_KEY_LENGTH);

    char websocket_url[WS_URL_LENGTH + LISTEN_KEY_LENGTH + 1];
    snprintf(websocket_url, sizeof(websocket_url), "%s%s", WS_USER_DATA_STREAMS_URL.data(), listen_key.data());

    auto ioc = std::make_shared<net::io_context>();
    auto ctx = std::make_shared<net::ssl::context>(net::ssl::context::tlsv12_client);
    ctx->set_verify_mode(net::ssl::verify_peer);
    ctx->set_default_verify_paths();

    _client = std::make_unique<WebSocketClientImpl>(ioc, ctx, websocket_url);
    _timer = std::make_shared<InvokeTimer>(ioc);

    if( _on_message_callback ) {
        _client->set_on_message_callback(_on_message_callback);
    }
    if( _on_error_callback ) {
        _client->set_on_error_callback(_on_error_callback);
    }

    _client->connect();
    _client->run();

    _timer->start( std::chrono::minutes(55), [self = shared_from_this()](){ self->ping(); });
}

//---------------------------------------------------------------------------------------

void WebSocketUserDataStreamsClient::stop() {

    _rest_api.del(LISTEN_KEY_ENDPOINT);

    if (_client) {
        _client->close();
    }
    _client.reset();

    _timer.reset();
}

//---------------------------------------------------------------------------------------

void WebSocketUserDataStreamsClient::ping() {

    std::string const response = _rest_api.put(LISTEN_KEY_ENDPOINT);

    if ( response.substr(0, LISTEN_KEY_JSON_PREFIX_LENGTH) != LISTEN_KEY_JSON_PREFIX ) {
        stop();
        start();
    }
}

//---------------------------------------------------------------------------------------

void WebSocketUserDataStreamsClient::set_on_message_callback(MsgCallbackT callback) {
    message_callback(std::move(callback));
}

//---------------------------------------------------------------------------------------

void WebSocketUserDataStreamsClient::set_on_error_callback(ErrCallbackT callback) {
    error_callback(std::move(callback));
}

//---------------------------------------------------------------------------------------

void WebSocketUserDataStreamsClient::message_callback(MsgCallbackT callback) {
    _on_message_callback = std::move(callback);
    if (_client) {
        _client->set_on_message_callback(_on_message_callback);
    }
}

//---------------------------------------------------------------------------------------

void WebSocketUserDataStreamsClient::error_callback(ErrCallbackT callback) {
    _on_error_callback = std::move(callback);
    if (_client) {
        _client->set_on_error_callback(_on_error_callback);
    }
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
