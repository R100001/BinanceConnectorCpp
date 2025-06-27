
//------------------------------------------------------------------------------------

#include "api.hpp"

#include <sstream>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/websocket/ssl.hpp>

#include "utils.hpp"

//------------------------------------------------------------------------------------

namespace net = boost::asio;

//------------------------------------------------------------------------------------

API::API(
    std::string_view hmac_api_key,
    std::string_view hmac_api_secret,
    std::string_view ed25519_api_key,
    std::string_view ed25519_private_key,
    std::string_view ed25519_private_key_passphrase,
    int32_t const timeout,
    std::string_view proxy,
    bool const show_limit_usage,
    bool const show_header
    )
    : _hmac_api_key(hmac_api_key),
      _hmac_api_secret(hmac_api_secret),
      _ed25519_api_key(ed25519_api_key),
      _ed25519_private_key(ed25519_private_key),
      _ed25519_private_key_passphrase(ed25519_private_key_passphrase),
      _timeout(timeout),
      _proxy(proxy),
      _show_limit_usage(show_limit_usage),
      _show_header(show_header),
      _rest_api(HTTPClient(hmac_api_key)),
      _websocket_api(std::make_shared<WebSocketAPIClient>()),
      _websocket_market_streams(std::make_shared<WebSocketMarketStreamsClient>()),
      _websocket_user_data_streams(std::make_shared<WebSocketUserDataStreamsClient>(hmac_api_key)) {}

//------------------------------------------------------------------------------------

std::optional<ServerMessageResponse> API::read_server_message(simdjson::ondemand::object &obj) {

    auto iterator = obj.begin();
    if (iterator != obj.end() && (*iterator).key() == "code") {
        
        ServerMessageResponse server_error;
        {auto error = (*iterator).value().get(server_error.code); DEBUG_ASSERT(!error);}
        
        ++iterator;
        DEBUG_ASSERT(iterator != obj.end() && (*iterator).key() == "msg");

        std::string_view msg;
        {auto error = (*iterator).value().get_string().get(msg); DEBUG_ASSERT(!error);}
        server_error.msg = std::string(msg);

        return server_error;
    }

    return std::nullopt;
}

//------------------------------------------------------------------------------------

ServerMessageResponse API::parse_response(std::string &response, ResponseIsServerMessage const) {
   
    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

#ifndef NDEBUG
    simdjson_print_json_tree(doc);
    doc.rewind();
#endif

    std::optional<ServerMessageResponse> server_message;
    {auto error = doc.get<std::optional<ServerMessageResponse>>().get(server_message); DEBUG_ASSERT(!error);}
    DEBUG_ASSERT(server_message.has_value());

    return server_message.value();
}

//------------------------------------------------------------------------------------
