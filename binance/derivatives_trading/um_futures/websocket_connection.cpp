
//------------------------------------------------------------------------------------

#include "websocket_connection.hpp"

//------------------------------------------------------------------------------------

namespace WebsocketAPI {

//------------------------------------------------------------------------------------

void connect(API &api) {
    api.ws_api_connect();
}

//------------------------------------------------------------------------------------

void disconnect(API &api) {
    api.ws_api_disconnect();
}

//------------------------------------------------------------------------------------

void set_on_message_callback(API &api, API::MsgCallbackT callback) {
    api.ws_api_message_callback(callback);
}

//------------------------------------------------------------------------------------

void set_on_error_callback(API &api, API::ErrCallbackT callback) {
    api.ws_api_error_callback(callback);
}

//------------------------------------------------------------------------------------

} // namespace WebsocketAPI

//------------------------------------------------------------------------------------

namespace WebsocketMarketStreams {

//------------------------------------------------------------------------------------

void subscribe(API &api, std::string const &stream_name) {
    api.ws_market_streams_subscribe(stream_name);
}

//------------------------------------------------------------------------------------

void subscribe(API &api, std::vector<std::string> const &stream_names) {
    api.ws_market_streams_subscribe(stream_names);
}

//------------------------------------------------------------------------------------

void unsubscribe(API &api, std::string const &stream_name) {
    api.ws_market_streams_unsubscribe(stream_name);
}

//------------------------------------------------------------------------------------

void unsubscribe(API &api, std::vector<std::string> const &stream_names) {
    api.ws_market_streams_unsubscribe(stream_names);
}

//------------------------------------------------------------------------------------

void set_on_message_callback(API &api, API::MsgCallbackT callback) {
    api.ws_user_data_streams_message_callback(callback);
}

//------------------------------------------------------------------------------------

void set_on_error_callback(API &api, API::ErrCallbackT callback) {
    api.ws_user_data_streams_error_callback(callback);
}

//------------------------------------------------------------------------------------

} // namespace WebsocketMarketStreams

//------------------------------------------------------------------------------------

namespace WebsocketUserDataStreams {

//------------------------------------------------------------------------------------

void start(API &api) {
    api.ws_user_data_streams_start();
}

//------------------------------------------------------------------------------------

void stop(API &api) {
    api.ws_user_data_streams_stop();
}

//------------------------------------------------------------------------------------
    
void set_on_message_callback(API &api, API::MsgCallbackT callback) {
    api.ws_user_data_streams_message_callback(callback);
}

//------------------------------------------------------------------------------------

void set_on_error_callback(API &api, API::ErrCallbackT callback) {
    api.ws_user_data_streams_error_callback(callback);
}

//------------------------------------------------------------------------------------

} // namespace WebsocketUserDataStreams

//------------------------------------------------------------------------------------
