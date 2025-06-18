
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
    _websocket_market_streams->set_on_message_callback_for_all_streams(std::move(callback));
}

//------------------------------------------------------------------------------------

void API::ws_market_streams_error_callback(ErrCallbackT callback) {
    _websocket_market_streams->set_on_error_callback_for_all_streams(std::move(callback));
}

//------------------------------------------------------------------------------------
//--------------------------WebSocket Market Streams Methods--------------------------
//------------------------------------------------------------------------------------

static void ws_market_send_request(std::shared_ptr<WebSocketMarketStreamsClient> ws_stream, std::string const &stream_name, WebsocketMarketStreamsMethod const wsms_method, std::string const &id) {

    std::string request_id = id.empty() ? std::to_string(get_timestamp()) : id;
    switch (wsms_method) {
        case WebsocketMarketStreamsMethod::SUBSCRIBE:
            ws_stream->subscribe_to_stream(stream_name, request_id);
            break;
        case WebsocketMarketStreamsMethod::UNSUBSCRIBE:
            ws_stream->unsubscribe_from_stream(stream_name, request_id);
            break;
    }
}
    

void API::aggregate_trade_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &id) {
    std::string const stream_name = symbol + "@aggTrade";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::mark_price_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, uint8_t const update_speed, std::string const &id) {
    std::string const stream_name = symbol + "@markPrice" + (update_speed == 3 ? "" : "@1s");

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::mark_price_stream_for_all_market(WebsocketMarketStreamsMethod const wsms_method, uint8_t const update_speed, std::string const &id) {
    std::string const stream_name = "!markPrice@arr" + (update_speed == 3 ? std::string() : std::string("@1s"));

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::kline_candlestick_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &interval, std::string const &id) {
    std::string const stream_name = symbol + "@kline_" + interval;

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::continuous_contract_kline_candlestick_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &pair, std::string const &contract_type, std::string const &interval, std::string const &id) {
    std::string const stream_name = pair + "_" + contract_type + "@continuousKline_" + interval;

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::individual_symbol_mini_ticker_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &id) {
    std::string const stream_name = symbol + "@miniTicker";
    
    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::all_market_mini_ticker_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &id) {
    std::string const stream_name = "!miniTicker@arr";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::individual_symbol_ticker_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &id) {
    std::string const stream_name = symbol + "@ticker";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::all_market_ticker_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &id) {
    std::string const stream_name = "!ticker@arr";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::individual_symbol_book_ticker_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &id) {
    std::string const stream_name = symbol + "@bookTicker";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::all_book_tickers_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &id) {
    std::string const stream_name = "!bookTicker";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::liquidation_order_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &id) {
    std::string const stream_name = symbol + "@forceOrder";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::all_market_liquidation_order_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &id) {
    std::string const stream_name = "!forceOrder@arr";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::partial_book_depth_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, int16_t const levels, uint16_t const update_speed, std::string const &id) {
    std::string const stream_name = symbol + "@depth" + std::to_string(levels) + (update_speed == 250 ? "" : "@" + std::to_string(update_speed) + "ms");

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::diff_book_depth_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, uint16_t const update_speed, std::string const &id) {
    std::string const stream_name = symbol + "@depth" + (update_speed == 250 ? "" : "@" + std::to_string(update_speed) + "ms");

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::composite_index_symbol_information_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &id) {
    std::string const stream_name = symbol + "@compositeIndex";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::contract_info_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &id) {
    std::string const stream_name = "!contractInfo";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::multi_assets_mode_asset_index(WebsocketMarketStreamsMethod const wsms_method, std::string const &asset_symbol, std::string const &id) {
    std::string const stream_name = asset_symbol.size() ? asset_symbol + "@assetIndex" : "!assetIndex@arr";

    ws_market_send_request(_websocket_market_streams, stream_name, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::ws_market_streams_multiple_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &streams, std::string const &id) {
    ws_market_send_request(_websocket_market_streams, streams, wsms_method, id);
}

//-------------------------------------------------------------------------------------

void API::ws_market_streams_list_subscriptions(std::string const &id) const {

    if(id.empty()) {
        _websocket_market_streams->list_subscriptions(std::to_string(get_timestamp()));
    }
    else {
        _websocket_market_streams->list_subscriptions(id);
    }
}

//-------------------------------------------------------------------------------------
