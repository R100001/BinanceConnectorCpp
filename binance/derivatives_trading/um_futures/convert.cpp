
#include "convert.hpp"
#include "convert_parsing_simdjson.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------

ListAllConvertedPairsResponse API::list_all_converted_pairs(std::string const &from_asset, std::string const &to_asset) {
    std::string const url = "/fapi/v1/convert/exchangeInfo";

    Parameters params;
    if (!from_asset.empty()) params.emplace_back("fromAsset", from_asset);
    if (!to_asset.empty()) params.emplace_back("toAsset", to_asset);

    std::string response = send_request<API::RequestType::GET>(url, params);

    return parse_response<ListAllConvertedPairsObject>(response);
}

SendQuoteRequestResponse API::send_quote_request(std::string const &from_asset, std::string const &to_asset, double const from_amount, double const to_amount, std::string const valid_time, int32_t const recv_window) {
    std::string const url = "/fapi/v1/convert/request";

    Parameters params;
    params.emplace_back("fromAsset", from_asset);
    params.emplace_back("toAsset", to_asset);
    if (from_amount != -1) params.emplace_back("fromAmount", from_amount);
    if (to_amount != -1) params.emplace_back("toAmount", to_amount);
    if (!valid_time.empty()) params.emplace_back("validTime", valid_time);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::POST>(url, params);

    return parse_response<SendQuoteRequestObject>(response);
}

AcceptQuoteResponse API::accept_quote(std::string const &quote_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/convert/acceptQuote";

    Parameters params;
    params.emplace_back("quoteId", quote_id);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::POST>(url, params);

    return parse_response<AcceptQuoteObject>(response);
}

OrderStatusResponse API::order_status(std::string const &order_id, std::string const &quote_id) {
    std::string const url = "/fapi/v1/convert/orderStatus";

    Parameters params;
    if (!order_id.empty()) params.emplace_back("orderId", order_id);
    if (!quote_id.empty()) params.emplace_back("quoteId", quote_id);

    std::string response = send_request<API::RequestType::GET>(url, params);

    return parse_response<OrderStatusObject>(response);
}

//------------------------------------------------------------------------------------
