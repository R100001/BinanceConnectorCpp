
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

#include "websocket_api.hpp"
#include "websocket_market_streams.hpp"
#include "websocket_user_data_streams.hpp"

#include "websocket_client.hpp"
#include "http_client.hpp"
#include "utils.hpp"
#include "authentication.hpp"

//------------------------------------------------------------------------------------
//----------------------------------------API-----------------------------------------
//------------------------------------------------------------------------------------

class API {

public: // Typedefs

    using MsgCallbackT = std::function<void(std::string_view)>;
    using ErrCallbackT = std::function<void(std::string_view)>;

    enum class RequestType : uint8_t {
        GET,
        POST,
        PUT,
        DELETE
    };

    enum class RequestFormat : uint8_t {
        QueryString,
        JSON
    };

    enum class WebsocketAPIResponseTypes : uint8_t {
        SERVER_MESSAGE,
        FUTURES_ACCOUNT_BALANCE_V2 = '1',
        FUTURES_ACCOUNT_BALANCE = '2',
        ACCOUNT_INFORMATION_V2 = '3',
        ACCOUNT_INFORMATION = '4',
        ORDER_BOOK = '5',
        SYMBOL_PRICE_TICKER = '6',
        SYMBOL_ORDER_BOOK_TICKER = '7',
        NEW_ORDER = '8',
        MODIFY_ORDER = '9',
        CANCEL_ORDER = 'a',
        QUERY_ORDER = 'b',
        POSITION_INFORMATION_V2 = 'c',
        POSITION_INFORMATION = 'd',
        SESSION_LOGON = 'i',
        SESSION_STATUS = 's',
        SESSION_LOGOUT = 'o'
    };
    using WebsocketAPIResponse = std::variant<
        ServerMessageResponse,
        Account::FuturesAccountBalanceV2StreamObject,
        Account::FuturesAccountBalanceStreamObject,
        Account::AccountInformationV2StreamObject,
        Account::AccountInformationStreamObject,
        MarketData::OrderBookStreamObject,
        MarketData::SymbolPriceTickerStreamObject,
        MarketData::SymbolOrderBookTickerStreamObject,
        Trade::NewOrderStreamObject,
        Trade::ModifyOrderStreamObject,
        Trade::CancelOrderStreamObject,
        Trade::QueryOrderStreamObject,
        Trade::PositionInformationV2StreamObject,
        Trade::PositionInformationStreamObject,
        SessionStreamObject
    >;

    enum class MarketDataStreamEventTypes : uint8_t {
        SERVER_MESSAGE,
        AGG_TRADE,
        MARK_PRICE_UPDATE,
        MARK_PRICE_UPDATE_ALL,
        KLINE,
        CONTINUOUS_KLINE,
        MINI_TICKER_24H,
        MINI_TICKER_24H_ALL,
        TICKER_24H,
        TICKER_24H_ALL,
        BOOK_TICKER,
        BOOK_TICKER_ALL, // Is this needed?
        FORCE_ORDER,
        FORCE_ORDER_ALL, // Is this needed?
        DEPTH_UPDATE_PARTIAL,
        DEPTH_UPDATE_DIFF, // Is this needed?
        COMPOSITE_INDEX,
        CONTRACT_INFO,
        ASSET_INDEX_UPDATE
    };
    using MarketDataStreamResponse = std::variant<
        ServerMessageResponse,
        WebsocketMarketStreams::AggregateTradeStreamObject,
        WebsocketMarketStreams::MarkPriceStreamObject,
        WebsocketMarketStreams::MarkPriceStreamForAllMarketStreamObject,
        WebsocketMarketStreams::KLineStreamObject,
        WebsocketMarketStreams::ContinuousKLineStreamObject,
        WebsocketMarketStreams::MiniTicker24hrStreamObject,
        WebsocketMarketStreams::MiniTickerAll24hrStreamObject,
        WebsocketMarketStreams::Ticker24hrStreamObject,
        WebsocketMarketStreams::TickerAll24hrStreamObject,
        WebsocketMarketStreams::BookTickerStreamObject,
        WebsocketMarketStreams::BookTickerAllStreamObject,
        WebsocketMarketStreams::ForceOrderStreamObject,
        WebsocketMarketStreams::ForceOrderAllStreamObject, // Is this needed?
        WebsocketMarketStreams::DepthUpdatePartialStreamObject,
        WebsocketMarketStreams::DepthUpdateDiffStreamObject,
        WebsocketMarketStreams::CompositeIndexStreamObject,
        WebsocketMarketStreams::ContractInfoStreamObject,
        WebsocketMarketStreams::AssetIndexUpdateStreamObject
    >;

    enum class UserDataStreamEventTypes : uint8_t {
        LISTEN_KEY_EXPIRED,
        ACCOUNT_UPDATE,
        MARGIN_CALL,
        ORDER_TRADE_UPDATE,
        TRADE_LITE,
        ACCOUNT_CONFIG_UPDATE,
        STRATEGY_UPDATE,
        GRID_UPDATE,
        CONDITIONAL_ORDER_TRIGGER_REJECT
    };
    using UserDataStreamResponse = std::variant<
        WebsocketUserDataStreams::ListenKeyExpiredStreamObject,
        WebsocketUserDataStreams::AccountUpdateStreamObject,
        WebsocketUserDataStreams::MarginCallStreamObject,
        WebsocketUserDataStreams::OrderTradeUpdateStreamObject,
        WebsocketUserDataStreams::TradeLiteStreamObject,
        WebsocketUserDataStreams::AccountConfigUpdateStreamObject,
        WebsocketUserDataStreams::StrategyUpdateStreamObject,
        WebsocketUserDataStreams::GridUpdateStreamObject,
        WebsocketUserDataStreams::ConditionalOrderTriggerRejectStreamObject
    >;

public: // Constructors

    API(
        std::string_view hmac_api_key,
        std::string_view hmac_api_secret = "",
        std::string_view ed25519_api_key = "",
        std::string_view ed25519_private_key = "",
        std::string_view ed25519_private_key_passphrase = "",
        int32_t const timeout = -1,
        std::string_view proxy = "",
        bool const show_limit_usage = false,
        bool const show_header = false
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


public: // Websocket API Streams

    void ws_api_connect();
    void ws_api_disconnect();

    void ws_api_session_logon();
    void ws_api_session_status();
    void ws_api_session_logout();
    
    void ws_api_message_callback(MsgCallbackT callback);
    void ws_api_error_callback(ErrCallbackT callback);

    // Account Streams
    void futures_account_balance_v2_stream(int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void futures_account_balance_stream(int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void account_information_v2_stream(int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void account_information_stream(int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");

    // Convert Streams

    // Market Data Streams
    void order_book_stream(std::string const &symbol, int16_t const &limit = -1);
    void symbol_price_ticker_stream(std::string const &symbol = "");
    void symbol_order_book_ticker_stream(std::string const &symbol = "");

    // Portfolio Margin Streams
    
    // Trade Streams
    void new_order_stream(Trade::NewOrder const &order, bool const close_position = false, int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void modify_order_stream(Trade::ModifyOrder const &order, int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void cancel_order_stream(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void query_order_stream(std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void position_information_v2_stream(std::string const &symbol = "", int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");
    void position_information_stream(std::string const &symbol = "", int32_t const recv_window = -1, std::string const &hmac_api_key = "", std::string const &hmac_api_secret = "");

public: // Websocket Market Streams

    void ws_market_streams_connect();
    void ws_market_streams_disconnect();
    void ws_market_streams_message_callback(MsgCallbackT callback);
    void ws_market_streams_error_callback(ErrCallbackT callback);

    void aggregate_trade_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol);
    void mark_price_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, uint8_t const update_speed = 3);
    void mark_price_stream_for_all_market(WebsocketMarketStreamsMethod const wsms_method, uint8_t const update_speed = 3);
    void kline_candlestick_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, std::string const &interval);
    void continuous_contract_kline_candlestick_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &pair, std::string const &contract_type, std::string const &interval);
    void individual_symbol_mini_ticker_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol);
    void all_market_mini_ticker_streams(WebsocketMarketStreamsMethod const wsms_method);
    void individual_symbol_ticker_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol);
    void all_market_ticker_streams(WebsocketMarketStreamsMethod const wsms_method);
    void individual_symbol_book_ticker_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol);
    void all_book_tickers_stream(WebsocketMarketStreamsMethod const wsms_method);
    void liquidation_order_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol);
    void all_market_liquidation_order_streams(WebsocketMarketStreamsMethod const wsms_method);
    void partial_book_depth_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, int16_t const levels, uint16_t const update_speed = 250);
    void diff_book_depth_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol, uint16_t const update_speed = 250);
    void composite_index_symbol_information_stream(WebsocketMarketStreamsMethod const wsms_method, std::string const &symbol);
    void contract_info_stream(WebsocketMarketStreamsMethod const wsms_method);
    void multi_assets_mode_asset_index(WebsocketMarketStreamsMethod const wsms_method, std::string const &asset_symbol = "");
    void ws_market_streams_multiple_streams(WebsocketMarketStreamsMethod const wsms_method, std::string const &streams);
    void ws_market_streams_list_subscriptions() const;

public: // Websocket User Data Streams

    void ws_user_data_streams_connect();
    void ws_user_data_streams_disconnect();

    void ws_user_data_streams_message_callback(MsgCallbackT callback);
    void ws_user_data_streams_error_callback(ErrCallbackT callback);

private: // REST API request methods

    template<RequestType req_type> std::string sign_request(std::string_view endpoint, Parameters &payload);
    template<RequestType req_type> std::string send_request(std::string_view endpoint, Parameters const &payload = {}); 
    template<RequestType req_type> std::string dispatch_request(std::string_view const endpoint, std::string const &payload) const;

private: // RestAPI Message Parsing

    /*----- Parsing Tags -----*/
    struct ArrayErrors {};
    struct ResponseIsServerMessage {};

    /*----- Parsing Functions -----*/
    template <typename JsonResponseStructured> 
    ResponseOrError<JsonResponseStructured> parse_response(std::string &response);

    template <typename JsonResponseStructured>
    ArrayErrorsResponse<JsonResponseStructured> parse_response(std::string &response, ArrayErrors const);

    ServerMessageResponse parse_response(std::string &response, ResponseIsServerMessage const);

public: // Server Message Parsing

    static std::optional<ServerMessageResponse> read_server_message(simdjson::ondemand::object &obj);

private: // Websockets Message Parsing

    WebsocketAPIResponse ws_api_parse_response(std::string &response);
    MarketDataStreamResponse ws_market_streams_parse_response(std::string &response);
    UserDataStreamResponse ws_user_data_streams_parse_response(std::string &response);

private:
    simdjson::ondemand::parser &parser() { return this->_parser; }

public: // Setters Getters

    std::string const &hmac_api_key() const { return this->_hmac_api_key; }
    std::string const &hmac_api_secret() const { return this->_hmac_api_secret; }
    std::string const &ed25519_api_key() const { return this->_ed25519_api_key; }
    std::string const &ed25519_private_key() const { return this->_ed25519_private_key; }
    std::string const &ed25519_private_key_passphrase() const { return this->_ed25519_private_key_passphrase; }

private: // Private variables

    std::string _hmac_api_key;
    std::string _hmac_api_secret;
    std::string _ed25519_api_key;
    std::string _ed25519_private_key;
    std::string _ed25519_private_key_passphrase;
    std::string _base_url;
    int32_t _timeout;
    std::string _proxy;
    bool _show_limit_usage;
    bool _show_header;

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

namespace simdjson {

//------------------------------------------------------------------------------------

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ServerMessageResponse &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "code", response.code)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "msg", response.msg)) return error;

    return SUCCESS;
}

//------------------------------------------------------------------------------------

} // namespace simdjson

//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
ResponseOrError<JsonResponseStructured> API::parse_response(std::string &response) {
    
    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

    std::optional<ServerMessageResponse> server_message;
    auto error = doc.get<std::optional<ServerMessageResponse>>().get(server_message);
    if(!error) {
        DEBUG_ASSERT(server_message.has_value());
        return server_message.value();
    }
    DEBUG_ASSERT(error == simdjson::error_code::NO_SUCH_FIELD);

    doc.rewind();
    
    JsonResponseStructured response_struct;
    error = doc.get(response_struct);
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

    std::optional<ServerMessageResponse> server_message;
    auto error = doc.get<std::optional<ServerMessageResponse>>().get(server_message);
    if(!error) {
        DEBUG_ASSERT(server_message.has_value());
        return server_message.value();
    }
    DEBUG_ASSERT(error == simdjson::error_code::NO_SUCH_FIELD);

    doc.rewind();

    simdjson::ondemand::array arr;
    error = doc.get_array().get(arr);
    DEBUG_ASSERT(!error);

    std::vector<ResponseOrError<JsonResponseStructured>> response_structs;
    for(simdjson::ondemand::value item : arr) {
        response_structs.emplace_back();
        error = item.get(response_structs.back());
        DEBUG_ASSERT(!error);
    }
    
    return response_structs;
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::sign_request(std::string_view endpoint, Parameters &payload)
{
    payload.emplace_back(std::make_pair("timestamp", std::to_string(get_timestamp())));
    payload.emplace_back(std::make_pair("signature", hmac_signature(hmac_api_secret(), prepare_query_string(payload))));
    return this->send_request<req_type>(endpoint, payload);
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::send_request(std::string_view endpoint, Parameters const &payload)
{
    return this->dispatch_request<req_type>(endpoint, prepare_query_string(payload));
}

//------------------------------------------------------------------------------------

template<API::RequestType req_type>
std::string API::dispatch_request(std::string_view endpoint, std::string const &payload) const
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
