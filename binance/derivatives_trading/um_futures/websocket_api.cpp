
//------------------------------------------------------------------------------------

#include "websocket_api.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------
//-------------------------------WebSocket API Handling-------------------------------
//------------------------------------------------------------------------------------

void API::ws_api_connect() {
    _websocket_api->connect();
}

//------------------------------------------------------------------------------------

void API::ws_api_disconnect() {
    _websocket_api->disconnect();
}

//------------------------------------------------------------------------------------

void API::ws_api_session_logon() {
    _websocket_api->session_logon(ed25519_api_key(), ed25519_private_key(), ed25519_private_key_passphrase());
}

//------------------------------------------------------------------------------------

void API::ws_api_session_status() {
    _websocket_api->session_status();
}

//------------------------------------------------------------------------------------

void API::ws_api_session_logout() {
    _websocket_api->session_logout();
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
//---------------------------------------Account--------------------------------------
//------------------------------------------------------------------------------------

void API::futures_account_balance_v2_stream(int32_t const recv_window, std::string const &id) {
    std::string const method = "v2/account.balance";

    Parameters params{
        {"timestamp", get_timestamp()}
    };

    std::string query_string = prepare_query_string(params);

    // api.ws_api_send_message()
}

//------------------------------------------------------------------------------------

void API::futures_account_balance_stream(int32_t const recv_window, std::string const &id) {
    std::string const method = "v1/account.balance";
}

//------------------------------------------------------------------------------------

void API::account_information_v2_stream(int32_t const recv_window, std::string const &id) {
    std::string const method = "v2/account.status";
}

//------------------------------------------------------------------------------------

void API::account_information_stream(int32_t const recv_window, std::string const &id) {
    std::string const method = "v1/account.status";
}

//------------------------------------------------------------------------------------
//-------------------------------------Market Data------------------------------------
//------------------------------------------------------------------------------------

void API::order_book_stream(std::string const &symbol, int16_t const &limit, std::string const &id) {
    std::string const method = "depth";
}

//------------------------------------------------------------------------------------

void API::symbol_price_ticker_stream(std::string const &symbol, std::string const &id) {
    std::string const method = "ticker.price";
}

//------------------------------------------------------------------------------------

void API::symbol_order_book_ticker_stream(std::string const &symbol, std::string const &id) {
    std::string const method = "ticker.book";
}

//------------------------------------------------------------------------------------
//----------------------------------------Trade---------------------------------------
//------------------------------------------------------------------------------------

void API::new_order_stream(Trade::NewOrder const &order, bool const close_position, int32_t const recv_window, std::string const &id) {
    std::string const method = "order.place";
}

//------------------------------------------------------------------------------------

void API::modify_order_stream(Trade::ModifyOrder const &order, int32_t const recv_window, std::string const &id) {
    std::string const method = "order.modify";
}

//------------------------------------------------------------------------------------

void API::cancel_order_stream(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int32_t const recv_window, std::string const &id) {
    std::string const method = "order.cancel";
}

//------------------------------------------------------------------------------------

void API::query_order_stream(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int32_t const recv_window, std::string const &id) {
    std::string const method = "order.status";
}

//------------------------------------------------------------------------------------

void API::position_information_v2_stream(std::string const &symbol, int32_t const recv_window, std::string const &id) {
    std::string const method = "v2/account.position";
}

//------------------------------------------------------------------------------------

void API::position_information_stream(std::string const &symbol, int32_t const recv_window, std::string const &id) {
    std::string const method = "account.position";
}

//------------------------------------------------------------------------------------
