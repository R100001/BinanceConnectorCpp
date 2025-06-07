
//------------------------------------------------------------------------------------

#ifndef MARKET_DATA_HPP
#define MARKET_DATA_HPP

//------------------------------------------------------------------------------------

#include "api.hpp"
#include "error.hpp"

//------------------------------------------------------------------------------------

namespace MarketData {

//------------------------------------------------------------------------------------

// Response Objects

struct ExchangeFilter {};

struct FilterPriceFilter {
    std::string filter_type;
    std::string min_price;
    std::string max_price;
    std::string tick_size;
};

struct FilterLotSize {
    std::string filter_type;
    std::string min_qty;
    std::string max_qty;
    std::string step_size;
};

struct FilterMarketLotSize {
    std::string filter_type;
    std::string min_qty;
    std::string max_qty;
    std::string step_size;
};

struct FilterMaxNumOrders {
    std::string filter_type;
    int32_t limit;
};

struct FilterMaxNumAlgoOrders {
    std::string filter_type;
    int32_t limit;
};

struct FilterMinNotional {
    std::string filter_type;
    std::string notional;
};

struct FilterPercentPrice {
    std::string filter_type;
    std::string multiplier_up;
    std::string multiplier_down;
    std::string multiplier_decimal;
};

using Filter = std::variant<FilterPriceFilter, FilterLotSize, FilterMarketLotSize, FilterMaxNumOrders, FilterMaxNumAlgoOrders, FilterMinNotional, FilterPercentPrice>;

struct RateLimit {
    std::string rate_limit_type;
    std::string interval;
    int32_t interval_num;
    int32_t limit;
};

struct Asset {
    std::string asset;
    std::string auto_asset_exchange;
    bool margin_available;
};

struct Symbol {
    std::vector<Filter> filters;
    std::vector<std::string> underlying_sub_type;
    std::vector<std::string> order_types;
    std::vector<std::string> time_in_force;
    std::string symbol;
    std::string pair;
    std::string contract_type;
    std::string status;
    std::string maint_margin_percent;
    std::string required_margin_percent;
    std::string base_asset;
    std::string quote_asset;
    std::string margin_asset;
    std::string underlying_type;
    std::string trigger_protect;
    std::string liquidation_fee;
    std::string market_take_bound;
    int64_t delivery_date;
    int64_t onboard_date;
    int32_t max_move_order_limit;
    int8_t price_precision;
    int8_t quantity_precision;
    int8_t base_asset_precision;
    int8_t quote_precision;
};

struct BidAskEntry {
    std::string price;
    std::string qty;
};

struct Trade {
    int64_t id;
    std::string price;
    std::string qty;
    std::string quote_qty;
    int64_t time;
    bool is_buyer_maker;
};

struct AggregatedTrade {
    uint64_t a;
    std::string p;
    std::string q;
    uint64_t f;
    uint64_t l;
    uint64_t T;
    bool m;
};

using KlineDataTypes = std::variant<int64_t, std::string>;

struct MarkPrice {
    std::string symbol;
    std::string mark_price;
    std::string index_price;
    std::string estimated_settle_price;
    std::string last_funding_rate;
    std::string interest_rate;
    int64_t next_funding_time;
    int64_t time;
};

using MarkPriceData = std::variant<MarkPrice, std::vector<MarkPrice>>;

struct FundingRate {
    std::string symbol;
    std::string funding_rate;
    int64_t funding_time;
    std::string mark_price;
};

struct FundingRateAdjustments {
    std::string symbol;
    std::string adjusted_funding_rate_cap;
    std::string adjusted_funding_rate_floor;
    int8_t funding_interval_hours;
    bool disclaimer;
};

struct PriceChangeStatistics24Hours {
    std::string symbol;
    std::string price_change;
    std::string price_change_percent;
    std::string weighted_avg_price;
    std::string last_price;
    std::string last_qty;
    std::string open_price;
    std::string high_price;
    std::string low_price;
    std::string volume;
    std::string quote_volume;
    int64_t open_time;
    int64_t close_time;
    int64_t first_id;
    int64_t last_id;
    int64_t count;
};

using Ticker24hrPriceChangeStatistics = std::variant<PriceChangeStatistics24Hours, std::vector<PriceChangeStatistics24Hours>>;

struct PriceTicker {
    std::string symbol;
    std::string price;
    int64_t time;
};

using SymbolPriceTicker = std::variant<PriceTicker, std::vector<PriceTicker>>;

struct OrderBookTicker {
    std::string symbol;
    std::string bid_price;
    std::string bid_qty;
    std::string ask_price;
    std::string ask_qty;
    int64_t time;
};

using SymbolOrderBookTicker = std::variant<OrderBookTicker, std::vector<OrderBookTicker>>;

struct DeliveryPrice {
    int64_t delivery_time;
    double delivery_price;
};

struct OpenInterestStatistics {
    std::string symbol;
    std::string sum_open_interest;
    std::string sum_open_interest_value;
    std::string timestamp;
};

struct LongShortRatio {
    std::string symbol;
    std::string long_short_ratio;
    std::string long_account;
    std::string short_account;
    std::string timestamp;
};

struct BuySellVolume {
    std::string buy_sell_ratio;
    std::string buy_vol;
    std::string sell_vol;
    std::string timestamp;
};

struct BaseAsset {
    std::string base_asset;
    std::string quote_asset;
    std::string weight_in_quantity;
    std::string weight_in_percentage;
};

struct CompositeIndexSymbolInformation {
    std::string symbol;
    std::string component;
    int64_t time;
    std::vector<BaseAsset> base_asset_list;
};

struct MultiAssetsModeAssetIndex {
    std::string symbol;
    std::string index;
    std::string bid_buffer;
    std::string ask_buffer;
    std::string bid_rate;
    std::string ask_rate;
    std::string auto_exchange_bid_buffer;
    std::string auto_exchange_ask_buffer;
    std::string auto_exchange_bid_rate;
    std::string auto_exchange_ask_rate;
    int64_t time;
};

using MultiAssetsModeAssetIndexData = std::variant<MultiAssetsModeAssetIndex, std::vector<MultiAssetsModeAssetIndex>>;

struct Constituent {
    std::string exchange;
    std::string symbol;
};

//------------------------------------------------------------------------------------

// Response Structs

struct TestConnectivityObject {};
using TestConnectivityResponse = API::ResponseOrError<TestConnectivityObject>;

struct CheckServerTimeObject {
    int64_t server_time;
};
using CheckServerTimeResponse = API::ResponseOrError<CheckServerTimeObject>;

struct ExchangeInformationObject {
    std::vector<ExchangeFilter> exchange_filters;
    std::vector<RateLimit> rate_limits;
    std::vector<Symbol> symbols;
    std::vector<Asset> assets;
    std::string futures_type;
    int64_t server_time;
    std::string timezone;
};
using ExchangeInformationResponse = API::ResponseOrError<ExchangeInformationObject>;

struct OrderBookObject {
    uint64_t last_update_id;
    uint64_t E;
    uint64_t T;
    std::vector<BidAskEntry> bids;
    std::vector<BidAskEntry> asks;
};
using OrderBookResponse = API::ResponseOrError<OrderBookObject>;

struct RecentTradesListObject {
    std::vector<Trade> trades;
};
using RecentTradesListResponse = API::ResponseOrError<RecentTradesListObject>;

struct OldTradesLookupObject {
    std::vector<Trade> trades;
};
using OldTradesLookupResponse = API::ResponseOrError<OldTradesLookupObject>;

struct CompressedAggregateTradesListObject {
    std::vector<AggregatedTrade> trades;
};
using CompressedAggregateTradesListResponse = API::ResponseOrError<CompressedAggregateTradesListObject>;

struct KlineCandlestickDataObject {
    std::vector<std::array<KlineDataTypes, 12>> klines;
};
using KlineCandlestickDataResponse = API::ResponseOrError<KlineCandlestickDataObject>;

struct ContinuousContractKlineCandlestickDataObject {
    std::vector<std::array<KlineDataTypes, 12>> klines;
};
using ContinuousContractKlineCandlestickDataResponse = API::ResponseOrError<ContinuousContractKlineCandlestickDataObject>;

struct IndexPriceKlineCandlestickDataObject {
    std::vector<std::array<KlineDataTypes, 12>> klines;
};
using IndexPriceKlineCandlestickDataResponse = API::ResponseOrError<IndexPriceKlineCandlestickDataObject>;

struct MarkPriceKlineCandlestickDataObject {
    std::vector<std::array<KlineDataTypes, 12>> klines;
};
using MarkPriceKlineCandlestickDataResponse = API::ResponseOrError<MarkPriceKlineCandlestickDataObject>;

struct PremiumIndexKlineDataObject {
    std::vector<std::array<KlineDataTypes, 12>> klines;
};
using PremiumIndexKlineDataResponse = API::ResponseOrError<PremiumIndexKlineDataObject>;

struct MarkPriceObject {
    MarkPriceData data;
};
using MarkPriceResponse = API::ResponseOrError<MarkPriceObject>;

struct GetFundingRateHistoryObject {
    std::vector<FundingRate> funding_rates;
};
using GetFundingRateHistoryResponse = API::ResponseOrError<GetFundingRateHistoryObject>;

struct GetFundingRateInfoObject {
    std::vector<FundingRateAdjustments> funding_rate_adjustments;
};
using GetFundingRateInfoResponse = API::ResponseOrError<GetFundingRateInfoObject>;

struct Ticker24hrPriceChangeStatisticsObject {
    Ticker24hrPriceChangeStatistics data;
};
using Ticker24hrPriceChangeStatisticsResponse = API::ResponseOrError<Ticker24hrPriceChangeStatisticsObject>;

struct SymbolPriceTickerObject {
    SymbolPriceTicker data;
};
using SymbolPriceTickerResponse = API::ResponseOrError<SymbolPriceTickerObject>;

struct SymbolPriceTickerV2Object {
    SymbolPriceTicker data;
};
using SymbolPriceTickerV2Response = API::ResponseOrError<SymbolPriceTickerV2Object>;

struct SymbolOrderBookTickerObject {
    SymbolOrderBookTicker data;
};
using SymbolOrderBookTickerResponse = API::ResponseOrError<SymbolOrderBookTickerObject>;

struct QueryDeliveryPriceObject {
    std::vector<DeliveryPrice> delivery_prices;
};
using QueryDeliveryPriceResponse = API::ResponseOrError<QueryDeliveryPriceObject>;

struct OpenInterestObject {
    std::string open_interest;
    std::string symbol;
    int64_t time;
};
using OpenInterestResponse = API::ResponseOrError<OpenInterestObject>;

struct OpenInterestStatisticsObject {
    std::vector<OpenInterestStatistics> open_interest_statistics;
};
using OpenInterestStatisticsResponse = API::ResponseOrError<OpenInterestStatisticsObject>;

struct TopTraderLongShortPositionRatioObject {
    std::vector<LongShortRatio> long_short_ratios;
};
using TopTraderLongShortPositionRatioResponse = API::ResponseOrError<TopTraderLongShortPositionRatioObject>;

struct TopTraderLongShortAccountRatioObject {
    std::vector<LongShortRatio> long_short_ratios;
};
using TopTraderLongShortAccountRatioResponse = API::ResponseOrError<TopTraderLongShortAccountRatioObject>;

struct LongShortRatioObject {
    std::vector<LongShortRatio> long_short_ratios;
};
using LongShortRatioResponse = API::ResponseOrError<LongShortRatioObject>;

struct TakerBuySellVolumeObject {
    std::vector<BuySellVolume> buy_sell_volumes;
};
using TakerBuySellVolumeResponse = API::ResponseOrError<TakerBuySellVolumeObject>;

struct Basis {
    std::string index_price;
    std::string contract_type;
    std::string basis_rate;
    std::string futures_price;
    std::string annualized_basis_rate;
    std::string basis;
    std::string pair;
    int64_t timestamp;
};
struct BasisObject {
    std::vector<Basis> basis;
};
using BasisResponse = API::ResponseOrError<BasisObject>;

struct CompositeIndexSymbolInformationObject {
    std::vector<CompositeIndexSymbolInformation> composite_index_symbol_information;
};
using CompositeIndexSymbolInformationResponse = API::ResponseOrError<CompositeIndexSymbolInformationObject>;

struct MultiAssetsModeAssetIndexObject {
    MultiAssetsModeAssetIndexData data;
};
using MultiAssetsModeAssetIndexResponse = API::ResponseOrError<MultiAssetsModeAssetIndexObject>;

struct QueryIndexPriceConstituentsObject {
    std::string symbol;
    std::vector<Constituent> constituents;
    int64_t time;
};
using QueryIndexPriceConstituentsResponse = API::ResponseOrError<QueryIndexPriceConstituentsObject>;

//------------------------------------------------------------------------------------

// REST API Endpoints

namespace RestAPI {

TestConnectivityResponse                        test_connectivity(API &api);
CheckServerTimeResponse                         check_server_time(API &api);
ExchangeInformationResponse                     exchange_information(API &api);
OrderBookResponse                               order_book(API &api, std::string const &symbol, int16_t const limit = -1);
RecentTradesListResponse                        recent_trades_list(API &api, std::string const &symbol, int16_t const limit = -1);
OldTradesLookupResponse                         old_trades_lookup(API &api, std::string const &symbol, int16_t const limit = -1, int64_t const from_id = -1);
CompressedAggregateTradesListResponse           compressed_aggregate_trades_list(API &api, std::string const &symbol, int64_t const from_id = -1, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
KlineCandlestickDataResponse                    kline_candlestick_data(API &api, std::string const &symbol, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
ContinuousContractKlineCandlestickDataResponse  continuous_contract_kline_candlestick_data(API &api, std::string const &pair, std::string const &contract_type, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
IndexPriceKlineCandlestickDataResponse          index_price_kline_candlestick_data(API &api, std::string const &pair, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
MarkPriceKlineCandlestickDataResponse           mark_price_kline_candlestick_data(API &api, std::string const &pair, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
PremiumIndexKlineDataResponse                   premium_index_kline_data(API &api, std::string const &symbol, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
MarkPriceResponse                               mark_price(API &api, std::string const &symbol = "");
GetFundingRateHistoryResponse                   get_funding_rate_history(API &api, std::string const &symbol = "", int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
GetFundingRateInfoResponse                      get_funding_rate_info(API &api);
Ticker24hrPriceChangeStatisticsResponse         ticker_24hr_price_change_statistics(API &api, std::string const &symbol = "");
SymbolPriceTickerResponse                       symbol_price_ticker(API &api, std::string const &symbol = "");
SymbolPriceTickerV2Response                     symbol_price_ticker_v2(API &api, std::string const &symbol = "");
SymbolOrderBookTickerResponse                   symbol_order_book_ticker(API &api, std::string const &symbol = "");
QueryDeliveryPriceResponse                      query_delivery_price(API &api, std::string const &pair);
OpenInterestResponse                            open_interest(API &api, std::string const &symbol);
OpenInterestStatisticsResponse                  open_interest_statistics(API &api, std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
TopTraderLongShortPositionRatioResponse         top_trader_long_short_position_ratio(API &api, std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
TopTraderLongShortAccountRatioResponse          top_trader_long_short_account_ratio(API &api, std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
LongShortRatioResponse                          long_short_ratio(API &api, std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
TakerBuySellVolumeResponse                      taker_buy_sell_volume(API &api, std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
BasisResponse                                   basis(API &api, std::string const &pair, std::string const &contract_type, std::string const &period, int16_t const &limit = -1, int64_t const &start_time = -1, int64_t const &end_time = -1);
CompositeIndexSymbolInformationResponse         composite_index_symbol_information(API &api, std::string const &symbol = "");
MultiAssetsModeAssetIndexResponse               multi_assets_mode_asset_index(API &api, std::string const &symbol = "");
QueryIndexPriceConstituentsResponse             query_index_price_constituents(API &api, std::string const &symbol);

} // namespace RestAPI

//------------------------------------------------------------------------------------

// Websocket API Endpoints

namespace WebsocketAPI {

//------------------------------------------------------------------------------------

void order_book(API &api, std::string const &symbol, int16_t const &limit = -1);
void symbol_ticker_price(API &api, std::string const &symbol = "");
void symbol_order_book_ticker(API &api, std::string const &symbol = "");

//------------------------------------------------------------------------------------

} // namespace WebsocketAPI

//------------------------------------------------------------------------------------

} // namespace MarketData

//------------------------------------------------------------------------------------

#endif // MARKET_DATA_HPP

//------------------------------------------------------------------------------------
