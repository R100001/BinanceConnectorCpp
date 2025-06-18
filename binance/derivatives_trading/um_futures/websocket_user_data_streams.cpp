
//------------------------------------------------------------------------------------

#include "websocket_user_data_streams.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_connect() {
    _websocket_user_data_streams->connect();
}

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_disconnect() {
    _websocket_user_data_streams->disconnect();
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
