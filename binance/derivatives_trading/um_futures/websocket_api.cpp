
//------------------------------------------------------------------------------------

#include "websocket_api.hpp"

#include "api.hpp"
#include "authentication.hpp"

#include "account_parsing_simdjson.hpp"
#include "convert_parsing_simdjson.hpp"
#include "market_data_parsing_simdjson.hpp"
#include "portfolio_margin_endpoints_parsing_simdjson.hpp"
#include "trade_parsing_simdjson.hpp"

//------------------------------------------------------------------------------------
//----------------------------Handle WebSocket API Response---------------------------
//------------------------------------------------------------------------------------

API::WebsocketAPIResponse API::ws_api_parse_response(std::string &response) {

    simdjson::ondemand::document doc;
    {auto error = _parser.iterate(response).get(doc); DEBUG_ASSERT(!error);}

    simdjson::ondemand::object obj;
    {auto error = doc.get_object().get(obj); DEBUG_ASSERT(!error);}

    uint8_t id = 0;
    {auto error = simdjson_get_value_field_name(obj, "id", id); DEBUG_ASSERT(!error);}

    uint16_t status = 0;
    {auto error = simdjson_get_value_field_name(obj, "status", status); DEBUG_ASSERT(!error);}
    if(status != 200) {
        ServerMessageResponse server_message;
        {auto error = obj.find_field("error").get<ServerMessageResponse>().get(server_message); DEBUG_ASSERT(!error);}
        return server_message;
    }

    switch(id) {
        case 'i':
        case 's':
        case 'o':
        {
            SessionStreamObject session_response;
            {auto error = obj.find_field("result").get<SessionStreamObject>().get(session_response); DEBUG_ASSERT(!error);}
            return session_response;
        }
        case '1':
        {
            Account::FuturesAccountBalanceV2StreamObject futures_account_balance_response;
            {auto error = obj.find_field("result").get<Account::FuturesAccountBalanceV2StreamObject>().get(futures_account_balance_response); DEBUG_ASSERT(!error);}
            return WebsocketAPIResponse(std::in_place_index<static_cast<uint8_t>(WebsocketAPIResponseTypes::FUTURES_ACCOUNT_BALANCE_V2)-'0'>, std::move(futures_account_balance_response));
        }
        case '2':
        {
            Account::FuturesAccountBalanceStreamObject futures_account_balance_response;
            {auto error = obj.find_field("result").get<Account::FuturesAccountBalanceStreamObject>().get(futures_account_balance_response); DEBUG_ASSERT(!error);}
            return WebsocketAPIResponse(std::in_place_index<static_cast<uint8_t>(WebsocketAPIResponseTypes::FUTURES_ACCOUNT_BALANCE)-'0'>, std::move(futures_account_balance_response));
        }
        case '3':
        {
            Account::AccountInformationV2StreamObject account_information_v3_response;
            {auto error = obj.find_field("result").get<Account::AccountInformationV2StreamObject>().get(account_information_v3_response); DEBUG_ASSERT(!error);}
            return account_information_v3_response;
        }
        case '4':
        {
            Account::AccountInformationStreamObject account_information_response;
            {auto error = obj.find_field("result").get<Account::AccountInformationStreamObject>().get(account_information_response); DEBUG_ASSERT(!error);}
            return account_information_response;
        }
        case '5':
        {
            MarketData::OrderBookStreamObject order_book_response;
            {auto error = obj.find_field("result").get<MarketData::OrderBookStreamObject>().get(order_book_response); DEBUG_ASSERT(!error);}
            return order_book_response;
        }
        case '6':
        {
            MarketData::SymbolPriceTickerStreamObject symbol_price_ticker_response;
            {auto error = obj.find_field("result").get<MarketData::SymbolPriceTickerStreamObject>().get(symbol_price_ticker_response); DEBUG_ASSERT(!error);}
            return symbol_price_ticker_response;
        }
        case '7':
        {
            MarketData::SymbolOrderBookTickerStreamObject symbol_order_book_ticker_response;
            {auto error = obj.find_field("result").get<MarketData::SymbolOrderBookTickerStreamObject>().get(symbol_order_book_ticker_response); DEBUG_ASSERT(!error);}
            return symbol_order_book_ticker_response;
        }
        case '8':
        {
            Trade::NewOrderStreamObject new_order_response;
            {auto error = obj.find_field("result").get<Trade::NewOrderStreamObject>().get(new_order_response); DEBUG_ASSERT(!error);}
            return new_order_response;
        }
        case '9':
        {
            Trade::ModifyOrderStreamObject modify_order_response;
            {auto error = obj.find_field("result").get<Trade::ModifyOrderStreamObject>().get(modify_order_response); DEBUG_ASSERT(!error);}
            return modify_order_response;
        }
        case 'a':
        {
            Trade::CancelOrderStreamObject cancel_order_response;
            {auto error = obj.find_field("result").get<Trade::CancelOrderStreamObject>().get(cancel_order_response); DEBUG_ASSERT(!error);}
            return cancel_order_response;
        }
        case 'b':
        {
            Trade::QueryOrderStreamObject query_order_response;
            {auto error = obj.find_field("result").get<Trade::QueryOrderStreamObject>().get(query_order_response); DEBUG_ASSERT(!error);}
            return query_order_response;
        }
        case 'c':
        {
            Trade::PositionInformationV2StreamObject position_information_v2_response;
            {auto error = obj.find_field("result").get<Trade::PositionInformationV2StreamObject>().get(position_information_v2_response); DEBUG_ASSERT(!error);}
            return position_information_v2_response;
        }
        case 'd':
        {
            Trade::PositionInformationStreamObject position_information_response;
            {auto error = obj.find_field("result").get<Trade::PositionInformationStreamObject>().get(position_information_response); DEBUG_ASSERT(!error);}
            return position_information_response;
        }
        default:
            DEBUG_ASSERT(false && "Unknown WebSocket API response ID");
            return ServerMessageResponse{0, "Unknown WebSocket API response ID"};
    }
}

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

    Parameters sign_params{
        {"apiKey", ed25519_api_key()},
        {"timestamp", get_timestamp()}
    };
    sign_params.emplace_back("signature", ed25519_signature(ed25519_private_key(), prepare_query_string(sign_params), ed25519_private_key_passphrase()));

    Parameters const request_params{
        {"id", 'i'},
        {"method", "session.logon"},
        {"params", prepare_json_string(sign_params)}
    };
    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::ws_api_session_status() {

    Parameters const request_params{
        {"id", 's'},
        {"method", "session.status"},
    };
    _websocket_api->send_message(prepare_json_string(request_params));
}

//------------------------------------------------------------------------------------

void API::ws_api_session_logout() {

    Parameters const request_params{
        {"id", 'o'},
        {"method", "session.logout"},
    };
    _websocket_api->send_message(prepare_json_string(request_params));
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

void API::futures_account_balance_v2_stream(int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "v2/account.balance";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    params.emplace_back("timestamp", get_timestamp());
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", '1'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::futures_account_balance_stream(int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "v1/account.balance";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();
    
    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    params.emplace_back("timestamp", get_timestamp());
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));
    
    Parameters const request_params{
        {"id", '2'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::account_information_v2_stream(int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "v2/account.status";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    params.emplace_back("timestamp", get_timestamp());
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));
    
    Parameters const request_params{
        {"id", '3'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::account_information_stream(int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "v1/account.status";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    params.emplace_back("timestamp", get_timestamp());
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", '4'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------
//-------------------------------------Market Data------------------------------------
//------------------------------------------------------------------------------------

void API::order_book_stream(std::string const &symbol, int16_t const &limit) {
    std::string const method = "depth";

    Parameters params;
    if(limit != -1) params.emplace_back("limit", limit);
    params.emplace_back("symbol", symbol);

    Parameters const request_params{
        {"id", '5'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::symbol_price_ticker_stream(std::string const &symbol) {
    std::string const method = "ticker.price";

    Parameters params;
    if(!symbol.empty()) params.emplace_back("symbol", symbol);

    Parameters const request_params{
        {"id", '6'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::symbol_order_book_ticker_stream(std::string const &symbol) {
    std::string const method = "ticker.book";

    Parameters params;
    if(!symbol.empty()) params.emplace_back("symbol", symbol);

    Parameters const request_params{
        {"id", '7'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------
//----------------------------------------Trade---------------------------------------
//------------------------------------------------------------------------------------

void API::new_order_stream(Trade::NewOrder const &order, bool const close_position, int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "order.place";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(order.activation_price != -1) params.emplace_back("activationPrice", order.activation_price);
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    if(order.callback_rate != -1) params.emplace_back("callbackRate", order.callback_rate);
    params.emplace_back("closePosition", close_position);
    if(order.good_till_date != -1) params.emplace_back("goodTillDate", order.good_till_date);
    if(!order.new_client_order_id.empty()) params.emplace_back("newClientOrderId", order.new_client_order_id);
    if(!order.new_order_resp_type.empty()) params.emplace_back("newOrderRespType", order.new_order_resp_type);
    if(!order.position_side.empty()) params.emplace_back("positionSide", order.position_side);
    if(order.price != -1) params.emplace_back("price", order.price);
    if(!order.price_match.empty()) params.emplace_back("priceMatch", order.price_match);
    if(order.price_protect) params.emplace_back("priceProtect", true);
    if(order.quantity != -1) params.emplace_back("quantity", order.quantity);
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    if(order.reduce_only) params.emplace_back("reduceOnly", true);
    if(!order.self_trade_prevention_mode.empty()) params.emplace_back("selfTradePreventionMode", order.self_trade_prevention_mode);
    params.emplace_back("side", order.side);
    if(order.stop_price != -1) params.emplace_back("stopPrice", order.stop_price);
    params.emplace_back("symbol", order.symbol);
    if(!order.time_in_force.empty()) params.emplace_back("timeInForce", order.time_in_force);
    params.emplace_back("timestamp", get_timestamp());
    params.emplace_back("type", order.type);
    if(!order.working_type.empty()) params.emplace_back("workingType", order.working_type);

    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", '8'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::modify_order_stream(Trade::ModifyOrder const &order, int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "order.modify";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    if(order.order_id != -1) params.emplace_back("orderId", order.order_id);
    if(!order.orig_client_order_id.empty()) params.emplace_back("origClientOrderId", order.orig_client_order_id);
    if(order.price != -1) params.emplace_back("price", order.price);
    if(!order.price_match.empty()) params.emplace_back("priceMatch", order.price_match);
    if(order.quantity != -1) params.emplace_back("quantity", order.quantity);
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    params.emplace_back("side", order.side);
    params.emplace_back("symbol", order.symbol);
    params.emplace_back("timestamp", get_timestamp());

    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", '9'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::cancel_order_stream(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "order.cancel";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    if(order_id != -1) params.emplace_back("orderId", order_id);
    if(!orig_client_order_id.empty()) params.emplace_back("origClientOrderId", orig_client_order_id);
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    params.emplace_back("symbol", symbol);
    params.emplace_back("timestamp", get_timestamp());

    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", 'a'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::query_order_stream(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "order.status";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    if(order_id != -1) params.emplace_back("orderId", order_id);
    if(!orig_client_order_id.empty()) params.emplace_back("origClientOrderId", orig_client_order_id);
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    params.emplace_back("symbol", symbol);
    params.emplace_back("timestamp", get_timestamp());

    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", 'b'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::position_information_v2_stream(std::string const &symbol, int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "v2/account.position";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    if(!symbol.empty()) params.emplace_back("symbol", symbol);
    params.emplace_back("timestamp", get_timestamp());

    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", 'c'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------

void API::position_information_stream(std::string const &symbol, int32_t const recv_window, std::string const &hmac_api_key, std::string const &hmac_api_secret) {
    std::string const method = "account.position";

    bool const ad_hoc_request = !hmac_api_key.empty() && !hmac_api_secret.empty();

    Parameters params;
    if(ad_hoc_request) params.emplace_back("apiKey", hmac_api_key);
    if(recv_window != -1) params.emplace_back("recvWindow", recv_window);
    if(!symbol.empty()) params.emplace_back("symbol", symbol);
    params.emplace_back("timestamp", get_timestamp());

    if(ad_hoc_request) params.emplace_back("signature", hmac_signature(hmac_api_secret, prepare_query_string(params)));

    Parameters const request_params{
        {"id", 'd'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------
