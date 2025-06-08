
//------------------------------------------------------------------------------------

#ifndef API_HPP
#define API_HPP

//------------------------------------------------------------------------------------

#include <string>
#include <vector>
#include <variant>
#include <memory>

#include "simdjson.h"

#include "api_declarations.hpp"

#include "account.hpp"
#include "convert.hpp"
#include "market_data.hpp"
#include "portfolio_margin_endpoints.hpp"
#include "trade.hpp"

#include "WebSocketClient.hpp"
#include "HTTPClient.hpp"
#include "utils.hpp"

//------------------------------------------------------------------------------------
//----------------------------------------API-----------------------------------------
//------------------------------------------------------------------------------------

class API {

public: // Typedefs

    using MsgCallbackT = std::function<void(std::string_view)>;
    using ErrCallbackT = std::function<void(std::string_view)>;

    enum class RequestType {
        GET,
        POST,
        PUT,
        DELETE
    };

    enum class RequestFormat {
        QueryString,
        JSON
    };

public: // Constructors

    API(
        std::string_view key,
        std::string_view secret = "",
        int32_t const timeout = -1,
        std::string_view proxy = "",
        bool const show_limit_usage = false,
        bool const show_header = false,
        std::string_view private_key = "",
        std::string_view private_key_passphrase = ""
    );

public: // Rest API

    // Account Endpoints
    Account::NewFutureAccountTransferResponse                        new_future_account_transfer(std::string const &type, std::string const &asset, double const amount, std::string const &from_symbol = "", std::string const &to_symbol = "", int32_t const recv_window = -1);
    Account::FuturesAccountBalanceV3Response                         futures_account_balance_v3(int32_t const recv_window = -1);
    Account::FuturesAccountBalanceResponse                           futures_account_balance(int32_t const recv_window = -1);
    Account::AccountInformationV3Response                            account_information_v3(int32_t const recv_window = -1);
    Account::AccountInformationResponse                              account_information(int32_t const recv_window = -1);
    Account::GetFutureAccountTransactionHistoryListResponse          get_future_account_transaction_history_list(std::string const &type, int64_t const start_time = -1, int64_t const end_time = -1, int32_t const current = -1, int8_t const size = -1, std::string const &from_symbol = "", std::string const &to_symbol = "", int32_t const recv_window = -1);
    Account::UserCommissionRateResponse                              user_commission_rate(std::string const &symbol, int32_t const recv_window = -1);
    Account::QueryAccountConfigurationResponse                       query_account_configuration(int32_t const recv_window = -1);
    Account::QuerySymbolConfigurationResponse                        query_symbol_configuration(std::string const &symbol = "", int32_t const recv_window = -1);
    Account::QueryOrderRateLimitResponse                             query_order_rate_limit(int32_t const recv_window = -1);
    Account::NotionalAndLeverageBracketsResponse                     notional_and_leverage_brackets(std::string const &symbol = "", int32_t const recv_window = -1);
    Account::GetCurrentMultiAssetsModeResponse                       get_current_multi_assets_mode(int32_t const recv_window = -1);
    Account::GetCurrentPositionModeResponse                          get_current_position_mode(int32_t const recv_window = -1);
    Account::GetIncomeHistoryResponse                                get_income_history(std::string const &symbol = "", std::string const &income_type = "", int64_t const start_time = -1, int64_t const end_time = -1, int32_t const page = -1, int16_t const limit = -1, int32_t const recv_window = -1);
    Account::FuturesTradingQuantitativeRulesIndicatorsResponse       futures_trading_quantitative_rules_indicators(std::string const &symbol = "", int32_t const recv_window = -1);
    Account::GetDownloadIdForFuturesTransactionHistoryResponse       get_download_id_for_futures_transaction_history(int64_t const start_time, int64_t const end_time, int32_t const recv_window = -1);
    Account::GetFuturesTransactionHistoryDownloadLinkByIdResponse    get_futures_transaction_history_download_link_by_id(std::string const &download_id, int32_t const recv_window = -1);
    Account::GetDownloadIdForFuturesOrderHistoryResponse             get_download_id_for_futures_order_history(int64_t const start_time, int64_t const end_time, int32_t const recv_window = -1);
    Account::GetFuturesOrderHistoryDownloadLinkByIdResponse          get_futures_order_history_download_link_by_id(std::string const &download_id, int32_t const recv_window = -1);
    Account::GetDownloadIdForFuturesTradeHistoryResponse             get_download_if_for_futures_trade_history(int64_t const start_time, int64_t const end_time, int32_t const recv_window = -1);
    Account::GetFuturesTradeDownloadLinkByIdResponse                 get_futures_trade_download_link_by_id(std::string const &download_id, int32_t const recv_window = -1);
    Account::ToggleBnbBurnOnFuturesTradeResponse                     toggle_bnb_burn_on_futures_trade(bool const feeBurn, int32_t const recv_window = -1);
    Account::GetBnbBurnStatusResponse                                get_bnb_burn_status(int32_t const recv_window = -1);

    // Convert Endpoints
    Convert::ListAllConvertedPairsResponse   list_all_converted_pairs(std::string const &from_asset = "", std::string const &to_asset = "");
    Convert::SendQuoteRequestResponse        send_quote_request(std::string const &from_asset, std::string const &to_asset, double const from_amount = -1, double const to_amount = -1, std::string const valid_time = "", int32_t const recv_window = -1);
    Convert::AcceptQuoteResponse             accept_quote(std::string const &quote_id, int32_t const recv_window = -1);
    Convert::OrderStatusResponse             order_status(std::string const &order_id = "", std::string const &quote_id = "");

    // Market Data Endpoints
    MarketData::TestConnectivityResponse                        test_connectivity();
    MarketData::CheckServerTimeResponse                         check_server_time();
    MarketData::ExchangeInformationResponse                     exchange_information();
    MarketData::OrderBookResponse                               order_book(std::string const &symbol, int16_t const limit = -1);
    MarketData::RecentTradesListResponse                        recent_trades_list(std::string const &symbol, int16_t const limit = -1);
    MarketData::OldTradesLookupResponse                         old_trades_lookup(std::string const &symbol, int16_t const limit = -1, int64_t const from_id = -1);
    MarketData::CompressedAggregateTradesListResponse           compressed_aggregate_trades_list(std::string const &symbol, int64_t const from_id = -1, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
    MarketData::KlineCandlestickDataResponse                    kline_candlestick_data(std::string const &symbol, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
    MarketData::ContinuousContractKlineCandlestickDataResponse  continuous_contract_kline_candlestick_data(std::string const &pair, std::string const &contract_type, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
    MarketData::IndexPriceKlineCandlestickDataResponse          index_price_kline_candlestick_data(std::string const &pair, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
    MarketData::MarkPriceKlineCandlestickDataResponse           mark_price_kline_candlestick_data(std::string const &pair, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
    MarketData::PremiumIndexKlineDataResponse                   premium_index_kline_data(std::string const &symbol, std::string const &interval, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
    MarketData::MarkPriceResponse                               mark_price(std::string const &symbol = "");
    MarketData::GetFundingRateHistoryResponse                   get_funding_rate_history(std::string const &symbol = "", int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1);
    MarketData::GetFundingRateInfoResponse                      get_funding_rate_info();
    MarketData::Ticker24hrPriceChangeStatisticsResponse         ticker_24hr_price_change_statistics(std::string const &symbol = "");
    MarketData::SymbolPriceTickerResponse                       symbol_price_ticker(std::string const &symbol = "");
    MarketData::SymbolPriceTickerV2Response                     symbol_price_ticker_v2(std::string const &symbol = "");
    MarketData::SymbolOrderBookTickerResponse                   symbol_order_book_ticker(std::string const &symbol = "");
    MarketData::QueryDeliveryPriceResponse                      query_delivery_price(std::string const &pair);
    MarketData::OpenInterestResponse                            open_interest(std::string const &symbol);
    MarketData::OpenInterestStatisticsResponse                  open_interest_statistics(std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
    MarketData::TopTraderLongShortPositionRatioResponse         top_trader_long_short_position_ratio(std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
    MarketData::TopTraderLongShortAccountRatioResponse          top_trader_long_short_account_ratio(std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
    MarketData::LongShortRatioResponse                          long_short_ratio(std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
    MarketData::TakerBuySellVolumeResponse                      taker_buy_sell_volume(std::string const &symbol, std::string const &period, int16_t const limit = -1, int64_t const start_time = -1, int64_t const end_time = -1);
    MarketData::BasisResponse                                   basis(std::string const &pair, std::string const &contract_type, std::string const &period, int16_t const &limit = -1, int64_t const &start_time = -1, int64_t const &end_time = -1);
    MarketData::CompositeIndexSymbolInformationResponse         composite_index_symbol_information(std::string const &symbol = "");
    MarketData::MultiAssetsModeAssetIndexResponse               multi_assets_mode_asset_index(std::string const &symbol = "");
    MarketData::QueryIndexPriceConstituentsResponse             query_index_price_constituents(std::string const &symbol);

    // Portfolio Margin Endpoints
    PortfolioMarginEndpoints::ClassicPortfolioMarginAccountInformationResponse classic_portfolio_margin_account_information(std::string const &asset, int32_t const recv_window = -1);

    // Trade Endpoints

    Trade::NewOrderResponse                        new_order(Trade::NewOrder const &order, bool const close_position = false, int32_t const recv_window = -1);
    Trade::PlaceMultipleOrdersResponse             place_multiple_orders(std::vector<Trade::NewOrder> const &orders, int32_t const recv_window = -1);
    Trade::ModifyOrderResponse                     modify_order(Trade::ModifyOrder const &order, int32_t const recv_window = -1);
    Trade::ModifyMultipleOrdersResponse            modify_multiple_orders(std::vector<Trade::ModifyOrder> const &orders, int32_t const recv_window = -1);
    Trade::GetOrderModifyHistoryResponse           get_order_modify_history(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int64_t const start_time = -1, int64_t const end_time = -1, int8_t const limit = -1, int32_t const recv_window = -1);
    Trade::CancelOrderResponse                     cancel_order(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
    Trade::CancelMultipleOrdersResponse            cancel_multiple_orders(std::string const &symbol, std::vector<int64_t> const &order_ids, std::vector<std::string> const &orig_client_order_ids, int32_t const recv_window = -1);
    Trade::CancelAllOpenOrdersResponse             cancel_all_open_orders(std::string const &symbol, int32_t const recv_window = -1);
    Trade::AutoCancelAllOpenOrdersResponse         auto_cancel_all_open_orders(std::string const &symbol, int64_t const countdown_time, int32_t const recv_window = -1);
    Trade::QueryOrderResponse                      query_order(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
    Trade::QueryAllOrdersResponse                  query_all_orders(std::string const &symbol, int64_t const order_id = -1, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1, int32_t const recv_window = -1);
    Trade::QueryCurrentAllOpenOrdersResponse       query_current_all_open_orders(std::string const &symbol = "", int32_t const recv_window = -1);
    Trade::QueryCurrentOpenOrderResponse           query_current_open_order(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
    Trade::QueryUsersForceOrdersResponse           query_users_force_orders(std::string const &symbol = "", std::string const &auto_close_type = "", int64_t const start_time = -1, int64_t const end_time = -1, int8_t const limit = -1, int32_t const recv_window = -1);
    Trade::QueryAccountTradeListResponse           query_account_trade_list(std::string const &symbol, int64_t const order_id = -1, int64_t const start_time = -1, int64_t const end_time = -1, int64_t const from_id = -1, int16_t const limit = -1, int32_t const recv_window = -1);
    Trade::ChangeMarginTypeResponse                change_margin_type(std::string const &symbol, std::string const &margin_type, int32_t const recv_window = -1);
    Trade::ChangePositionModeResponse              change_position_mode(std::string const &dual_side_position, int32_t const recv_window = -1);
    Trade::ChangeInitialLeverageResponse           change_initial_leverage(std::string const &symbol, int8_t const leverage, int32_t const recv_window = -1);
    Trade::ChangeMultiAssetsModeResponse           change_multi_assets_mode(std::string const &multi_assets_margin, int32_t const recv_window = -1);
    Trade::ModifyIsolatedPositionMarginResponse    modify_isolated_position_margin(std::string const &symbol, double const amount, int8_t const type, std::string const &position_side, int32_t const recv_window = -1);
    Trade::PositionInformationV2Response           position_information_v2(std::string const &symbol = "", int32_t const recv_window = -1);
    Trade::PositionInformationV3Response           position_information_v3(std::string const &symbol = "", int32_t const recv_window = -1);
    Trade::PositionAdlQuantileEstimationResponse   position_adl_quantile_estimation(std::string const &symbol = "", int32_t const recv_window = -1);
    Trade::GetPositionMarginChangeHistoryResponse  get_position_margin_change_history(std::string const &symbol, int8_t const type, int64_t const start_time = -1, int64_t const end_time = -1, int32_t const limit = -1, int32_t const recv_window = -1);
    Trade::TestNewOrderResponse                    test_new_order(Trade::NewOrder const &order, bool const close_position = false, int32_t const recv_window = -1);


public: // Websocket Streams

    // Account Streams
    void futures_account_balance_v2_stream(int32_t const recv_window = -1);
    void futures_account_balance_stream(int32_t const recv_window = -1);
    void account_information_v2_stream(int32_t const recv_window = -1);
    void account_information_stream(int32_t const recv_window = -1);

    // Convert Streams

    // Market Data Streams
    void order_book_stream(std::string const &symbol, int16_t const &limit = -1);
    void symbol_ticker_price_stream(std::string const &symbol = "");
    void symbol_order_book_ticker_stream(std::string const &symbol = "");

    // Portfolio Margin Streams
    
    // Trade Streams
    void new_order_stream(Trade::NewOrder const &order, bool const close_position = false, int32_t const recv_window = -1);
    void modify_order_stream(Trade::ModifyOrder const &order, int32_t const recv_window = -1);
    void cancel_order_stream(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
    void query_order_stream(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
    void position_information_v2_stream(std::string const &symbol = "", int32_t const recv_window = -1);
    void position_information_stream(std::string const &symbol = "", int32_t const recv_window = -1);


public: // WebSocket API

    void ws_api_connect();
    void ws_api_disconnect();
    void ws_api_send_message(std::string_view message);

    void ws_api_message_callback(MsgCallbackT callback);
    void ws_api_error_callback(ErrCallbackT callback);

public: // Websocket Market Streams

    void ws_market_streams_subscribe(std::string const &stream_name);
    void ws_market_streams_subscribe(std::vector<std::string> const &stream_names);
    void ws_market_streams_unsubscribe(std::string const &stream_name);
    void ws_market_streams_unsubscribe(std::vector<std::string> const &stream_names);
    std::string ws_market_streams_list_subscriptions() const;

    void ws_market_streams_message_callback(MsgCallbackT callback);
    void ws_market_streams_error_callback(ErrCallbackT callback);

public: // Websocket User Data Streams

    void ws_user_data_streams_start();
    void ws_user_data_streams_stop();

    void ws_user_data_streams_message_callback(MsgCallbackT callback);
    void ws_user_data_streams_error_callback(ErrCallbackT callback);

public: // REST API request methods

    template <RequestType req_type> std::string sign_request(std::string_view endpoint, Parameters &payload);
    template <RequestType req_type> std::string send_request(std::string_view endpoint, Parameters const &payload = {}); 

public: // Public message parsing

    /*----- Parsing Tags -----*/
    struct ArrayErrors {};
    struct ResponseIsServerMessage {};

    /*----- Parsing Functions -----*/
    template <typename JsonResponseStructured> 
    ResponseOrError<JsonResponseStructured> parse_response(std::string &response);

    template <typename JsonResponseStructured>
    ArrayErrorsResponse<JsonResponseStructured> parse_response(std::string &response, ArrayErrors const);

    ServerMessageResponse parse_response(std::string &response, ResponseIsServerMessage const);

    static std::optional<ServerMessageResponse> read_server_message(simdjson::ondemand::object &obj);

private:
    simdjson::ondemand::parser &parser() { return this->_parser; }

private: // Private methods

    std::string sign_message(std::string_view message) const;
    template<RequestType req_type> std::string dispach_request(std::string_view const endpoint, std::string const &payload) const;
    
public: // Setters Getters

    std::string const &api_key() const { return this->_key; }

private: // Private variables

    std::string _key;
    std::string _secret;
    std::string _base_url;
    int32_t _timeout;
    std::string _proxy;
    bool _show_limit_usage;
    bool _show_header;
    std::string _private_key;
    std::string _private_key_passphrase;

private: // HTTP Client and WebSocket Client

    HTTPClient _rest_api;

    std::shared_ptr<WebSocketAPIClient> _websocket_api;
    std::shared_ptr<WebSocketMarketStreamsClient> _websocket_market_streams;
    std::shared_ptr<WebSocketUserDataStreamsClient> _websocket_user_data_streams;

private: // Parsing variables

    simdjson::ondemand::parser _parser;
};

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
ResponseOrError<JsonResponseStructured> API::parse_response(std::string &response) {
    
    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

    auto obj = doc.get_object();
    if (!obj.error()) {
        std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());

        if(res.has_value()) return res.value();
    }

    doc.rewind();
    
    JsonResponseStructured response_struct;
    auto error = doc.get(response_struct);
    std::cout << "Error: " << simdjson::error_message(error) << std::endl;
    DEBUG_ASSERT(!error);

    return response_struct;
}

//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
ArrayErrorsResponse<JsonResponseStructured> API::parse_response(std::string &response, ArrayErrors const) {

    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

#ifndef NDEBUG
    simdjson_print_json_tree(doc);
    doc.rewind();
#endif

    auto obj = doc.get_object();
    if(!obj.error()) {
        std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());
        DEBUG_ASSERT(res.has_value());

        return res.value();
    }
    doc.rewind();

    simdjson::ondemand::array arr;
    auto error = doc.get_array().get(arr);
    DEBUG_ASSERT(!error);

    std::vector<ResponseOrError<JsonResponseStructured>> response_structs;
    for(simdjson::ondemand::value item : arr) {
        response_structs.emplace_back();
        auto error = item.get(response_structs.back());
        DEBUG_ASSERT(!error);
    }
    
    return response_structs;
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::sign_request(std::string_view endpoint, Parameters &payload)
{
    payload.emplace_back(std::make_pair("timestamp", std::to_string(get_timestamp())));
    payload.emplace_back(std::make_pair("signature", this->sign_message(prepare_query_string(payload))));
    return this->send_request<req_type>(endpoint, payload);
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::send_request(std::string_view endpoint, Parameters const &payload)
{
    return this->dispach_request<req_type>(endpoint, prepare_query_string(payload));
}

//------------------------------------------------------------------------------------

template<API::RequestType req_type>
std::string API::dispach_request(std::string_view endpoint, std::string const &payload) const
{
    std::string_view request = payload.empty() ? endpoint : std::string(endpoint) + "?" + payload;

    switch(req_type) {
        case API::RequestType::GET:
            return this->_rest_api.get(request, this->_timeout, this->_proxy);
        case API::RequestType::POST:
            return this->_rest_api.post(request, this->_timeout, this->_proxy);
        case API::RequestType::PUT:
            return this->_rest_api.put(request, this->_timeout, this->_proxy);
        case API::RequestType::DELETE:
            return this->_rest_api.del(request, this->_timeout, this->_proxy);
        default:
            throw std::runtime_error("Unsupported HTTP method!");
    }
}

//------------------------------------------------------------------------------------

#endif // API_HPP

//------------------------------------------------------------------------------------
