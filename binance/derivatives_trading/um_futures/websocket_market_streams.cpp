
//------------------------------------------------------------------------------------

#include "websocket_market_streams.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------
//-------------------------WebSocket Market Streams Handling--------------------------
//------------------------------------------------------------------------------------

void API::ws_market_streams_connect() {
    _websocket_market_streams->connect();
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_disconnect() {
    _websocket_market_streams->disconnect();
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_message_callback(MsgCallbackT callback) {
    _websocket_market_streams->set_on_message_callback(std::move(callback));
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_error_callback(ErrCallbackT callback) {
    _websocket_market_streams->set_on_error_callback(std::move(callback));
}

//------------------------------------------------------------------------------------
//--------------------------WebSocket Market Streams Methods--------------------------
//------------------------------------------------------------------------------------

static std::string ws_market_prepare_request(std::string const &stream_name, WebsocketMarketStreamsMethod const wsms_method, std::string const &id) {

    std::string const method = (wsms_method == WebsocketMarketStreamsMethod::SUBSCRIBE) ? "SUBSCRIBE" : "UNSUBSCRIBE";

    Parameters const params{
        {"method", method},
        {"params", std::vector<std::string>{stream_name}},
        {"id", id}
    };

    return prepare_json_string(params);
}
    

void API::aggregate_trade_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol) {
    std::string const stream_name = symbol + "@aggTrade";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "agg_trade"));
}

//-------------------------------------------------------------------------------------

void API::mark_price_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, uint8_t const update_speed) {
    std::string const stream_name = symbol + "@markPrice" + (update_speed == 3 ? "" : "@1s");

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "mark_price"));
}

//-------------------------------------------------------------------------------------

void API::mark_price_stream_for_all_market(WebsocketMarketStreamsMethod const wsms_method, uint8_t const update_speed) {
    std::string const stream_name = "!markPrice@arr" + (update_speed == 3 ? std::string() : std::string("@1s"));

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "mark_price_all"));
}

//-------------------------------------------------------------------------------------

void API::kline_candlestick_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &interval) {
    std::string const stream_name = symbol + "@kline_" + interval;

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "klines"));
}

//-------------------------------------------------------------------------------------

void API::continuous_contract_kline_candlestick_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &pair, std::string const &contract_type, std::string const &interval) {
    std::string const stream_name = pair + "_" + contract_type + "@continuousKline_" + interval;

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "continuous_klines"));
}

//-------------------------------------------------------------------------------------

void API::individual_symbol_mini_ticker_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol) {
    std::string const stream_name = symbol + "@miniTicker";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "mini_ticker"));
}

//-------------------------------------------------------------------------------------

void API::all_market_mini_ticker_streams(WebsocketMarketStreamsMethod const wsms_method) {
    std::string const stream_name = "!miniTicker@arr";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "mini_ticker_all"));
}

//-------------------------------------------------------------------------------------

void API::individual_symbol_ticker_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol) {
    std::string const stream_name = symbol + "@ticker";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "ticker"));
}

//-------------------------------------------------------------------------------------

void API::all_market_ticker_streams(WebsocketMarketStreamsMethod const wsms_method) {
    std::string const stream_name = "!ticker@arr";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "ticker_all"));
}

//-------------------------------------------------------------------------------------

void API::individual_symbol_book_ticker_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol) {
    std::string const stream_name = symbol + "@bookTicker";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "book_ticker"));
}

//-------------------------------------------------------------------------------------

void API::all_book_tickers_stream(WebsocketMarketStreamsMethod const wsms_method) {
    std::string const stream_name = "!bookTicker";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "book_ticker_all"));
}

//-------------------------------------------------------------------------------------

void API::liquidation_order_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol) {
    std::string const stream_name = symbol + "@forceOrder";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "force_order"));
}

//-------------------------------------------------------------------------------------

void API::all_market_liquidation_order_streams(WebsocketMarketStreamsMethod const wsms_method) {
    std::string const stream_name = "!forceOrder@arr";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "force_order_all"));
}

//-------------------------------------------------------------------------------------

void API::partial_book_depth_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, int16_t const levels, uint16_t const update_speed) {
    std::string const stream_name = symbol + "@depth" + std::to_string(levels) + (update_speed == 250 ? "" : "@" + std::to_string(update_speed) + "ms");

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "depth_partial"));
}

//-------------------------------------------------------------------------------------

void API::diff_book_depth_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, uint16_t const update_speed) {
    std::string const stream_name = symbol + "@depth" + (update_speed == 250 ? "" : "@" + std::to_string(update_speed) + "ms");

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "depth_diff"));
}

//-------------------------------------------------------------------------------------

void API::composite_index_symbol_information_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol) {
    std::string const stream_name = symbol + "@compositeIndex";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "composite_index"));
}

//-------------------------------------------------------------------------------------

void API::contract_info_stream(WebsocketMarketStreamsMethod const wsms_method) {
    std::string const stream_name = "!contractInfo";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "contract_info"));
}

//-------------------------------------------------------------------------------------

void API::multi_assets_mode_asset_index(WebsocketMarketStreamsMethod const wsms_method, std::string const &asset_symbol) {
    std::string const stream_name = asset_symbol.size() ? asset_symbol + "@assetIndex" : "!assetIndex@arr";

    _websocket_market_streams->send_message(ws_market_prepare_request(stream_name, wsms_method, "asset_index"));
}

//-------------------------------------------------------------------------------------

void API::ws_market_streams_multiple_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &streams) {
    _websocket_market_streams->send_message(ws_market_prepare_request(streams, wsms_method, "multiple_streams"));
}

//-------------------------------------------------------------------------------------

void API::ws_market_streams_list_subscriptions() const {

    Parameters const params{
        {"method", "LIST_SUBSCRIPTIONS"},
        {"id", "list_subscriptions"}
    };

    std::string const message = prepare_json_string(params);
    _websocket_market_streams->send_message(message);
}

//-------------------------------------------------------------------------------------
