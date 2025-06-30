
//------------------------------------------------------------------------------------

#include "websocket_market_streams.hpp"
#include "websocket_market_streams_parsing_simdjson.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------
//------------------------Handle Websocket Market Stream Event------------------------
//------------------------------------------------------------------------------------

static API::MarketDataStreamEventTypes ws_market_streams_detect_event_type(simdjson::ondemand::value val) {

    bool const is_array = (val.type() == simdjson::ondemand::json_type::array);
    simdjson::ondemand::object obj;
    if (is_array) {
        simdjson::ondemand::array arr;
        {auto error = val.get_array().get(arr); DEBUG_ASSERT(!error);}
        for (auto item : arr) {
            {auto error = item.get_object().get(obj); DEBUG_ASSERT(!error);}
            break;
        }
    }
    else {
        {auto error = val.get_object().get(obj); DEBUG_ASSERT(!error);}
    }

    std::string_view event_type;
    auto error = obj.find_field("e").get_string().get(event_type);
    if (error) return API::MarketDataStreamEventTypes::SERVER_MESSAGE;

    if (event_type == "aggTrade") {
        return API::MarketDataStreamEventTypes::AGG_TRADE;
    }
    else if (event_type == "markPriceUpdate") {
        return is_array ? API::MarketDataStreamEventTypes::MARK_PRICE_UPDATE_ALL : API::MarketDataStreamEventTypes::MARK_PRICE_UPDATE;
    }
    else if (event_type == "kline") {
        return API::MarketDataStreamEventTypes::KLINE;
    }
    else if (event_type == "continuous_kline") {
        return API::MarketDataStreamEventTypes::CONTINUOUS_KLINE;
    }
    else if (event_type == "24hrMiniTicker") {
        return is_array ? API::MarketDataStreamEventTypes::MINI_TICKER_24H_ALL : API::MarketDataStreamEventTypes::MINI_TICKER_24H;
    }
    else if (event_type == "24hrTicker") {
        return is_array ? API::MarketDataStreamEventTypes::TICKER_24H_ALL : API::MarketDataStreamEventTypes::TICKER_24H;
    }
    else if (event_type == "bookTicker") {
        return API::MarketDataStreamEventTypes::BOOK_TICKER;
    }
    else if (event_type == "forceOrder") {
        return API::MarketDataStreamEventTypes::FORCE_ORDER;
    }
    else if (event_type == "depthUpdate") {
        return API::MarketDataStreamEventTypes::DEPTH_UPDATE_PARTIAL;
    }
    else if (event_type == "compositeIndex") {
        return API::MarketDataStreamEventTypes::COMPOSITE_INDEX;
    }
    else if (event_type == "contractInfo") {
        return API::MarketDataStreamEventTypes::CONTRACT_INFO;
    }
    else if (event_type == "assetIndexUpdate") {
        return API::MarketDataStreamEventTypes::ASSET_INDEX_UPDATE;
    }
    else {
        return API::MarketDataStreamEventTypes::SERVER_MESSAGE;
    }
}

//------------------------------------------------------------------------------------

API::MarketDataStreamResponse API::ws_market_streams_parse_response(std::string &response) {

    simdjson::ondemand::document doc;
    {auto error = _parser.iterate(response).get(doc); DEBUG_ASSERT(!error);}

    MarketDataStreamEventTypes const event_type = ws_market_streams_detect_event_type(doc);
    doc.rewind();

    switch (event_type) {
    case MarketDataStreamEventTypes::SERVER_MESSAGE: 
    {
        ServerMessageResponse server_message;
        {auto error = doc.get(server_message); DEBUG_ASSERT(!error);}
        return server_message;
    }
    case MarketDataStreamEventTypes::AGG_TRADE: 
    {
        AggregateTradeStreamObject agg_trade;
        {auto error = doc.get(agg_trade); DEBUG_ASSERT(!error);}
        return agg_trade;
    }
    case MarketDataStreamEventTypes::MARK_PRICE_UPDATE: 
    {
        MarkPriceStreamObject mark_price;
        {auto error = doc.get(mark_price); DEBUG_ASSERT(!error);}
        return mark_price;
    }
    case MarketDataStreamEventTypes::MARK_PRICE_UPDATE_ALL: 
    {
        MarkPriceStreamForAllMarketStreamObject mark_price_all;
        {auto error = doc.get(mark_price_all); DEBUG_ASSERT(!error);}
        return mark_price_all;
    }
    case MarketDataStreamEventTypes::KLINE: 
    {
        KLineStreamObject kline;
        {auto error = doc.get(kline); DEBUG_ASSERT(!error);}
        return kline;
    }
    case MarketDataStreamEventTypes::CONTINUOUS_KLINE: 
    {
        ContinuousKLineStreamObject continuous_kline;
        {auto error = doc.get(continuous_kline); DEBUG_ASSERT(!error);}
        return continuous_kline;
    }
    case MarketDataStreamEventTypes::MINI_TICKER_24H: 
    {
        MiniTicker24hrStreamObject mini_ticker;
        {auto error = doc.get(mini_ticker); DEBUG_ASSERT(!error);}
        return mini_ticker;
    }
    case MarketDataStreamEventTypes::MINI_TICKER_24H_ALL: 
    {
        MiniTickerAll24hrStreamObject mini_ticker_all;
        {auto error = doc.get(mini_ticker_all); DEBUG_ASSERT(!error);}
        return mini_ticker_all;
    }
    case MarketDataStreamEventTypes::TICKER_24H: 
    {
        Ticker24hrStreamObject ticker;
        {auto error = doc.get(ticker); DEBUG_ASSERT(!error);}
        return ticker;
    }
    case MarketDataStreamEventTypes::TICKER_24H_ALL: 
    {
        TickerAll24hrStreamObject ticker_all;
        {auto error = doc.get(ticker_all); DEBUG_ASSERT(!error);}
        return ticker_all;
    }
    case MarketDataStreamEventTypes::BOOK_TICKER: 
    {
        BookTickerStreamObject book_ticker;
        {auto error = doc.get(book_ticker); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::BOOK_TICKER)>, std::move(book_ticker));
    }
    case MarketDataStreamEventTypes::BOOK_TICKER_ALL: 
    {
        BookTickerAllStreamObject book_ticker_all;
        {auto error = doc.get(book_ticker_all); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::BOOK_TICKER_ALL)>, std::move(book_ticker_all));
    }
    case MarketDataStreamEventTypes::FORCE_ORDER: 
    {
        ForceOrderStreamObject force_order;
        {auto error = doc.get(force_order); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::FORCE_ORDER)>, std::move(force_order));
    }
    case MarketDataStreamEventTypes::FORCE_ORDER_ALL: 
    {
        ForceOrderAllStreamObject force_order_all;
        {auto error = doc.get(force_order_all); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::FORCE_ORDER_ALL)>, std::move(force_order_all));
    }
    case MarketDataStreamEventTypes::DEPTH_UPDATE_PARTIAL: 
    {
        DepthUpdatePartialStreamObject depth_update_partial;
        {auto error = doc.get(depth_update_partial); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::DEPTH_UPDATE_PARTIAL)>, std::move(depth_update_partial));
    }
    case MarketDataStreamEventTypes::DEPTH_UPDATE_DIFF: 
    {
        DepthUpdateDiffStreamObject depth_update_diff;
        {auto error = doc.get(depth_update_diff); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::DEPTH_UPDATE_DIFF)>, std::move(depth_update_diff));
    }
    case MarketDataStreamEventTypes::COMPOSITE_INDEX: 
    {
        CompositeIndexStreamObject composite_index;
        {auto error = doc.get(composite_index); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::COMPOSITE_INDEX)>, std::move(composite_index));
    }
    case MarketDataStreamEventTypes::CONTRACT_INFO: 
    {
        ContractInfoStreamObject contract_info;
        {auto error = doc.get(contract_info); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::CONTRACT_INFO)>, std::move(contract_info));
    }
    case MarketDataStreamEventTypes::ASSET_INDEX_UPDATE: 
    {
        AssetIndexUpdateStreamObject asset_index_update;
        {auto error = doc.get(asset_index_update); DEBUG_ASSERT(!error);}
        return MarketDataStreamResponse(std::in_place_index<static_cast<uint8_t>(MarketDataStreamEventTypes::ASSET_INDEX_UPDATE)>, std::move(asset_index_update));
    }
    default: 
    {
        ServerMessageResponse server_message;
        server_message.code = -1; // Unknown event type
        server_message.msg = "Unknown market data stream event type";
        return server_message;
    }
    }
}

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
