
//------------------------------------------------------------------------------------

#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------

#include <string>
#include <memory>
#include <chrono>
#include <functional>

#include "HTTPClient.hpp"

//------------------------------------------------------------------------------------

class WebSocketClientImpl;
class InvokeTimer;

//------------------------------------------------------------------------------------

using MsgCallbackT = std::function<void(std::string_view)>;
using ErrCallbackT = std::function<void(std::string_view)>;

//------------------------------------------------------------------------------------

class WebSocketAPIClient : public std::enable_shared_from_this<WebSocketAPIClient> {

private: // Constants
    static constexpr std::string_view WS_API_URL = "wss://ws-fapi.binance.com/ws-fapi/v1";
    static constexpr std::string_view WS_API_TESTNET_URL = "wss://testnet.binancefuture.com/ws-fapi/v1";

public:
    WebSocketAPIClient();
    ~WebSocketAPIClient();

    void connect();
    void disconnect();
    
    void send_message(std::string_view message);

    void set_on_message_callback(MsgCallbackT callback);
    void set_on_error_callback(ErrCallbackT callback);
#if 0 // Until queues are ready
    bool any_message() const;
    bool any_error() const;

    std::string consume_message();
    std::string consume_error();
    
    std::optional<std::string> consume_message_safe();
    std::optional<std::string> consume_error_safe();
#endif // Until queues are ready
private:
    std::unique_ptr<WebSocketClientImpl> _client;
}; // class WebSocketAPIClient

//------------------------------------------------------------------------------------

class WebSocketMarketStreamsClient : public std::enable_shared_from_this<WebSocketMarketStreamsClient> {

public:
    using StreamIdT = uint64_t;

private: // Constants
    static constexpr std::string_view WS_MARKET_STREAMS_URL = "wss://fstream.binance.com/ws/";
    static constexpr std::string_view WS_MARKET_STREAMS_COMBINED_STREAMS_URL = "wss://fstream.binance.com/stream?streams=";

public:
    WebSocketMarketStreamsClient();
    ~WebSocketMarketStreamsClient();

    void subscribe_to_stream(std::string const &stream_name);
    void subscribe_to_stream(std::vector<std::string> const &stream_names);
    void unsubscribe_from_stream(std::string const &stream_name);
    void unsubscribe_from_stream(std::vector<std::string> const &stream_names);
#if 0 // Until queues are ready
    void unsubscribe_from_all_streams();
    void set_on_message_callback_for_stream(StreamIdT const stream_id, MsgCallbackT callback);
    void set_on_message_callback_for_stream(std::string_view stream_name, MsgCallbackT callback);
    void set_on_error_callback_for_stream(StreamIdT const stream_id, ErrCallbackT callback);
    void set_on_error_callback_for_stream(std::string_view stream_name, ErrCallbackT callback);
#endif // Until queues are ready
    void set_on_message_callback_for_all_streams(MsgCallbackT callback);
    void set_on_error_callback_for_all_streams(ErrCallbackT callback);
    
#if 0 // Until queues are ready
    bool any_message() const;
    bool any_error() const;

    std::string consume_message();
    std::string consume_error();

    std::optional<std::string> consume_message_safe();
    std::optional<std::string> consume_error_safe();
#endif // Until queues are ready
    
private:
    std::unique_ptr<WebSocketClientImpl> _client;
}; // class WebSocketMarketStreamsClient

//------------------------------------------------------------------------------------

class WebSocketUserDataStreamsClient : public std::enable_shared_from_this<WebSocketUserDataStreamsClient> {

private: // Constants
    static constexpr std::string_view REST_API_USER_DATA_STREAMS_URL = "https://fapi.binance.com";
    static constexpr std::string_view WS_USER_DATA_STREAMS_URL = "wss://fstream.binance.com/ws/";

    static constexpr std::string_view LISTEN_KEY_ENDPOINT = "/fapi/v1/listenKey";

    static constexpr std::string_view LISTEN_KEY_JSON_PREFIX = R"("listenKey":")";
    static constexpr size_t LISTEN_KEY_JSON_PREFIX_LENGTH = LISTEN_KEY_JSON_PREFIX.size();
    static constexpr size_t LISTEN_KEY_LENGTH = 64;
    static constexpr size_t WS_URL_LENGTH = WS_USER_DATA_STREAMS_URL.size();

public:
    WebSocketUserDataStreamsClient(std::string_view api_key);
    ~WebSocketUserDataStreamsClient();

    void start();
    void stop();
    void set_on_message_callback(MsgCallbackT callback);
    void set_on_error_callback(ErrCallbackT callback);

private:
    void tick();
    void ping();
    void message_callback(MsgCallbackT callback);
    void error_callback(ErrCallbackT callback);

private: // Variables
    HTTPClient _rest_api;
    std::shared_ptr<InvokeTimer> _timer;

    std::string _listen_key;
    std::string _user_data_stream_url;

    MsgCallbackT _on_message_callback;
    ErrCallbackT _on_error_callback;

private:
    std::unique_ptr<WebSocketClientImpl> _client;
}; // class WebSocketUserDataStreamsClient

//------------------------------------------------------------------------------------

#endif // WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------
