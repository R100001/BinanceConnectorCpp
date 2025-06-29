
//-----------------------------------------------------------------------------

#ifndef TRADE_PARSING_SIMDJSON_HPP
#define TRADE_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------

#include "trade.hpp"

#include "api.hpp"
#include "utils.hpp"

//------------------------------------------------------------------------------------

using namespace Trade;

//------------------------------------------------------------------------------------

// Helper Functions

static void remove_last_comma(std::stringstream &ss) {
    std::streampos endPos = ss.tellp();
    
    if (endPos > 0) {
        ss.seekg(-1, std::ios_base::end);
        char lastChar = ss.get();
        
        if (lastChar == ',') {
            ss.seekp(-1, std::ios_base::end);
        }
    }
}

static std::string orders_to_json(std::vector<NewOrder> const &orders) {

    if (orders.empty()) return "";

    std::stringstream ss;
    ss << "[";

    for(NewOrder const order : orders) {
        ss << "{";
        
        ss << "\"symbol\":\"" << order.symbol << "\",";
        ss << "\"side\":\"" << order.side << "\",";
        ss << "\"type\":\"" << order.type << "\",";
        ss << "\"quantity\":" << order.quantity << ",";
        if (order.position_side != "") ss << "\"positionSide\":\"" << order.position_side << "\",";
        if (order.price != -1) ss << "\"price\":" << order.price << ",";
        if (order.time_in_force != "") ss << "\"timeInForce\":\"" << order.time_in_force << "\",";
        if (order.stop_price != -1) ss << "\"stopPrice\":" << order.stop_price << ",";
        if (order.new_client_order_id != "") ss << "\"newClientOrderId\":\"" << order.new_client_order_id << "\",";
        if (order.activation_price != -1) ss << "\"activationPrice\":" << order.activation_price << ",";
        if (order.callback_rate != -1) ss << "\"callbackRate\":" << order.callback_rate << ",";
        if (order.working_type != "") ss << "\"workingType\":\"" << order.working_type << "\",";
        if (order.new_order_resp_type != "") ss << "\"newOrderRespType\":\"" << order.new_order_resp_type << "\",";
        if (order.price_match != "") ss << "\"priceMatch\":\"" << order.price_match << "\",";
        if (order.self_trade_prevention_mode != "") ss << "\"selfTradePrevention\":\"" << order.self_trade_prevention_mode << "\",";
        if (order.good_till_date != -1) ss << "\"goodTillDate\":" << order.good_till_date << ",";
        if (order.reduce_only) ss << "\"reduceOnly\":" << order.reduce_only << ",";
        if (order.price_protect) ss << "\"priceProtect\":" << order.price_protect << ",";

        remove_last_comma(ss); // This will work only if at least one more character will be added

        ss << "},"; // Will this be removed check the remove_last_comma function
    }

    remove_last_comma(ss); // This will work only if at least one more character will be added

    ss << "]"; // Will this be removed check the remove_last_comma function
    
    return ss.str();
}

static std::string orders_to_json(std::vector<ModifyOrder> const &orders) {

    if (orders.empty()) return "";

    std::stringstream ss;
    ss << "[";

    for(ModifyOrder const order : orders) {
        ss << "{";
        
        ss << "\"symbol\":\"" << order.symbol << "\",";
        ss << "\"side\":\"" << order.side << "\",";
        ss << "\"quantity\":" << order.quantity << ",";
        ss << "\"price\":" << order.price << ",";
        if (order.order_id != -1) ss << "\"orderId\":" << order.order_id << ",";
        if (order.orig_client_order_id != "") ss << "\"origClientOrderId\":\"" << order.orig_client_order_id << "\",";
        if (order.price_match != "") ss << "\"priceMatch\":\"" << order.price_match << "\",";
        
        remove_last_comma(ss); // This will work only if at least one more character will be added

        ss << "},"; // Will this be removed check the remove_last_comma function
    }

    remove_last_comma(ss); // This will work only if at least one more character will be added

    ss << "]"; // Will this be removed check the remove_last_comma function

    return ss.str();
}

std::string data_to_list(std::vector<int64_t> const &data) {
    if (data.empty()) return "";

    std::stringstream ss;
    ss << "[";

    for(int64_t const &d : data) {
        ss << d << ",";
    }

    remove_last_comma(ss);

    ss << "]";

    return ss.str();
}

std::string data_to_list(std::vector<std::string> const &data) {
    if (data.empty()) return "";

    std::stringstream ss;
    ss << "[";

    for(std::string const &d : data) {
        ss << "\"" << d << "\",";
    }

    remove_last_comma(ss);

    ss << "]";

    return ss.str();
}

//------------------------------------------------------------------------------------

namespace simdjson {

// ---------- New Order ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, NewOrderObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQuote", response.cum_quote)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", response.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", response.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", response.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", response.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "reduceOnly", response.reduce_only)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "side", response.side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", response.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", response.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "stopPrice", response.stop_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "closePosition", response.close_position)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", response.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origType", response.orig_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "activatePrice", response.activate_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceRate", response.price_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", response.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceProtect", response.price_protect)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceMatch", response.price_match)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "selfTradePreventionMode", response.self_trade_prevention_mode)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "goodTillDate", response.good_till_date)) return error;

    return SUCCESS;
}
// ----------------------------------

// ---------- Place Multiple Orders ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PlaceMultipleOrdersObjectOrError &response_or_error) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    auto const res = API::read_server_message(obj);
    if (res.has_value()) {
        response_or_error = res.value();
        return SUCCESS;
    }

    PlaceMultipleOrdersObject response;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQuote", response.cum_quote)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", response.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", response.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", response.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", response.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "reduceOnly", response.reduce_only)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "side", response.side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", response.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", response.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "stopPrice", response.stop_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", response.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origType", response.orig_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "activatePrice", response.activate_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceRate", response.price_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", response.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceProtect", response.price_protect)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceMatch", response.price_match)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "selfTradePreventionMode", response.self_trade_prevention_mode)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "goodTillDate", response.good_till_date)) return error;
    response_or_error = response;

    return SUCCESS;
}
// -------------------------------------------

// ---------- Modify Order ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ModifyOrderObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pair", response.pair)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", response.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", response.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", response.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", response.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", response.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumBase", response.cum_base)) return error;
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
// ----------------------------------

// ---------- Modify Multiple Orders ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ModifyMultipleOrdersObjectOrError &response_or_error) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    auto const res = API::read_server_message(obj);
    if (res.has_value()) {
        response_or_error = res.value();
        return SUCCESS;
    }

    ModifyOrderObject response;
    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pair", response.pair)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", response.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", response.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", response.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", response.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", response.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumBase", response.cum_base)) return error;
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
    response_or_error = response;

    return SUCCESS;
}
// -------------------------------------------

// ---------- Get Order Modify History ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PriceQtyChange &change) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "before", change.before)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "after", change.after)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Amendment &amendment) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "price", amendment.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", amendment.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "count", amendment.count)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OrderModificationInfo &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "amendingId", response.amending_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pair", response.pair)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", response.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "amendment", response.amendment)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetOrderModifyHistoryObject &response) {

    if (auto error = val.get(response.order_modification_info)) return error;

    return SUCCESS;
}
// -------------------------------------------

// ---------- Cancel Order ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CancelOrderObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
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
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", response.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "activatePrice", response.activate_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceRate", response.price_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", response.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceProtect", response.price_protect)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceMatch", response.price_match)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "selfTradePreventionMode", response.self_trade_prevention_mode)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "goodTillDate", response.good_till_date)) return error;
    
    return SUCCESS;
}
// ----------------------------------

// ---------- Cancel Multiple Orders ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CancelMultipleOrdersObjectOrError &response_or_error) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    auto const res = API::read_server_message(obj);
    if (res.has_value()) {
        response_or_error = res.value();
        return SUCCESS;
    }

    CancelOrderObject response;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", response.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQty", response.cum_qty)) return error;
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
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", response.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "activatePrice", response.activate_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceRate", response.price_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", response.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceProtect", response.price_protect)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceMatch", response.price_match)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "selfTradePreventionMode", response.self_trade_prevention_mode)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "goodTillDate", response.good_till_date)) return error;
    response_or_error = response;

    return SUCCESS;
}
// -------------------------------------------

// ---------- Cancel All Open Orders ----------
// API::ServerMessageResponse
// --------------------------------------------

// ---------- Auto Cancel All Open Orders ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AutoCancelAllOpenOrdersObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "countdownTime", response.countdown_time)) return error;

    return SUCCESS;
}
// ------------------------------------------------

// ---------- Query Order ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryOrderObject &response) {

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
    if (auto error = simdjson_get_value_field_name(obj, "priceMatch", response.price_match)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "selfTradePreventionMode", response.self_trade_prevention_mode)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "goodTillDate", response.good_till_date)) return error;

    return SUCCESS;
}
// ---------------------------------

// ---------- Query All Orders ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryAllOrdersObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    return SUCCESS;
}
// --------------------------------------

// ---------- Query Current All Open Orders ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryCurrentAllOpenOrdersObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    return SUCCESS;
}
// --------------------------------------------------

// ---------- Query Current Open Order ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryCurrentOpenOrderObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    return SUCCESS;
}
// ---------------------------------------------

// ---------- Query Users Force Orders ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ForceOrder &force_order) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "orderId", force_order.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", force_order.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", force_order.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "clientOrderId", force_order.client_order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", force_order.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "avgPrice", force_order.avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origQty", force_order.orig_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "executedQty", force_order.executed_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cumQuote", force_order.cum_quote)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", force_order.time_in_force)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", force_order.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "reduceOnly", force_order.reduce_only)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "closePosition", force_order.close_position)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "side", force_order.side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", force_order.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "stopPrice", force_order.stop_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "workingType", force_order.working_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "origType", force_order.orig_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", force_order.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", force_order.update_time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryUsersForceOrdersObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    return SUCCESS;
}
// ---------------------------------------------

// ---------- Query Account Trade List ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountTrade &trade) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "buyer", trade.buyer)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "commission", trade.commission)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "commissionAsset", trade.commission_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "id", trade.id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maker", trade.maker)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderId", trade.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", trade.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "qty", trade.qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "quoteQty", trade.quote_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "realizedPnl", trade.realized_pnl)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "side", trade.side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", trade.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", trade.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", trade.time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryAccountTradeListObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    return SUCCESS;
}
// ---------------------------------------------

// ---------- Change Margin Type ----------
// API::ServerMessageResponse
// ----------------------------------------

// ---------- Change Position Mode ----------
// API::ServerMessageResponse
// ------------------------------------------

// ---------- Change Initial Leverage ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ChangeInitialLeverageObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "leverage", response.leverage)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxNotionalValue", response.max_notional_value)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;

    return SUCCESS;
}
// ---------------------------------------------

// ---------- Change Multi Assets Mode ----------
// API::ServerMessageResponse
// ----------------------------------------------

// ---------- Modify Isolated Position Margin ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ModifyIsolatedPositionMarginObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "amount", response.amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "code", response.message.code)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "msg", response.message.msg)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", response.type)) return error;

    return SUCCESS;
}
// ----------------------------------------------------

// ---------- Position Information V2 ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PositionInfoV2 &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "entryPrice", response.entry_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "breakEvenPrice", response.break_even_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginType", response.margin_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isAutoAddMargin", response.is_auto_add_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isolatedMargin", response.isolated_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "leverage", response.leverage)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "liquidationPrice", response.liquidation_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "markPrice", response.mark_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxNotionalValue", response.max_notional_value)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionAmt", response.position_amt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "notional", response.notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isolatedWallet", response.isolated_wallet)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "unRealizedProfit", response.unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", response.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PositionInformationV2Object &response) {

    if (auto error = val.get(response.positions)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Position Information V3 ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PositionInfoV3 &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", response.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionAmt", response.position_amt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "entryPrice", response.entry_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "breakEvenPrice", response.break_even_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "markPrice", response.mark_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "unRealizedProfit", response.unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "liquidationPrice", response.liquidation_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isolatedMargin", response.isolated_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "notional", response.notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginAsset", response.margin_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isolatedWallet", response.isolated_wallet)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "initialMargin", response.initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maintMargin", response.maint_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionInitialMargin", response.position_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "openOrderInitialMargin", response.open_order_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "adl", response.adl)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bidNotional", response.bid_notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "askNotional", response.ask_notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PositionInformationV3Object &response) {

    if (auto error = val.get(response.positions)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Position Adl Quantile Estimation ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AdlQuantile &adl_quantile) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "hedge", adl_quantile.hedge)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "long", adl_quantile.long_)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "short", adl_quantile.short_)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AdlQuantileEstimation &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "adl_quantile", response.adl_quantile)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PositionAdlQuantileEstimationObject &response) {

    if (auto error = val.get(response.adl_quantile_estimations)) return error;

    return SUCCESS;
}
// ------------------------------------------------------

// ---------- Get Position Margin Change History ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PositionMarginChange &change) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", change.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", change.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "deltaType", change.delta_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "amount", change.amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "asset", change.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", change.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", change.position_side)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetPositionMarginChangeHistoryObject &response) {

    if (auto error = val.get(response.position_margin_changes)) return error;

    return SUCCESS;
}
// ------------------------------------------------------

// ---------- Test New Order ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, TestNewOrderObject &response) {

    if (auto error = val.get(response.order)) return error;

    return SUCCESS;
}
// ------------------------------------


// Websocket API

// ---------- Session Responses ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SessionStreamObject &response) {
    
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

//-----------------------------------------------------------------------------

#endif // TRADE_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------