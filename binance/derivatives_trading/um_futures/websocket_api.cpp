
//------------------------------------------------------------------------------------

#include "websocket_api.hpp"

#include "api.hpp"
#include "authentication.hpp"

//------------------------------------------------------------------------------------
//----------------------------------Simdjson Parsing----------------------------------
//------------------------------------------------------------------------------------

namespace simdjson {

using namespace Trade;

// ---------- Session Responses ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SessionObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "apiKey", response.api_key)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "authorizedSince", response.authorized_since)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "connectedSince", response.connected_since)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "returnRateLimits", response.return_rate_limits)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "serverTime", response.server_time)) return error;

    return SUCCESS;
}
// ---------------------------------------

// ---------- New Order Stream ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, NewOrderStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", response.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", response.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", response.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", response.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", response.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQuote", response.cum_quote)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", response.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "reduceOnly", response.reduce_only)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "closePosition", response.close_position)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "side", response.side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", response.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "stopPrice", response.stop_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", response.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceProtect", response.price_protect)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origType", response.orig_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceMatch", response.price_match)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "selfTradePreventionMode", response.self_trade_prevention_mode)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "goodTillDate", response.good_till_date)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    
    return SUCCESS;
}
// --------------------------------------

// ---------- Modify Order Stream ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ModifyOrderStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", response.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", response.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", response.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", response.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", response.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQuote", response.cum_quote)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", response.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "reduceOnly", response.reduce_only)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "closePosition", response.close_position)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "side", response.side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", response.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "stopPrice", response.stop_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", response.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceProtect", response.price_protect)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origType", response.orig_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceMatch", response.price_match)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "selfTradePreventionMode", response.self_trade_prevention_mode)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "goodTillDate", response.good_till_date)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;

    return SUCCESS;
}
// -----------------------------------------

// ---------- Query Order Stream ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryOrderStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", response.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQuote", response.cum_quote)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", response.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", response.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origType", response.orig_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", response.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "reduceOnly", response.reduce_only)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "side", response.side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", response.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", response.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "stopPrice", response.stop_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "closePosition", response.close_position)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", response.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", response.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "activatePrice", response.activate_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceRate", response.price_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", response.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceProtect", response.price_protect)) return error;

    return SUCCESS;
}
// ----------------------------------------

} // namespace simdjson

//------------------------------------------------------------------------------------

void API::ws_api_parse_response(std::string &response) {

    simdjson::ondemand::document doc;
    {auto error = _parser.iterate(response).get(doc); DEBUG_ASSERT(!error);}

    simdjson::ondemand::object obj;
    {auto error = doc.get_object().get(obj); DEBUG_ASSERT(!error);}

    uint8_t id = 0;
    {auto error = simdjson_get_value_field_name(obj, "id", id); DEBUG_ASSERT(!error);}

    uint16_t status = 0;
    {auto error = simdjson_get_value_field_name(obj, "status", status); DEBUG_ASSERT(!error);}
    if(status != 200) {
        std::optional<ServerMessageResponse> server_message;
        {auto error = obj.find_field("error").get<std::optional<ServerMessageResponse>>().get(server_message); DEBUG_ASSERT(!error);}
        //DO SOMETHING WITH THE SERVER MESSAGE
    }

    switch(id) {
        case 'i':
        case 's':
        case 'o':
        {
            SessionObject session_response;
            {auto error = obj.find_field("result").get<SessionObject>().get(session_response); DEBUG_ASSERT(!error);}
            break;            
        }
        case '0':
        case '1':
        {
            Account::FuturesAccountBalanceObject futures_account_balance_response;
            {auto error = obj.find_field("result").get<Account::FuturesAccountBalanceObject>().get(futures_account_balance_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '2':
        {
            Account::AccountInformationV3Object account_information_v3_response;
            {auto error = obj.find_field("result").get<Account::AccountInformationV3Object>().get(account_information_v3_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '3':
        {
            Account::AccountInformationObject account_information_response;
            {auto error = obj.find_field("result").get<Account::AccountInformationObject>().get(account_information_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '4':
        {
            MarketData::OrderBookObject order_book_response;
            {auto error = obj.find_field("result").get<MarketData::OrderBookObject>().get(order_book_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '5':
        {
            MarketData::SymbolPriceTickerObject symbol_price_ticker_response;
            {auto error = obj.find_field("result").get<MarketData::SymbolPriceTickerObject>().get(symbol_price_ticker_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '6':
        {
            MarketData::SymbolOrderBookTickerObject symbol_order_book_ticker_response;
            {auto error = obj.find_field("result").get<MarketData::SymbolOrderBookTickerObject>().get(symbol_order_book_ticker_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '7':
        {
            Trade::NewOrderStreamObject new_order_response;
            {auto error = obj.find_field("result").get<Trade::NewOrderStreamObject>().get(new_order_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '8':
        {
            Trade::ModifyOrderStreamObject modify_order_response;
            {auto error = obj.find_field("result").get<Trade::ModifyOrderStreamObject>().get(modify_order_response); DEBUG_ASSERT(!error);}
            break;
        }
        case '9':
        {
            Trade::CancelOrderObject cancel_order_response;
            {auto error = obj.find_field("result").get<Trade::CancelOrderObject>().get(cancel_order_response); DEBUG_ASSERT(!error);}
            break;
        }
        case 'a':
        {
            Trade::QueryOrderStreamObject query_order_response;
            {auto error = obj.find_field("result").get<Trade::QueryOrderStreamObject>().get(query_order_response); DEBUG_ASSERT(!error);}
            break;
        }
        case 'b':
        {
            Trade::PositionInformationV3Object position_information_v2_response;
            {auto error = obj.find_field("result").get<Trade::PositionInformationV3Object>().get(position_information_v2_response); DEBUG_ASSERT(!error);}
            break;
        }
        case 'c':
        {
            Trade::PositionInformationV2Object position_information_response;
            {auto error = obj.find_field("result").get<Trade::PositionInformationV2Object>().get(position_information_response); DEBUG_ASSERT(!error);}
            break;
        }
        default:
            break;
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
        {"id", '0'},
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
        {"id", '1'},
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
        {"id", '2'},
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
        {"id", '3'},
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
        {"id", '4'},
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
        {"id", '5'},
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
        {"id", '6'},
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
        {"id", '7'},
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
        {"id", '8'},
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
        {"id", '9'},
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
        {"id", 'a'},
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
        {"id", 'b'},
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
        {"id", 'c'},
        {"method", method},
        {"params", prepare_json_string(params)}
    };

    _websocket_api->send_message(prepare_json_string(request_params, true));
}

//------------------------------------------------------------------------------------
