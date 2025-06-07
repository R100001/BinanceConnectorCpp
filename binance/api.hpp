
//------------------------------------------------------------------------------------

#ifndef API_HPP
#define API_HPP

//------------------------------------------------------------------------------------

#include <string>
#include <vector>
#include <variant>
#include <memory>

#include "lib/HTTPClient.hpp"
#include "lib/WebSocketClient.hpp"
#include "simdjson.h"

#include "error.hpp"
#include "lib/utils.hpp"

//------------------------------------------------------------------------------------
//----------------------------------------API-----------------------------------------
//------------------------------------------------------------------------------------

class API {

public: // Typedefs

    using MsgCallbackT = std::function<void(std::string_view)>;
    using ErrCallbackT = std::function<void(std::string_view)>;

    enum class RequestType {
        GET,
        POST,
        PUT,
        DELETE
    };

    enum class RequestFormat {
        QueryString,
        JSON
    };

public: // Constructors

    API(
        std::string_view key,
        std::string_view secret = "",
        int32_t const timeout = -1,
        std::string_view proxy = "",
        bool const show_limit_usage = false,
        bool const show_header = false,
        std::string_view private_key = "",
        std::string_view private_key_passphrase = ""
    );

public: // REST API request methods

    template <RequestType req_type> std::string sign_request(std::string_view endpoint, Parameters &payload);
    template <RequestType req_type> std::string send_request(std::string_view endpoint, Parameters const &payload = {}); 

public: // WebSocket API

    void ws_api_connect();
    void ws_api_disconnect();
    void ws_api_send_message(std::string_view message);

    void ws_api_message_callback(MsgCallbackT callback);
    void ws_api_error_callback(ErrCallbackT callback);

public: // Websocket Market Streams

    void ws_market_streams_subscribe(std::string const &stream_name);
    void ws_market_streams_subscribe(std::vector<std::string> const &stream_names);
    void ws_market_streams_unsubscribe(std::string const &stream_name);
    void ws_market_streams_unsubscribe(std::vector<std::string> const &stream_names);
    std::string ws_market_streams_list_subscriptions() const;

    void ws_market_streams_message_callback(MsgCallbackT callback);
    void ws_market_streams_error_callback(ErrCallbackT callback);

public: // Websocket User Data Streams

    void ws_user_data_streams_start();
    void ws_user_data_streams_stop();

    void ws_user_data_streams_message_callback(MsgCallbackT callback);
    void ws_user_data_streams_error_callback(ErrCallbackT callback);

public: // Public message parsing

    /*----- Parsing Tags -----*/
    struct ArrayErrors {};
    struct ResponseIsServerMessage {};

    /*----- Parsing Responses -----*/
    template <typename JsonResponseStructured> 
    using ResponseOrError = std::variant<JsonResponseStructured, ServerMessage>;
    template <typename JsonResponseStructured>
    using ArrayErrorsResponse = ResponseOrError<std::vector<ResponseOrError<JsonResponseStructured>>>;
    using ServerMessageResponse = ServerMessage;

    /*----- Parsing Functions -----*/
    template <typename JsonResponseStructured> 
    ResponseOrError<JsonResponseStructured> parse_response(std::string &response);

    template <typename JsonResponseStructured>
    ArrayErrorsResponse<JsonResponseStructured> parse_response(std::string &response, ArrayErrors const);

    ServerMessageResponse parse_response(std::string &response, ResponseIsServerMessage const);

    static std::optional<ServerMessageResponse> read_server_message(simdjson::ondemand::object &obj);

private:
    simdjson::ondemand::parser &parser() { return this->_parser; }

private: // Private methods

    std::string sign_message(std::string_view message) const;
    template<RequestType req_type> std::string dispach_request(std::string_view const endpoint, std::string const &payload) const;
    
public: // Setters Getters

    std::string const &api_key() const { return this->_key; }

private: // Private variables

    std::string _key;
    std::string _secret;
    std::string _base_url;
    int32_t _timeout;
    std::string _proxy;
    bool _show_limit_usage;
    bool _show_header;
    std::string _private_key;
    std::string _private_key_passphrase;

private: // HTTP Client and WebSocket Client

    HTTPClient _rest_api;

    std::shared_ptr<WebSocketAPIClient> _websocket_api;
    std::shared_ptr<WebSocketMarketStreamsClient> _websocket_market_streams;
    std::shared_ptr<WebSocketUserDataStreamsClient> _websocket_user_data_streams;

private: // Parsing variables

    simdjson::ondemand::parser _parser;
};

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
API::ResponseOrError<JsonResponseStructured> API::parse_response(std::string &response) {
    
    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

    auto obj = doc.get_object();
    if (!obj.error()) {
        std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());

        if(res.has_value()) return res.value();
    }

    doc.rewind();
    
    JsonResponseStructured response_struct;
    auto error = doc.get(response_struct);
    std::cout << "Error: " << simdjson::error_message(error) << std::endl;
    DEBUG_ASSERT(!error);

    return response_struct;
}

//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
API::ArrayErrorsResponse<JsonResponseStructured> API::parse_response(std::string &response, ArrayErrors const) {

    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

#ifndef NDEBUG
    simdjson_print_json_tree(doc);
    doc.rewind();
#endif

    auto obj = doc.get_object();
    if(!obj.error()) {
        std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());
        DEBUG_ASSERT(res.has_value());

        return res.value();
    }
    doc.rewind();

    simdjson::ondemand::array arr;
    auto error = doc.get_array().get(arr);
    DEBUG_ASSERT(!error);

    std::vector<ResponseOrError<JsonResponseStructured>> response_structs;
    for(simdjson::ondemand::value item : arr) {
        response_structs.emplace_back();
        auto error = item.get(response_structs.back());
        DEBUG_ASSERT(!error);
    }
    
    return response_structs;
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::sign_request(std::string_view endpoint, Parameters &payload)
{
    payload.emplace_back(std::make_pair("timestamp", std::to_string(get_timestamp())));
    payload.emplace_back(std::make_pair("signature", this->sign_message(prepare_query_string(payload))));
    return this->send_request<req_type>(endpoint, payload);
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::send_request(std::string_view endpoint, Parameters const &payload)
{
    return this->dispach_request<req_type>(endpoint, prepare_query_string(payload));
}

//------------------------------------------------------------------------------------

template<API::RequestType req_type>
std::string API::dispach_request(std::string_view endpoint, std::string const &payload) const
{
    std::string_view request = payload.empty() ? endpoint : std::string(endpoint) + "?" + payload;

    switch(req_type) {
        case API::RequestType::GET:
            return this->_rest_api.get(request, this->_timeout, this->_proxy);
        case API::RequestType::POST:
            return this->_rest_api.post(request, this->_timeout, this->_proxy);
        case API::RequestType::PUT:
            return this->_rest_api.put(request, this->_timeout, this->_proxy);
        case API::RequestType::DELETE:
            return this->_rest_api.del(request, this->_timeout, this->_proxy);
        default:
            throw std::runtime_error("Unsupported HTTP method!");
    }
}

//------------------------------------------------------------------------------------

#endif // API_HPP

//------------------------------------------------------------------------------------
