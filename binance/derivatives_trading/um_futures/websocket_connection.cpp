
//------------------------------------------------------------------------------------

#include "websocket_connection.hpp"
#include "api.hpp"

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
