
//--------------------------------------------------------------------------------------

#include "account.hpp"
#include "account_parsing_simdjson.hpp"

#include "api.hpp"

//--------------------------------------------------------------------------------------

using namespace Account;

//--------------------------------------------------------------------------------------

NewFutureAccountTransferResponse API::new_future_account_transfer(std::string const &type, std::string const &asset, double const amount, std::string const &from_symbol, std::string const &to_symbol, int32_t const recv_window) {
    std::string const url = "/sapi/v1/asset/transfer";

    Parameters params;
    params.emplace_back("type", type);
    params.emplace_back("asset", asset);
    params.emplace_back("amount", amount);
    if (from_symbol != "") params.emplace_back("fromSymbol", from_symbol);
    if (to_symbol != "") params.emplace_back("toSymbol", to_symbol);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::POST>(url, params);

    return parse_response<NewFutureAccountTransferObject>(response);
}

FuturesAccountBalanceV3Response API::futures_account_balance_v3(int32_t const recv_window) {
    std::string const url = "/fapi/v3/balance";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<FuturesAccountBalanceV3Object>(response);
}

FuturesAccountBalanceResponse API::futures_account_balance(int32_t const recv_window) {
    std::string const url = "/fapi/v2/balance";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<FuturesAccountBalanceObject>(response);
}

AccountInformationV3Response API::account_information_v3(int32_t const recv_window) {
    std::string const url = "/fapi/v3/account";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<AccountInformationV3Object>(response);
}

AccountInformationResponse API::account_information(int32_t const recv_window) {
    std::string const url = "/fapi/v2/account";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<AccountInformationObject>(response);
}

GetFutureAccountTransactionHistoryListResponse API::get_future_account_transaction_history_list(std::string const &type, int64_t const start_time, int64_t const end_time, int32_t const current, int8_t const size, std::string const &from_symbol, std::string const &to_symbol, int32_t const recv_window) {
    std::string const url = "/sapi/v1/asset/transfer";

    Parameters params;
    params.emplace_back("type", type);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (current != -1) params.emplace_back("current", current);
    if (size != -1) params.emplace_back("size", size);
    if (from_symbol != "") params.emplace_back("fromSymbol", from_symbol);
    if (to_symbol != "") params.emplace_back("toSymbol", to_symbol);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetFutureAccountTransactionHistoryListObject>(response);
}

UserCommissionRateResponse API::user_commission_rate(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v1/commissionRate";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<UserCommissionRateObject>(response);
}

QueryAccountConfigurationResponse API::query_account_configuration(int32_t const recv_window) {
    std::string const url = "/fapi/v1/accountConfig";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<QueryAccountConfigurationObject>(response);
}

QuerySymbolConfigurationResponse API::query_symbol_configuration(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v1/symbolConfig";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<QuerySymbolConfigurationObject>(response);
}

QueryOrderRateLimitResponse API::query_order_rate_limit(int32_t const recv_window) {
    std::string const url = "/fapi/v1/rateLimit/order";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<QueryOrderRateLimitObject>(response);
}

NotionalAndLeverageBracketsResponse API::notional_and_leverage_brackets(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v1/leverageBracket";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<NotionalAndLeverageBracketsObject>(response);
}

GetCurrentMultiAssetsModeResponse API::get_current_multi_assets_mode(int32_t const recv_window) {
    std::string const url = "/fapi/v1/multiAssetsMargin";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetCurrentMultiAssetsModeObject>(response);
}

GetCurrentPositionModeResponse API::get_current_position_mode(int32_t const recv_window) {
    std::string const url = "/fapi/v1/positionSide/dual";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetCurrentPositionModeObject>(response);
}

GetIncomeHistoryResponse API::get_income_history(std::string const &symbol, std::string const &income_type, int64_t const start_time, int64_t const end_time, int32_t const page, int16_t const limit, int32_t const recv_window) {
    std::string const url = "/fapi/v1/income";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (income_type != "") params.emplace_back("incomeType", income_type);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (page != -1) params.emplace_back("page", page);
    if (limit != -1) params.emplace_back("limit", limit);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);
    
    return parse_response<GetIncomeHistoryObject>(response);
}

FuturesTradingQuantitativeRulesIndicatorsResponse API::futures_trading_quantitative_rules_indicators(std::string const &symbol, int32_t const recv_window) {
    std::string const url = "/fapi/v1/apiTradingStatus";

    Parameters params;
    if (symbol != "") params.emplace_back("symbol", symbol);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<FuturesTradingQuantitativeRulesIndicatorsObject>(response);
}

GetDownloadIdForFuturesTransactionHistoryResponse API::get_download_id_for_futures_transaction_history(int64_t const start_time, int64_t const end_time, int32_t const recv_window) {
    std::string const url = "/fapi/v1/income/asyn";

    Parameters params;
    params.emplace_back("startTime", start_time);
    params.emplace_back("endTime", end_time);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetDownloadIdForFuturesTransactionHistoryObject>(response);
}

GetFuturesTransactionHistoryDownloadLinkByIdResponse API::get_futures_transaction_history_download_link_by_id(std::string const &download_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/income/asyn/id";

    Parameters params;
    params.emplace_back("downloadId", download_id);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetFuturesTransactionHistoryDownloadLinkByIdObject>(response);
}

GetDownloadIdForFuturesOrderHistoryResponse API::get_download_id_for_futures_order_history(int64_t const start_time, int64_t const end_time, int32_t const recv_window) {
    std::string const url = "/fapi/v1/order/asyn";

    Parameters params;
    params.emplace_back("startTime", start_time);
    params.emplace_back("endTime", end_time);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetDownloadIdForFuturesOrderHistoryObject>(response);
}

GetFuturesOrderHistoryDownloadLinkByIdResponse API::get_futures_order_history_download_link_by_id(std::string const &download_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/order/asyn/id";

    Parameters params;
    params.emplace_back("downloadId", download_id);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetFuturesOrderHistoryDownloadLinkByIdObject>(response);
}

GetDownloadIdForFuturesTradeHistoryResponse API::get_download_if_for_futures_trade_history(int64_t const start_time, int64_t const end_time, int32_t const recv_window) {
    std::string const url = "/fapi/v1/trade/asyn";

    Parameters params;
    params.emplace_back("startTime", start_time);
    params.emplace_back("endTime", end_time);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetDownloadIdForFuturesTradeHistoryObject>(response);
}

GetFuturesTradeDownloadLinkByIdResponse API::get_futures_trade_download_link_by_id(std::string const &download_id, int32_t const recv_window) {
    std::string const url = "/fapi/v1/trade/asyn/id";

    Parameters params;
    params.emplace_back("downloadId", download_id);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetFuturesTradeDownloadLinkByIdObject>(response);
}

ToggleBnbBurnOnFuturesTradeResponse API::toggle_bnb_burn_on_futures_trade(bool const feeBurn, int32_t const recv_window) {
    std::string const url = "/fapi/v1/feeBurn";

    Parameters params;
    params.emplace_back("feeBurn", feeBurn);
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::POST>(url, params);

    return parse_response(response, API::ResponseIsServerMessage{});
}

GetBnbBurnStatusResponse API::get_bnb_burn_status(int32_t const recv_window) {
    std::string const url = "/fapi/v1/feeBurn";

    Parameters params;
    if (recv_window > 0) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<API::RequestType::GET>(url, params);

    return parse_response<GetBnbBurnStatusObject>(response);
}

//---------------------------------------------------------------------------------------
