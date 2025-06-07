
//------------------------------------------------------------------------------------

#include "api.hpp"

#include <sstream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>

#include "lib/utils.hpp"
#include "lib/authentication.hpp"

//------------------------------------------------------------------------------------

namespace net = boost::asio;

//------------------------------------------------------------------------------------

API::API(
    std::string_view key,
    std::string_view secret,
    int32_t const timeout,
    std::string_view proxy,
    bool const show_limit_usage,
    bool const show_header,
    std::string_view private_key,
    std::string_view private_key_passphrase)
    : _key(key),
      _secret(secret),
      _timeout(timeout),
      _proxy(proxy),
      _show_limit_usage(show_limit_usage),
      _show_header(show_header),
      _private_key(private_key),
      _private_key_passphrase(private_key_passphrase),
      _rest_api(HTTPClient(key)),
      _websocket_api(std::make_shared<WebSocketAPIClient>()),
      _websocket_market_streams(std::make_shared<WebSocketMarketStreamsClient>()),
      _websocket_user_data_streams(std::make_shared<WebSocketUserDataStreamsClient>(key)) {}

//------------------------------------------------------------------------------------

std::string API::sign_message(std::string_view message) const
{
    if(this->_private_key.empty()) {
        return hmac_hashing(this->_secret, message);
    } else {
        return rsa_signature(this->_private_key, message, this->_private_key_passphrase);
    }
}

//------------------------------------------------------------------------------------

std::optional<API::ServerMessageResponse> API::read_server_message(simdjson::ondemand::object &obj) {

    auto iterator = obj.begin();
    if (iterator != obj.end() && (*iterator).key() == "code") {
        
        ServerMessage server_error;
        auto code = (*iterator).value().get_int64();
        DEBUG_ASSERT(!code.error());
        server_error.code = static_cast<int>(code.value_unsafe());
        
        ++iterator;
        DEBUG_ASSERT(iterator != obj.end());
        DEBUG_ASSERT((*iterator).key() == "msg");

        std::string_view msg;
        auto error = (*iterator).value().get_string().get(msg);
        DEBUG_ASSERT(!error);
        server_error.msg = std::string(msg);

        return server_error;
    }

    return std::nullopt;
}

//------------------------------------------------------------------------------------

API::ServerMessageResponse API::parse_response(std::string &response, ResponseIsServerMessage const) {
   
    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

#ifndef NDEBUG
    simdjson_print_json_tree(doc);
    doc.rewind();
#endif

    auto obj = doc.get_object();
    DEBUG_ASSERT(!obj.error());

    std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());
    DEBUG_ASSERT(res.has_value());

    return res.value();
}

//------------------------------------------------------------------------------------
//--------------------------------WebSocket API Methods-------------------------------
//------------------------------------------------------------------------------------

void API::ws_api_connect() {
    _websocket_api->connect();
}

//------------------------------------------------------------------------------------

void API::ws_api_disconnect() {
    _websocket_api->disconnect();
}

//------------------------------------------------------------------------------------

void API::ws_api_send_message(std::string_view message) {
    _websocket_api->send_message(message);
}

//------------------------------------------------------------------------------------

void API::ws_api_message_callback(MsgCallbackT callback) {
    _websocket_api->set_on_message_callback(std::move(callback));
}

//------------------------------------------------------------------------------------

void API::ws_api_error_callback(ErrCallbackT callback) {
    _websocket_api->set_on_error_callback(std::move(callback));
}

//------------------------------------------------------------------------------------
//--------------------------WebSocket Market Streams Methods--------------------------
//------------------------------------------------------------------------------------

void API::ws_market_streams_subscribe(std::string const &stream_name) {
    _websocket_market_streams->subscribe_to_stream(stream_name);
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_subscribe(std::vector<std::string> const &stream_names) {
    _websocket_market_streams->subscribe_to_stream(stream_names);
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_unsubscribe(std::string const &stream_name) {
    _websocket_market_streams->unsubscribe_from_stream(stream_name);
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_unsubscribe(std::vector<std::string> const &stream_names) {
    _websocket_market_streams->unsubscribe_from_stream(stream_names);
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_message_callback(MsgCallbackT callback) {
    _websocket_market_streams->set_on_message_callback_for_all_streams(std::move(callback));
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_error_callback(ErrCallbackT callback) {
    _websocket_market_streams->set_on_error_callback_for_all_streams(std::move(callback));
}

//------------------------------------------------------------------------------------
//-------------------------WebSocket User Data Streams Methods------------------------
//------------------------------------------------------------------------------------

void API::ws_user_data_streams_start() {
    _websocket_user_data_streams->start();
}

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_stop() {
    _websocket_user_data_streams->stop();
}

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_message_callback(MsgCallbackT callback) {
    _websocket_user_data_streams->set_on_message_callback(std::move(callback));
}

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_error_callback(ErrCallbackT callback) {
    _websocket_user_data_streams->set_on_error_callback(std::move(callback));
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------