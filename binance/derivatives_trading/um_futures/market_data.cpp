
#include "market_data.hpp"
#include "market_data_parsing_simdjson.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------

TestConnectivityResponse API::test_connectivity() {
    std::string const url = "/fapi/v1/ping";

    std::string response = send_request<RequestType::GET>(url);

    return parse_response<TestConnectivityObject>(response);
}

CheckServerTimeResponse API::check_server_time() {
    std::string const url = "/fapi/v1/time";

    std::string response = send_request<RequestType::GET>(url);

    return parse_response<CheckServerTimeObject>(response);
}

ExchangeInformationResponse API::exchange_information() {
    std::string const url = "/fapi/v1/exchangeInfo";

    std::string response = send_request<RequestType::GET>(url);

    return parse_response<ExchangeInformationObject>(response);
}

OrderBookResponse API::order_book(std::string const &symbol, int16_t const limit) {
    std::string const url = "/fapi/v1/depth";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<OrderBookObject>(response);
}

RecentTradesListResponse API::recent_trades_list(std::string const &symbol, int16_t const limit) {
    std::string const url = "/fapi/v1/trades";
    
    Parameters params;
    params.emplace_back("symbol", symbol);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<RecentTradesListObject>(response);
}

OldTradesLookupResponse API::old_trades_lookup(std::string const &symbol, int16_t const limit, int64_t const from_id) {
    std::string const url = "/fapi/v1/historicalTrades";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (limit != -1) params.emplace_back("limit", limit);
    if (from_id != -1) params.emplace_back("fromId", from_id);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<OldTradesLookupObject>(response);
}

CompressedAggregateTradesListResponse API::compressed_aggregate_trades_list(std::string const &symbol, int64_t const from_id, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/aggTrades";

    Parameters params;
    params.emplace_back("symbol", symbol);
    if (from_id != -1) params.emplace_back("fromId", from_id);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<CompressedAggregateTradesListObject>(response);
}

KlineCandlestickDataResponse API::kline_candlestick_data(std::string const &symbol, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/klines";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);
    
    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<KlineCandlestickDataObject>(response);
}

ContinuousContractKlineCandlestickDataResponse API::continuous_contract_kline_candlestick_data(std::string const &pair, std::string const &contract_type, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/continuousKlines";

    Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("contractType", contract_type);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<ContinuousContractKlineCandlestickDataObject>(response);
}

IndexPriceKlineCandlestickDataResponse API::index_price_kline_candlestick_data(std::string const &pair, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/indexPriceKlines";

    Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<IndexPriceKlineCandlestickDataObject>(response);
}

MarkPriceKlineCandlestickDataResponse API::mark_price_kline_candlestick_data(std::string const &pair, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/markPriceKlines";

    Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<MarkPriceKlineCandlestickDataObject>(response);
}

PremiumIndexKlineDataResponse API::premium_index_kline_data(std::string const &symbol, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/premiumIndexKlines";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<PremiumIndexKlineDataObject>(response);
}

MarkPriceResponse API::mark_price(std::string const &symbol) {
    std::string const url = "/fapi/v1/premiumIndex";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<MarkPriceObject>(response);
}

GetFundingRateHistoryResponse API::get_funding_rate_history(std::string const &symbol, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/fundingRate";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<GetFundingRateHistoryObject>(response);
}

GetFundingRateInfoResponse API::get_funding_rate_info() {
    std::string const url = "/fapi/v1/fundingInfo";

    std::string response = send_request<RequestType::GET>(url);

    return parse_response<GetFundingRateInfoObject>(response);
}

Ticker24hrPriceChangeStatisticsResponse API::ticker_24hr_price_change_statistics(std::string const &symbol) {
    std::string const url = "/fapi/v1/ticker/24hr";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<Ticker24hrPriceChangeStatisticsObject>(response);
}

SymbolPriceTickerResponse API::symbol_price_ticker(std::string const &symbol) {
    std::string const url = "/fapi/v1/ticker/price";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<SymbolPriceTickerObject>(response);
}

SymbolPriceTickerV2Response API::symbol_price_ticker_v2(std::string const &symbol) {
    std::string const url = "/fapi/v2/ticker/price";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<SymbolPriceTickerV2Object>(response);
}

SymbolOrderBookTickerResponse API::symbol_order_book_ticker(std::string const &symbol) {
    std::string const url = "/fapi/v1/ticker/bookTicker";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<SymbolOrderBookTickerObject>(response);
}

QueryDeliveryPriceResponse API::query_delivery_price(std::string const &pair) {
    std::string const url = "/futures/data/delivery-price";

    Parameters params;
    params.emplace_back("pair", pair);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<QueryDeliveryPriceObject>(response);
}

OpenInterestResponse API::open_interest(std::string const &symbol) {
    std::string const url = "/fapi/v1/openInterest";

    Parameters params;
    params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<OpenInterestObject>(response);
}

OpenInterestStatisticsResponse API::open_interest_statistics(std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/fapi/v1/openInterestHist";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<OpenInterestStatisticsObject>(response);
}

TopTraderLongShortPositionRatioResponse API::top_trader_long_short_position_ratio(std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/topLongShortPositionRatio";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<TopTraderLongShortPositionRatioObject>(response);
}

TopTraderLongShortAccountRatioResponse API::top_trader_long_short_account_ratio(std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/topLongShortAccountRatio";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<TopTraderLongShortAccountRatioObject>(response);
}

LongShortRatioResponse API::long_short_ratio(std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/globalLongShortAccountRatio";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<LongShortRatioObject>(response);
}

TakerBuySellVolumeResponse API::taker_buy_sell_volume(std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/takerlongshortRatio";

    Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<TakerBuySellVolumeObject>(response);
}

BasisResponse API::basis(std::string const &pair, std::string const &contract_type, std::string const &period, int16_t const &limit, int64_t const &start_time, int64_t const &end_time) {
    std::string const url = "/futures/data/basis";

    Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("contractType", contract_type);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<BasisObject>(response);
}

CompositeIndexSymbolInformationResponse API::composite_index_symbol_information(std::string const &symbol) {
    std::string const url = "/fapi/v1/indexInfo";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<CompositeIndexSymbolInformationObject>(response);
}

MultiAssetsModeAssetIndexResponse API::multi_assets_mode_asset_index(std::string const &symbol) {
    std::string const url = "/fapi/v1/assetIndex";

    Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<MultiAssetsModeAssetIndexObject>(response);
}

QueryIndexPriceConstituentsResponse API::query_index_price_constituents(std::string const &symbol) {
    std::string const url = "/fapi/v1/constituents";

    Parameters params;
    params.emplace_back("symbol", symbol);

    std::string response = send_request<RequestType::GET>(url, params);

    return parse_response<QueryIndexPriceConstituentsObject>(response);
}

//------------------------------------------------------------------------------------
