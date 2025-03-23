
#include "convert.hpp"

#include "lib/utils.hpp"

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

//------------------------------------------------------------------------------------

namespace Convert {

//------------------------------------------------------------------------------------

// REST API Endpoints

namespace RestAPI {

ListAllConvertedPairsResponse list_all_converted_pairs(DerivativesTrading &api, std::string const &from_asset, std::string const &to_asset) {
    std::string const url = "/fapi/v1/convert/exchangeInfo";

    API::Parameters params;
    if (!from_asset.empty()) params.emplace_back("fromAsset", from_asset);
    if (!to_asset.empty()) params.emplace_back("toAsset", to_asset);

    std::string response = api.send_request("GET", url, params);

    return parse_api_response<ListAllConvertedPairsObject>(api.get_parser(), response);
}

SendQuoteRequestResponse send_quote_request(DerivativesTrading &api, std::string const &from_asset, std::string const &to_asset, double const from_amount, double const to_amount, std::string const valid_time, int32_t const recv_window) {
    std::string const url = "/fapi/v1/convert/request";

    API::Parameters params;
    params.emplace_back("fromAsset", from_asset);
    params.emplace_back("toAsset", to_asset);
    if (from_amount != -1) params.emplace_back("fromAmount", from_amount);
    if (to_amount != -1) params.emplace_back("toAmount", to_amount);
    if (!valid_time.empty()) params.emplace_back("validTime", valid_time);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = api.sign_request("POST", url, params);

    return parse_api_response<SendQuoteRequestObject>(api.get_parser(), response);
}

AcceptQuoteResponse accept_quote(DerivativesTrading &api, std::string const &quote_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/convert/acceptQuote";

    API::Parameters params;
    params.emplace_back("quoteId", quote_id);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = api.sign_request("POST", url, params);

    return parse_api_response<AcceptQuoteObject>(api.get_parser(), response);
}

OrderStatusResponse order_status(DerivativesTrading &api, std::string const &order_id, std::string const &quote_id) {
    std::string const url = "/fapi/v1/convert/orderStatus";

    API::Parameters params;
    if (!order_id.empty()) params.emplace_back("orderId", order_id);
    if (!quote_id.empty()) params.emplace_back("quoteId", quote_id);

    std::string response = api.send_request("GET", url, params);

    return parse_api_response<OrderStatusObject>(api.get_parser(), response);
}

} // namespace RestAPI

//------------------------------------------------------------------------------------

} // namespace Convert

//------------------------------------------------------------------------------------
