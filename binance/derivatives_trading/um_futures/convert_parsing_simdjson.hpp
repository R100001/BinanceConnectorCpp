
//-----------------------------------------------------------------------------

#ifndef CONVERT_PARSING_SIMDJSON_HPP
#define CONVERT_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------

#include "convert.hpp"

#include "utils.hpp"

//------------------------------------------------------------------------------------

namespace simdjson {

using namespace Convert;

// ---------- List All Converted Pairs ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ConvertPairs &convert_pairs) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "fromAsset", convert_pairs.from_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "toAsset", convert_pairs.to_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fromAssetMinAmount", convert_pairs.from_asset_min_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fromAssetMaxAmount", convert_pairs.from_asset_max_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "toAssetMinAmount", convert_pairs.to_asset_min_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "toAssetMaxAmount", convert_pairs.to_asset_max_amount)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ListAllConvertedPairsObject &response) {

    if (auto error = val.get(response.pairs)) return error;

    return SUCCESS;
}
// ----------------------------------------------

// ---------- Send Quote Request ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SendQuoteRequestObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "quoteId", response.quote_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ratio", response.ratio)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "inverseRatio", response.inverse_ratio)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "validTimestamp", response.valid_timestamp)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "toAmount", response.to_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fromAmount", response.from_amount)) return error;

    return SUCCESS;
}
// ----------------------------------------

// ---------- Accept Quote ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AcceptQuoteObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "createTime", response.create_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderStatus", response.order_status)) return error;

    return SUCCESS;
}
// ----------------------------------

// ---------- Order Status ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OrderStatusObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "orderId", response.order_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderStatus", response.order_status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fromAsset", response.from_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fromAmount", response.from_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "toAsset", response.to_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "toAmount", response.to_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ratio", response.ratio)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "inverseRatio", response.inverse_ratio)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "createTime", response.create_time)) return error;

    return SUCCESS;
}
// ----------------------------------

} // namespace simdjson

//-----------------------------------------------------------------------------

#endif // CONVERT_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------
