
//------------------------------------------------------------------------------------

#include "trade.hpp"

#include "lib/utils.hpp"
#include "api.hpp"

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

} // namespace simdjson

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
