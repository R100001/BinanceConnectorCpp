
#include "market_data.hpp"

#include "lib/utils.hpp"

//------------------------------------------------------------------------------------

namespace simdjson {

using namespace MarketData;

// ---------- Test Connectivity ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, TestConnectivityObject& response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    return SUCCESS;
}
// --------------------------------------

// ---------- Check Server Time ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CheckServerTimeObject& response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "serverTime", response.server_time)) return error;

    return SUCCESS;
}
// ---------------------------------------

// ---------- Exchange Information ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ExchangeFilter &exchange_filter) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, RateLimit &rate_limit) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "rateLimitType", rate_limit.rate_limit_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "interval", rate_limit.interval)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "intervalNum", rate_limit.interval_num)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "limit", rate_limit.limit)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Asset &asset) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "asset", asset.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginAvailable", asset.margin_available)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "autoAssetExchange", asset.auto_asset_exchange)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Filter &filter) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    std::string filter_type;
    if (auto error = simdjson_get_value_field_name<true>(obj, "filterType", filter_type)) return error;

    if (filter_type == "PRICE_FILTER") {
        
        FilterPriceFilter price_filter;
        price_filter.filter_type = filter_type;
        if (auto error = simdjson_get_value_field_name<true>(obj, "minPrice", price_filter.min_price)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "maxPrice", price_filter.max_price)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "tickSize", price_filter.tick_size)) return error;

        filter = price_filter;

    }
    else if (filter_type == "LOT_SIZE") {
        
        FilterLotSize lot_size;
        lot_size.filter_type = filter_type;
        if (auto error = simdjson_get_value_field_name<true>(obj, "minQty", lot_size.min_qty)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "maxQty", lot_size.max_qty)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "stepSize", lot_size.step_size)) return error;

        filter = lot_size;

    }
    else if (filter_type == "MARKET_LOT_SIZE") {
        
        FilterMarketLotSize market_lot_size;
        market_lot_size.filter_type = filter_type;
        if (auto error = simdjson_get_value_field_name<true>(obj, "minQty", market_lot_size.min_qty)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "maxQty", market_lot_size.max_qty)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "stepSize", market_lot_size.step_size)) return error;

        filter = market_lot_size;

    }
    else if (filter_type == "MAX_NUM_ORDERS") {
        
        FilterMaxNumOrders max_num_orders;
        max_num_orders.filter_type = filter_type;
        if (auto error = simdjson_get_value_field_name(obj, "limit", max_num_orders.limit)) return error;

        filter = max_num_orders;

    }
    else if (filter_type == "MAX_NUM_ALGO_ORDERS") {
        
        FilterMaxNumAlgoOrders max_num_algo_orders;
        max_num_algo_orders.filter_type = filter_type;
        if (auto error = simdjson_get_value_field_name(obj, "limit", max_num_algo_orders.limit)) return error;

        filter = max_num_algo_orders;

    }
    else if (filter_type == "MIN_NOTIONAL") {
        
        FilterMinNotional min_notional;
        min_notional.filter_type = filter_type;
        if (auto error = simdjson_get_value_field_name(obj, "notional", min_notional.notional)) return error;

        filter = min_notional;

    }
    else if (filter_type == "PERCENT_PRICE") {
        
        FilterPercentPrice percent_price;
        percent_price.filter_type = filter_type;
        if (auto error = simdjson_get_value_field_name<true>(obj, "multiplierDecimal", percent_price.multiplier_decimal)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "multiplierUp", percent_price.multiplier_up)) return error;
        if (auto error = simdjson_get_value_field_name<true>(obj, "multiplierDown", percent_price.multiplier_down)) return error;
    
        filter = percent_price;

    }

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Symbol &symbol) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", symbol.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pair", symbol.pair)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "contractType", symbol.contract_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "deliveryDate", symbol.delivery_date)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "onboardDate", symbol.onboard_date)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", symbol.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maintMarginPercent", symbol.maint_margin_percent)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "requiredMarginPercent", symbol.required_margin_percent)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "baseAsset", symbol.base_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "quoteAsset", symbol.quote_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginAsset", symbol.margin_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pricePrecision", symbol.price_precision)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "quantityPrecision", symbol.quantity_precision)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "baseAssetPrecision", symbol.base_asset_precision)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "quotePrecision", symbol.quote_precision)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "underlyingType", symbol.underlying_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "underlyingSubType", symbol.underlying_sub_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "triggerProtect", symbol.trigger_protect)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "liquidationFee", symbol.liquidation_fee)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marketTakeBound", symbol.market_take_bound)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxMoveOrderLimit", symbol.max_move_order_limit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "filters", symbol.filters)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "orderTypes", symbol.order_types)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timeInForce", symbol.time_in_force)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ExchangeInformationObject& response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "timezone", response.timezone)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "serverTime", response.server_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "futuresType", response.futures_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "rateLimits", response.rate_limits)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "exchangeFilters", response.exchange_filters)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "assets", response.assets)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbols", response.symbols)) return error;

    return SUCCESS;
}
// ------------------------------------------

// ---------- Order Book ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, BidAskEntry &entry) {

    ondemand::array arr;
    if (auto error = val.get_array().get(arr)) return error;
    
    std::array<std::string, 2> arr_str;
    int i = 0;
    for (auto field : arr) {
        std::string_view sv;
        if (auto error = field.get(sv)) return error;
        arr_str[i++] = std::string(sv);
    }
    entry.price = std::move(arr_str[0]);
    entry.qty = std::move(arr_str[1]);

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OrderBookObject& response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "lastUpdateId", response.last_update_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bids", response.bids)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "asks", response.asks)) return error;

    return SUCCESS;
}
// --------------------------------

// ---------- Recent Trades List ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Trade &trade) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "id", trade.id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", trade.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "qty", trade.qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "quoteQty", trade.quote_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", trade.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isBuyerMaker", trade.is_buyer_maker)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, RecentTradesListObject& response) {

    if(auto error = val.get(response.trades)) return error;

    return SUCCESS;
}
// ----------------------------------------

// ---------- Old Trades Lookup ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OldTradesLookupObject& response) {

    if(auto error = val.get(response.trades)) return error;

    return SUCCESS;
}
// ---------------------------------------

// ---------- Compressed Aggregate Trades List ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AggregatedTrade &trade) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "a", trade.a)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", trade.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", trade.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "f", trade.f)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", trade.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", trade.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "m", trade.m)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CompressedAggregateTradesListObject& response) {

    if(auto error = val.get(response.trades)) return error;

    return SUCCESS;
}
// ---------------------------------------------------

// ---------- Kline Candlestick Data ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, std::array<KlineDataTypes, 12> &response) {

    ondemand::array arr;
    if (auto error = val.get_array().get(arr)) return error;

    int i = 0;
    for (auto field : arr) {
        if(field.type() == ondemand::json_type::number) {
            int64_t temp;
            if (auto error = field.get(temp)) return error;
            response[i++] = temp;
        }
        else {
            std::string_view sv;
            if (auto error = field.get(sv)) return error;
            response[i++] = std::move(std::string(sv));
        }
    }

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, KlineCandlestickDataObject& response) {

    if(auto error = val.get(response.klines)) return error;

    return SUCCESS;
} 
// ------------------------------------------

// ---------- Continuous Contract Kline Candlestick Data ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ContinuousContractKlineCandlestickDataObject& response) {

    if(auto error = val.get(response.klines)) return error;

    return SUCCESS;
}
// ---------------------------------------------------------------

// ---------- Index Price Kline Candlestick Data ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, IndexPriceKlineCandlestickDataObject& response) {

    if(auto error = val.get(response.klines)) return error;

    return SUCCESS;
}
// -------------------------------------------------------

// ---------- Mark Price Kline Candlestick Data ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MarkPriceKlineCandlestickDataObject& response) {

    if(auto error = val.get(response.klines)) return error;

    return SUCCESS;
}
// ------------------------------------------------------

// ---------- Premium Index Kline Data ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PremiumIndexKlineDataObject& response) {

    if(auto error = val.get(response.klines)) return error;

    return SUCCESS;
}
// ----------------------------------------------

// ---------- Mark Price ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MarkPrice &mark_price) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", mark_price.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "markPrice", mark_price.mark_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "indexPrice", mark_price.index_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "estimatedSettlePrice", mark_price.estimated_settle_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "lastFundingRate", mark_price.last_funding_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "interestRate", mark_price.interest_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "nextFundingTime", mark_price.next_funding_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", mark_price.time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MarkPriceObject& response) {

    if (val.type() == ondemand::json_type::object) {
        MarkPrice mark_price;
        if(auto error = val.get(mark_price)) return error;
        response.data = std::move(mark_price);
    }
    else {
        std::vector<MarkPrice> mark_prices;
        if(auto error = val.get(mark_prices)) return error;
        response.data = std::move(mark_prices);
    }

    return SUCCESS;
}
// -----------------------------------

// ---------- Get Funding Rate History ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, FundingRate &funding_rate) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", funding_rate.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fundingTime", funding_rate.funding_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fundingRate", funding_rate.funding_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "markPrice", funding_rate.mark_price)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetFundingRateHistoryObject& response) {

    if(auto error = val.get(response.funding_rates)) return error;

    return SUCCESS;
}
// ----------------------------------------------

// ---------- Get Funding Rate Info ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, FundingRateAdjustments &funding_rate_adjustments) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", funding_rate_adjustments.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "adjustedFundingRateCap", funding_rate_adjustments.adjusted_funding_rate_cap)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "adjustedFundingRateFloor", funding_rate_adjustments.adjusted_funding_rate_floor)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "fundingIntervalHours", funding_rate_adjustments.funding_interval_hours)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "disclaimer", funding_rate_adjustments.disclaimer)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetFundingRateInfoObject& response) {

    if(auto error = val.get(response.funding_rate_adjustments)) return error;

    return SUCCESS;
}
// ------------------------------------------

// ---------- Ticker 24hr Price Change Statistics ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PriceChangeStatistics24Hours &price_change_statistics) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", price_change_statistics.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceChange", price_change_statistics.price_change)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "priceChangePercent", price_change_statistics.price_change_percent)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "weightedAvgPrice", price_change_statistics.weighted_avg_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "lastPrice", price_change_statistics.last_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "lastQty", price_change_statistics.last_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "openPrice", price_change_statistics.open_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "highPrice", price_change_statistics.high_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "lowPrice", price_change_statistics.low_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "volume", price_change_statistics.volume)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "quoteVolume", price_change_statistics.quote_volume)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "openTime", price_change_statistics.open_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "closeTime", price_change_statistics.close_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "firstId", price_change_statistics.first_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "lastId", price_change_statistics.last_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "count", price_change_statistics.count)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Ticker24hrPriceChangeStatisticsObject &response) {

    if (val.type() == ondemand::json_type::object) {
        PriceChangeStatistics24Hours price_change_statistics;
        if(auto error = val.get(price_change_statistics)) return error;
        response.data = std::move(price_change_statistics);
    }
    else {
        std::vector<PriceChangeStatistics24Hours> price_change_statistics;
        if(auto error = val.get(price_change_statistics)) return error;
        response.data = std::move(price_change_statistics);
    }

    return SUCCESS;
}
// ---------------------------------------------------------

// ---------- Symbol Price Ticker ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PriceTicker &price_ticker) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", price_ticker.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "price", price_ticker.price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", price_ticker.time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SymbolPriceTickerObject &response) {

    if (val.type() == ondemand::json_type::object) {
        PriceTicker price_ticker;
        if(auto error = val.get(price_ticker)) return error;
        response.data = std::move(price_ticker);
    }
    else {
        std::vector<PriceTicker> price_tickers;
        if(auto error = val.get(price_tickers)) return error;
        response.data = std::move(price_tickers);
    }

    return SUCCESS;
}
// -----------------------------------------

// ---------- Symbol Price Ticker V2 ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SymbolPriceTickerV2Object &response) {

    if (val.type() == ondemand::json_type::object) {
        PriceTicker price_ticker;
        if(auto error = val.get(price_ticker)) return error;
        response.data = std::move(price_ticker);
    }
    else {
        std::vector<PriceTicker> price_tickers;
        if(auto error = val.get(price_tickers)) return error;
        response.data = std::move(price_tickers);
    }

    return SUCCESS;
}
// -------------------------------------------

// ---------- Symbol Order Book Ticker ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OrderBookTicker &order_book_ticker) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", order_book_ticker.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bidPrice", order_book_ticker.bid_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bidQty", order_book_ticker.bid_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "askPrice", order_book_ticker.ask_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "askQty", order_book_ticker.ask_qty)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", order_book_ticker.time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SymbolOrderBookTickerObject &response) {

    if (val.type() == ondemand::json_type::object) {
        OrderBookTicker order_book_ticker;
        if(auto error = val.get(order_book_ticker)) return error;
        response.data = std::move(order_book_ticker);
    }
    else {
        std::vector<OrderBookTicker> order_book_tickers;
        if(auto error = val.get(order_book_tickers)) return error;
        response.data = std::move(order_book_tickers);
    }

    return SUCCESS;
}
// --------------------------------------------

// ---------- Query Delivery Price ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, DeliveryPrice &delivery_price) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "deliveryTime", delivery_price.delivery_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "deliveryPrice", delivery_price.delivery_price)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryDeliveryPriceObject &response) {

    if (auto error = val.get(response.delivery_prices)) return error;

    return SUCCESS;
}
// ----------------------------------------

// ---------- Open Interest ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OpenInterestObject &open_interest) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "openInterest", open_interest.open_interest)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", open_interest.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", open_interest.time)) return error;

    return SUCCESS;
}
// ----------------------------------

// ---------- Open Interest Statistics ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OpenInterestStatistics &open_interest_statistics) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", open_interest_statistics.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "sumOpenInterest", open_interest_statistics.sum_open_interest)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "sumOpenInterestValue", open_interest_statistics.sum_open_interest_value)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timestamp", open_interest_statistics.timestamp)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OpenInterestStatisticsObject &response) {

    if (auto error = val.get(response.open_interest_statistics)) return error;

    return SUCCESS;
}
// ----------------------------------------------

// ---------- Top Trader Long Short Position Ratio ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, LongShortRatio &long_short_ratio) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", long_short_ratio.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "longShortRatio", long_short_ratio.long_short_ratio)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "longAccount", long_short_ratio.long_account)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "shortAccount", long_short_ratio.short_account)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timestamp", long_short_ratio.timestamp)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, TopTraderLongShortPositionRatioObject &response) {

    if (auto error = val.get(response.long_short_ratios)) return error;

    return SUCCESS;
}
// --------------------------------------------------------

// ---------- Top Trader Long Short Account Ratio ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, TopTraderLongShortAccountRatioObject &response) {

    if (auto error = val.get(response.long_short_ratios)) return error;

    return SUCCESS;
}
// --------------------------------------------------------

// ---------- Long Short Ratio ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, LongShortRatioObject &response) {

    if (auto error = val.get(response.long_short_ratios)) return error;

    return SUCCESS;
}
// -----------------------------------

// ---------- Taker Buy Sell Volume ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, BuySellVolume &buy_sell_volume) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "buySellRatio", buy_sell_volume.buy_sell_ratio)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "buyVol", buy_sell_volume.buy_vol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "sellVol", buy_sell_volume.sell_vol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timestamp", buy_sell_volume.timestamp)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, TakerBuySellVolumeObject &response) {

    if (auto error = val.get(response.buy_sell_volumes)) return error;

    return SUCCESS;
}
// -----------------------------------------

// ---------- Basis ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Basis &basis) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "indexPrice", basis.index_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "contractType", basis.contract_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "basisRate", basis.basis_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "futuresPrice", basis.futures_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "annualizedBasisRate", basis.annualized_basis_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "basis", basis.basis)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pair", basis.pair)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timestamp", basis.timestamp)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, BasisObject &response) {

    if (auto error = val.get(response.basis)) return error;

    return SUCCESS;
}
// ---------------------------

// ---------- Composite  Index Symbol Information ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, BaseAsset &base_asset) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "baseAsset", base_asset.base_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "quoteAsset", base_asset.quote_asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "weightInQuantity", base_asset.weight_in_quantity)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "weightInPercentage", base_asset.weight_in_percentage)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CompositeIndexSymbolInformation &composite_index_symbol_information) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", composite_index_symbol_information.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", composite_index_symbol_information.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "component", composite_index_symbol_information.component)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "baseAssetList", composite_index_symbol_information.base_asset_list)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CompositeIndexSymbolInformationObject &response) {

    if (auto error = val.get(response.composite_index_symbol_information)) return error;

    return SUCCESS;
}
// --------------------------------------------------------

// ---------- Multi Assets Mode Asset Index ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MultiAssetsModeAssetIndex &multi_assets_mode_asset_index) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", multi_assets_mode_asset_index.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", multi_assets_mode_asset_index.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "index", multi_assets_mode_asset_index.index)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bidBuffer", multi_assets_mode_asset_index.bid_buffer)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "askBuffer", multi_assets_mode_asset_index.ask_buffer)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bidRate", multi_assets_mode_asset_index.bid_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "askRate", multi_assets_mode_asset_index.ask_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "autoExchangeBidBuffer", multi_assets_mode_asset_index.auto_exchange_bid_buffer)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "autoExchangeAskBuffer", multi_assets_mode_asset_index.auto_exchange_ask_buffer)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "autoExchangeBidRate", multi_assets_mode_asset_index.auto_exchange_bid_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "autoExchangeAskRate", multi_assets_mode_asset_index.auto_exchange_ask_rate)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MultiAssetsModeAssetIndexObject &response) {

    if (val.type() == ondemand::json_type::object) {
        MultiAssetsModeAssetIndex multi_assets_mode_asset_index;
        if(auto error = val.get(multi_assets_mode_asset_index)) return error;
        response.data = std::move(multi_assets_mode_asset_index);
    }
    else {
        std::vector<MultiAssetsModeAssetIndex> multi_assets_mode_asset_indexes;
        if(auto error = val.get(multi_assets_mode_asset_indexes)) return error;
        response.data = std::move(multi_assets_mode_asset_indexes);
    }

    return SUCCESS;
}
// ------------------------------------------------

// ---------- Query Index Price Constituents ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Constituent &constituent) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "exchange", constituent.exchange)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "symbol", constituent.symbol)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryIndexPriceConstituentsObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", response.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "constituents", response.constituents)) return error;

    return SUCCESS;
}
// ---------------------------------------------------

} // namespace simdjson

//------------------------------------------------------------------------------------

namespace MarketData {

//------------------------------------------------------------------------------------

// REST API Endpoints

namespace RestAPI {

TestConnectivityResponse test_connectivity(DerivativesTrading &api) {
    std::string const url = "/fapi/v1/ping";

    std::string response = api.query(url);

    return api.parse_response<TestConnectivityObject>(response);
}

CheckServerTimeResponse check_server_time(DerivativesTrading &api) {
    std::string const url = "/fapi/v1/time";

    std::string response = api.query(url);

    return api.parse_response<CheckServerTimeObject>(response);
}

ExchangeInformationResponse exchange_information(DerivativesTrading &api) {
    std::string const url = "/fapi/v1/exchangeInfo";

    std::string response = api.query(url);

    return api.parse_response<ExchangeInformationObject>(response);
}

OrderBookResponse order_book(DerivativesTrading &api, std::string const &symbol, int16_t const limit) {
    std::string const url = "/fapi/v1/depth";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<OrderBookObject>(response);
}

RecentTradesListResponse recent_trades_list(DerivativesTrading &api, std::string const &symbol, int16_t const limit) {
    std::string const url = "/fapi/v1/trades";
    
    API::Parameters params;
    params.emplace_back("symbol", symbol);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<RecentTradesListObject>(response);
}

OldTradesLookupResponse old_trades_lookup(DerivativesTrading &api, std::string const &symbol, int16_t const limit, int64_t const from_id) {
    std::string const url = "/fapi/v1/historicalTrades";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    if (limit != -1) params.emplace_back("limit", limit);
    if (from_id != -1) params.emplace_back("fromId", from_id);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<OldTradesLookupObject>(response);
}

CompressedAggregateTradesListResponse compressed_aggregate_trades_list(DerivativesTrading &api, std::string const &symbol, int64_t const from_id, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/aggTrades";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    if (from_id != -1) params.emplace_back("fromId", from_id);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<CompressedAggregateTradesListObject>(response);
}

KlineCandlestickDataResponse kline_candlestick_data(DerivativesTrading &api, std::string const &symbol, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/klines";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);
    
    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<KlineCandlestickDataObject>(response);
}

ContinuousContractKlineCandlestickDataResponse continuous_contract_kline_candlestick_data(DerivativesTrading &api, std::string const &pair, std::string const &contract_type, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/continuousKlines";

    API::Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("contractType", contract_type);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<ContinuousContractKlineCandlestickDataObject>(response);
}

IndexPriceKlineCandlestickDataResponse index_price_kline_candlestick_data(DerivativesTrading &api, std::string const &pair, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/indexPriceKlines";

    API::Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<IndexPriceKlineCandlestickDataObject>(response);
}

MarkPriceKlineCandlestickDataResponse mark_price_kline_candlestick_data(DerivativesTrading &api, std::string const &pair, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/markPriceKlines";

    API::Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<MarkPriceKlineCandlestickDataObject>(response);
}

PremiumIndexKlineDataResponse premium_index_kline_data(DerivativesTrading &api, std::string const &symbol, std::string const &interval, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/premiumIndexKlines";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("interval", interval);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<PremiumIndexKlineDataObject>(response);
}

MarkPriceResponse mark_price(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/premiumIndex";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<MarkPriceObject>(response);
}

GetFundingRateHistoryResponse get_funding_rate_history(DerivativesTrading &api, std::string const &symbol, int64_t const start_time, int64_t const end_time, int16_t const limit) {
    std::string const url = "/fapi/v1/fundingRate";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);
    if (limit != -1) params.emplace_back("limit", limit);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<GetFundingRateHistoryObject>(response);
}

GetFundingRateInfoResponse get_funding_rate_info(DerivativesTrading &api) {
    std::string const url = "/fapi/v1/fundingInfo";

    std::string response = api.query(url);

    return api.parse_response<GetFundingRateInfoObject>(response);
}

Ticker24hrPriceChangeStatisticsResponse ticker_24hr_price_change_statistics(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/ticker/24hr";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<Ticker24hrPriceChangeStatisticsObject>(response);
}

SymbolPriceTickerResponse symbol_price_ticker(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/ticker/price";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<SymbolPriceTickerObject>(response);
}

SymbolPriceTickerV2Response symbol_price_ticker_v2(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v2/ticker/price";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<SymbolPriceTickerV2Object>(response);
}

SymbolOrderBookTickerResponse symbol_order_book_ticker(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/ticker/bookTicker";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<SymbolOrderBookTickerObject>(response);
}

QueryDeliveryPriceResponse query_delivery_price(DerivativesTrading &api, std::string const &pair) {
    std::string const url = "/futures/data/delivery-price";

    API::Parameters params;
    params.emplace_back("pair", pair);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<QueryDeliveryPriceObject>(response);
}

OpenInterestResponse open_interest(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/openInterest";

    API::Parameters params;
    params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<OpenInterestObject>(response);
}

OpenInterestStatisticsResponse open_interest_statistics(DerivativesTrading &api, std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/fapi/v1/openInterestHist";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<OpenInterestStatisticsObject>(response);
}

TopTraderLongShortPositionRatioResponse top_trader_long_short_position_ratio(DerivativesTrading &api, std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/topLongShortPositionRatio";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<TopTraderLongShortPositionRatioObject>(response);
}

TopTraderLongShortAccountRatioResponse top_trader_long_short_account_ratio(DerivativesTrading &api, std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/topLongShortAccountRatio";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<TopTraderLongShortAccountRatioObject>(response);
}

LongShortRatioResponse long_short_ratio(DerivativesTrading &api, std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/globalLongShortAccountRatio";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<LongShortRatioObject>(response);
}

TakerBuySellVolumeResponse taker_buy_sell_volume(DerivativesTrading &api, std::string const &symbol, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/takerlongshortRatio";

    API::Parameters params;
    params.emplace_back("symbol", symbol);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<TakerBuySellVolumeObject>(response);
}

BasisResponse basis(DerivativesTrading &api, std::string const &pair, std::string const &contract_type, std::string const &period, int16_t const limit, int64_t const start_time, int64_t const end_time) {
    std::string const url = "/futures/data/basis";

    API::Parameters params;
    params.emplace_back("pair", pair);
    params.emplace_back("contractType", contract_type);
    params.emplace_back("period", period);
    if (limit != -1) params.emplace_back("limit", limit);
    if (start_time != -1) params.emplace_back("startTime", start_time);
    if (end_time != -1) params.emplace_back("endTime", end_time);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<BasisObject>(response);
}

CompositeIndexSymbolInformationResponse composite_index_symbol_information(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/indexInfo";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<CompositeIndexSymbolInformationObject>(response);
}

MultiAssetsModeAssetIndexResponse multi_assets_mode_asset_index(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/assetIndex";

    API::Parameters params;
    if (!symbol.empty()) params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<MultiAssetsModeAssetIndexObject>(response);
}

QueryIndexPriceConstituentsResponse query_index_price_constituents(DerivativesTrading &api, std::string const &symbol) {
    std::string const url = "/fapi/v1/constituents";

    API::Parameters params;
    params.emplace_back("symbol", symbol);

    std::string response = api.send_request<API::RequestType::GET>(url, params);

    return api.parse_response<QueryIndexPriceConstituentsObject>(response);
}

} // namespace RestAPI

//------------------------------------------------------------------------------------

} // namespace MarketData

//------------------------------------------------------------------------------------
