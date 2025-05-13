
//------------------------------------------------------------------------------------

#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------

#include <string>
#include <memory>
#include <chrono>
#include <functional>

//------------------------------------------------------------------------------------

class WebSocketAPI {

private: // Constants
    constexpr static std::string_view base_endpoint = "wss://ws-fapi.binance.com/ws-fapi/v1";
    constexpr static std::string_view base_endpoint_testnet = "wss://testnet.binancefuture.com/ws-fapi/v1";

public:
    WebSocketAPI();

private:
    class WebSocketClientImpl;
    std::unique_ptr<WebSocketClientImpl> _client;
}; // class WebSocketAPI

//------------------------------------------------------------------------------------

class WebSocketMarketStreams {

private: // Constants
    constexpr static std::string_view base_endpoint = "wss://fstream.binance.com";
    constexpr static std::string_view base_raw_stream_endpoint = "/ws/";
    constexpr static std::string_view base_combined_streams_endpoint = "/stream?streams=";

public:
    WebSocketMarketStreams();
    
private:
    class WebSocketClientImpl;
    std::unique_ptr<WebSocketClientImpl> _client;
}; // class WebSocketMarketStreams

//------------------------------------------------------------------------------------

class WebSocketUserDataStreams {

private: // Constants
    constexpr static std::string_view base_API_endpoint = "https://fapi.binance.com";
    constexpr static std::string_view base_websocket_endpoint = "wss://fstream.binance.com";
    constexpr static std::string_view base_raw_stream_endpoint = "/ws/";

public:
    WebSocketUserDataStreams();
    
private:
    class WebSocketClientImpl;
    std::unique_ptr<WebSocketClientImpl> _client;
}; // class WebSocketUserDataStreams

//------------------------------------------------------------------------------------

#endif // WEBSOCKETCLIENT_HPP

//------------------------------------------------------------------------------------
