
//------------------------------------------------------------------------------------

#include "trade.hpp"
#include "trade_parsing_simdjson.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------

NewOrderResponse API::new_order(Trade::NewOrder const &order, bool const close_position, int32_t const recv_window) {
    std::string const url = "/fapi/v1/order";

    Parameters params;
    params.emplace_back("symbol", order.symbol);
    params.emplace_back("side", order.side);
    params.emplace_back("type", order.type);
    if (order.position_side != "") params.emplace_back("positionSide", order.position_side);
    if (order.price != -1) params.emplace_back("price", order.price);
    if (order.quantity != -1) params.emplace_back("quantity", order.quantity);
    if (order.time_in_force != "") params.emplace_back("timeInForce", order.time_in_force);
    if (order.stop_price != -1) params.emplace_back("stopPrice", order.stop_price);
    if (order.new_client_order_id != "") params.emplace_back("newClientOrderId", order.new_client_order_id);
    if (order.activation_price != -1) params.emplace_back("activationPrice", order.activation_price);
    if (order.callback_rate != -1) params.emplace_back("callbackRate", order.callback_rate);
    if (order.working_type != "") params.emplace_back("workingType", order.working_type);
    if (order.new_order_resp_type != "") params.emplace_back("newOrderRespType", order.new_order_resp_type);
    if (order.price_match != "") params.emplace_back("priceMatch", order.price_match);
    if (order.self_trade_prevention_mode != "") params.emplace_back("selfTradePrevention", order.self_trade_prevention_mode);
    if (order.good_till_date != -1) params.emplace_back("goodTillDate", order.good_till_date);
    if (order.reduce_only) params.emplace_back("reduceOnly", order.reduce_only);
    if (order.price_protect) params.emplace_back("priceProtect", order.price_protect);
    if (close_position) params.emplace_back("closePosition", close_position);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response<NewOrderObject>(response);
}

PlaceMultipleOrdersResponse API::place_multiple_orders(std::vector<Trade::NewOrder> const &orders, int32_t const recv_window) {
    std::string const url = "/fapi/v1/batchOrders";

    Parameters params;
    params.emplace_back("batchOrders", orders_to_json(orders));
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response<PlaceMultipleOrdersObject>(response, API::ArrayErrors{});
}

ModifyOrderResponse API::modify_order(Trade::ModifyOrder const &order, int32_t const recv_window) {
    std::string const url = "/fapi/v1/order";

    Parameters params;
    params.emplace_back("symbol", order.symbol);
    params.emplace_back("side", order.side);
    params.emplace_back("quantity", order.quantity);
    params.emplace_back("price", order.price);
    if (order.order_id != -1) params.emplace_back("orderId", order.order_id);
    if (order.orig_client_order_id != "") params.emplace_back("origClientOrderId", order.orig_client_order_id);
    if (order.price_match != "") params.emplace_back("priceMatch", order.price_match);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::PUT>(url, params);

    return parse_response<ModifyOrderObject>(response);
}

ModifyMultipleOrdersResponse API::modify_multiple_orders(std::vector<Trade::ModifyOrder> const &orders, int32_t const recv_window) {
    std::string const url = "/fapi/v1/batchOrders";

    Parameters params;
    params.emplace_back("batchOrders", orders_to_json(orders));
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::PUT>(url, params);

    return parse_response<ModifyMultipleOrdersObject>(response, API::ArrayErrors{});
}

GetOrderModifyHistoryResponse API::get_order_modify_history(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int64_t const start_time, int64_t const end_time, int8_t const limit, int32_t const recv_window) {
    std::string const url = "/fapi/v1/orderAmendment";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (order_id != -1) params.emplace_back("orderId", order_id);
    if (orig_client_order_id != "") params.emplace_back("origClientOrderId", orig_client_order_id);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<GetOrderModifyHistoryObject>(response);
}

CancelOrderResponse API::cancel_order(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/order";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (order_id != -1) params.emplace_back("orderId", order_id);
    if (orig_client_order_id != "") params.emplace_back("origClientOrderId", orig_client_order_id);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::DELETE>(url, params);

    return parse_response<CancelOrderObject>(response);
}

CancelMultipleOrdersResponse API::cancel_multiple_orders(std::string const &symbol, std::vector<int64_t> const &order_ids, std::vector<std::string> const &orig_client_order_ids, int32_t const recv_window) {
    std::string const url = "/fapi/v1/batchOrders";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (!order_ids.empty()) params.emplace_back("orderList", data_to_list(order_ids));
    if (!orig_client_order_ids.empty()) params.emplace_back("origClientOrderIdList", data_to_list(orig_client_order_ids));
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::DELETE>(url, params);

    return parse_response<CancelMultipleOrdersObject>(response, API::ArrayErrors{});
}

CancelAllOpenOrdersResponse API::cancel_all_open_orders(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v1/allOpenOrders";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::DELETE>(url, params);

    return parse_response(response, API::ResponseIsServerMessage{});
}

AutoCancelAllOpenOrdersResponse API::auto_cancel_all_open_orders(std::string const &symbol, int64_t const countdown_time, int32_t const recv_window) {
    std::string const url = "/fapi/v1/countdownCancelAll";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("countdownTime", countdown_time);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response<AutoCancelAllOpenOrdersObject>(response);
}

QueryOrderResponse API::query_order(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/order";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (order_id != -1) params.emplace_back("orderId", order_id);
    if (orig_client_order_id != "") params.emplace_back("origClientOrderId", orig_client_order_id);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<QueryOrderObject>(response);
}

QueryAllOrdersResponse API::query_all_orders(std::string const &symbol, int64_t const order_id, int64_t const start_time, int64_t const end_time, int16_t const limit, int32_t const recv_window) {
    std::string const url = "/fapi/v1/allOrders";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (order_id != -1) params.emplace_back("orderId", order_id);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<QueryAllOrdersObject>(response);
}

QueryCurrentAllOpenOrdersResponse API::query_current_all_open_orders(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v1/openOrders";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<QueryCurrentAllOpenOrdersObject>(response);
}

QueryCurrentOpenOrderResponse API::query_current_open_order(std::string const &symbol, int64_t const order_id, std::string const orig_client_order_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/openOrder";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (order_id != -1) params.emplace_back("orderId", order_id);
    if (orig_client_order_id != "") params.emplace_back("origClientOrderId", orig_client_order_id);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<QueryCurrentOpenOrderObject>(response);
}

QueryUsersForceOrdersResponse API::query_users_force_orders(std::string const &symbol, std::string const &auto_close_type, int64_t const start_time, int64_t const end_time, int8_t const limit, int32_t const recv_window) {
    std::string const url = "/fapi/v1/forceOrders";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (auto_close_type != "") params.emplace_back("autoCloseType", auto_close_type);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<QueryUsersForceOrdersObject>(response);
}

QueryAccountTradeListResponse API::query_account_trade_list(std::string const &symbol, int64_t const order_id, int64_t const start_time, int64_t const end_time, int64_t const from_id, int16_t const limit, int32_t const recv_window) {
    std::string const url = "/fapi/v1/userTrades";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (order_id != -1) params.emplace_back("orderId", order_id);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (from_id != -1) params.emplace_back("fromId", from_id);
    if (limit != -1) params.emplace_back("limit", limit);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<QueryAccountTradeListObject>(response);
}

ChangeMarginTypeResponse API::change_margin_type(std::string const &symbol, std::string const &margin_type, int32_t const recv_window) {
    std::string const url = "/fapi/v1/marginType";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("marginType", margin_type);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response(response, API::ResponseIsServerMessage{});
}

ChangePositionModeResponse API::change_position_mode(std::string const &dual_side_position, int32_t const recv_window) {
    std::string const url = "/fapi/v1/positionSide/dual";

    Parameters params;
    params.emplace_back("dualSidePosition", dual_side_position);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response(response, API::ResponseIsServerMessage{});
}

ChangeInitialLeverageResponse API::change_initial_leverage(std::string const &symbol, int8_t const leverage, int32_t const recv_window) {
    std::string const url = "/fapi/v1/leverage";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("leverage", leverage);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response<ChangeInitialLeverageObject>(response);
}

ChangeMultiAssetsModeResponse API::change_multi_assets_mode(std::string const &multi_assets_margin, int32_t const recv_window) {
    std::string const url = "/fapi/v1/multiAssetsMargin";

    Parameters params;
    params.emplace_back("multiAssetsMargin", multi_assets_margin);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response(response, API::ResponseIsServerMessage{});
}

ModifyIsolatedPositionMarginResponse API::modify_isolated_position_margin(std::string const &symbol, double const amount, int8_t const type, std::string const &position_side, int32_t const recv_window) {
    std::string const url = "/fapi/v1/positionMargin";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("amount", amount);
    params.emplace_back("type", type);
    if (position_side != "") params.emplace_back("positionSide", position_side);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response<ModifyIsolatedPositionMarginObject>(response);
}

PositionInformationV2Response API::position_information_v2(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v2/positionRisk";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<PositionInformationV2Object>(response);
}

PositionInformationV3Response API::position_information_v3(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v3/positionRisk";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<PositionInformationV3Object>(response);
}

PositionAdlQuantileEstimationResponse API::position_adl_quantile_estimation(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v1/adlQuantile";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<PositionAdlQuantileEstimationObject>(response);
}

GetPositionMarginChangeHistoryResponse API::get_position_margin_change_history(std::string const &symbol, int8_t const type, int64_t const start_time, int64_t const end_time, int32_t const limit, int32_t const recv_window) {
    std::string const url = "/fapi/v1/positionMargin/history";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (type != -1) params.emplace_back("type", type);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<GetPositionMarginChangeHistoryObject>(response);
}

TestNewOrderResponse API::test_new_order(Trade::NewOrder const &order, bool const close_position, int32_t const recv_window) {
    std::string const url = "/fapi/v1/order/test";

    Parameters params;
    params.emplace_back("symbol", order.symbol);
    params.emplace_back("side", order.side);
    params.emplace_back("type", order.type);
    if (order.position_side != "") params.emplace_back("positionSide", order.position_side);
    if (order.price != -1) params.emplace_back("price", order.price);
    if (order.quantity != -1) params.emplace_back("quantity", order.quantity);
    if (order.time_in_force != "") params.emplace_back("timeInForce", order.time_in_force);
    if (order.stop_price != -1) params.emplace_back("stopPrice", order.stop_price);
    if (order.new_client_order_id != "") params.emplace_back("newClientOrderId", order.new_client_order_id);
    if (order.activation_price != -1) params.emplace_back("activationPrice", order.activation_price);
    if (order.callback_rate != -1) params.emplace_back("callbackRate", order.callback_rate);
    if (order.working_type != "") params.emplace_back("workingType", order.working_type);
    if (order.new_order_resp_type != "") params.emplace_back("newOrderRespType", order.new_order_resp_type);
    if (order.price_match != "") params.emplace_back("priceMatch", order.price_match);
    if (order.self_trade_prevention_mode != "") params.emplace_back("selfTradePrevention", order.self_trade_prevention_mode);
    if (order.good_till_date != -1) params.emplace_back("goodTillDate", order.good_till_date);
    if (order.reduce_only) params.emplace_back("reduceOnly", order.reduce_only);
    if (order.price_protect) params.emplace_back("priceProtect", order.price_protect);
    if (close_position) params.emplace_back("closePosition", close_position);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::POST>(url, params);

    return parse_response<TestNewOrderObject>(response);
}

//------------------------------------------------------------------------------------
