
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

//------------------------------------------------------------------------------------

#include "derivatives_trading.hpp"
#include "error.hpp"

//------------------------------------------------------------------------------------

// Response Objects

struct FuturesAccountBalance {
    std::string account_alias;
    std::string asset;
    std::string balance;
    std::string cross_wallet_balance;
    std::string cross_un_pnl;
    std::string available_balance;
    std::string max_withdraw_amount;
    int64_t update_time;
    bool margin_available;
};

struct SingleAssetMode {
    std::string asset;
    std::string wallet_balance;
    std::string unrealized_profit;
    std::string margin_balance;
    std::string maint_margin;
    std::string initial_margin;
    std::string position_initial_margin;
    std::string open_order_initial_margin;
    std::string cross_wallet_balance;
    std::string cross_un_pnl;
    std::string available_balance;
    std::string max_withdraw_amount;
    int64_t update_time;
};

struct MultiAssetsMode {
    std::string asset;
    std::string wallet_balance;
    std::string unrealized_profit;
    std::string margin_balance;
    std::string maint_margin;
    std::string initial_margin;
    std::string position_initial_margin;
    std::string open_order_initial_margin;
    std::string cross_wallet_balance;
    std::string cross_un_pnl;
    std::string available_balance;
    std::string max_withdraw_amount;
    int64_t update_time;
    bool margin_available;
};

using Asset = std::variant<SingleAssetMode, MultiAssetsMode>;

struct Position {
    std::string symbol;
    std::string position_side;
    std::string position_amt;
    std::string unrealized_profit;
    std::string isolated_margin;
    std::string notional;
    std::string isolated_wallet;
    std::string initial_margin;
    std::string maint_margin;
    int64_t update_time;
};

struct PositionOld {
    std::string symbol;
    std::string initial_margin;
    std::string maint_margin;
    std::string unrealized_profit;
    std::string position_initial_margin;
    std::string open_order_initial_margin;
    std::string leverage;
    std::string entry_price;
    std::string max_notional;
    std::string bid_notional;
    std::string ask_notional;
    std::string position_side;
    std::string position_amt;
    int64_t update_time;
    bool isolated;
};

struct Transfer {
    std::string asset;
    std::string amount;
    std::string type;
    std::string status;
    int64_t tran_id;
    int64_t timestamp;
};

struct SymbolConfiguration {
    std::string symbol;
    std::string margin_type;
    std::string is_auto_add_margin;
    std::string max_notional_value;
    int16_t leverage;
};

struct RateLimit {
    std::string rate_limit_type;
    std::string interval;
    int32_t interval_num;
    int32_t limit;
};

struct Bracket {
    double maint_margin_ratio;
    int32_t notional_bracket;
    int32_t notional_cap;
    int32_t notional_floor;
    int32_t cum;
    int16_t initial_lev;
};

struct SymbolNotionalAndLeverageBrackets {
    std::string symbol;
    double notional_coef;
    std::vector<Bracket> brackets;
};

using NotionalAndLeverageBrackets = std::variant<SymbolNotionalAndLeverageBrackets, std::vector<SymbolNotionalAndLeverageBrackets>>;

struct IncomeHistory {
    std::string symbol;
    std::string income_type;
    std::string income;
    std::string asset;
    std::string info;
    std::string trade_id;
    int64_t time;
    int64_t tran_id;
};

struct Indicator {
    std::string indicator;
    uint64_t planned_recover_time;
    double value;
    double trigger_value;
    bool is_locked;
};

//------------------------------------------------------------------------------------

// Response Structs

struct NewFutureAccountTransferObject {
    std::string tran_id; 
};
using NewFutureAccountTransferResponse = std::variant<NewFutureAccountTransferObject, ServerError>;

struct FuturesAccountBalanceV3Object {
    std::vector<FuturesAccountBalance> balances;
};
using FuturesAccountBalanceV3Response = std::variant<FuturesAccountBalanceV3Object, ServerError>;

struct FuturesAccountBalanceObject {
    std::vector<FuturesAccountBalance> balances;
};
using FuturesAccountBalanceResponse = std::variant<FuturesAccountBalanceObject, ServerError>;

struct AccountInformationV3Object {
    std::string total_initial_margin;
    std::string total_maint_margin;
    std::string total_wallet_balance;
    std::string total_unrealized_profit;
    std::string total_margin_balance;
    std::string total_position_initial_margin;
    std::string total_open_order_initial_margin;
    std::string total_cross_wallet_balance;
    std::string total_cross_un_pnl;
    std::string available_balance;
    std::string max_withdraw_amount;
    std::vector<Asset> assets;
    std::vector<Position> positions;
};
using AccountInformationV3Response = std::variant<AccountInformationV3Object, ServerError>;

struct AccountInformationObject {
    int64_t trade_group_id;
    std::string total_initial_margin;
    std::string total_maint_margin;
    std::string total_wallet_balance;
    std::string total_unrealized_profit;
    std::string total_margin_balance;
    std::string total_position_initial_margin;
    std::string total_open_order_initial_margin;
    std::string total_cross_wallet_balance;
    std::string total_cross_un_pnl;
    std::string available_balance;
    std::string max_withdraw_amount;
    std::vector<MultiAssetsMode> assets;
    std::vector<PositionOld> positions;
    int8_t fee_tier;
    int8_t update_time;
    bool fee_burn;
    bool can_deposit;
    bool can_withdraw;
    bool multi_assets_margin;
};
using AccountInformationResponse = std::variant<AccountInformationObject, ServerError>;

struct GetFutureAccountTransactionHistoryListObject {
    int32_t total;
    std::vector<Transfer> rows;
};
using GetFutureAccountTransactionHistoryListResponse = std::variant<GetFutureAccountTransactionHistoryListObject, ServerError>;

struct UserCommissionRateObject {
    std::string symbol;
    std::string maker_commission_rate;
    std::string taker_commission_rate;
};
using UserCommissionRateResponse = std::variant<UserCommissionRateObject, ServerError>;

struct QueryAccountConfigurationObject {
    int64_t trade_group_id;
    int8_t fee_tier;
    int8_t update_time;
    bool can_trade;
    bool can_deposit;
    bool can_withdraw;
    bool dual_side_position;
    bool multi_assets_margin;
};
using QueryAccountConfigurationResponse = std::variant<QueryAccountConfigurationObject, ServerError>;

struct QuerySymbolConfigurationObject {
    std::vector<SymbolConfiguration> symbols;
};
using QuerySymbolConfigurationResponse = std::variant<QuerySymbolConfigurationObject, ServerError>;

struct QueryOrderRateLimitObject {
    std::vector<RateLimit> rate_limits;
};
using QueryOrderRateLimitResponse = std::variant<QueryOrderRateLimitObject, ServerError>;

struct NotionalAndLeverageBracketsObject {
    NotionalAndLeverageBrackets brackets;
};
using NotionalAndLeverageBracketsResponse = std::variant<NotionalAndLeverageBracketsObject, ServerError>;

struct GetCurrentMultiAssetsModeObject {
    bool multi_assets_margin;
};
using GetCurrentMultiAssetsModeResponse = std::variant<GetCurrentMultiAssetsModeObject, ServerError>;

struct GetCurrentPositionModeObject {
    bool dual_side_position;
};
using GetCurrentPositionModeResponse = std::variant<GetCurrentPositionModeObject, ServerError>;

struct GetIncomeHistoryObject {
    std::vector<IncomeHistory> history;
};
using GetIncomeHistoryResponse = std::variant<GetIncomeHistoryObject, ServerError>;

struct FuturesTradingQuantitativeRulesIndicatorsObject {
    uint64_t update_time;
    std::unordered_map<std::string, Indicator> indicators;
};
using FuturesTradingQuantitativeRulesIndicatorsResponse = std::variant<FuturesTradingQuantitativeRulesIndicatorsObject, ServerError>;

struct GetDownloadIdForFuturesTransactionHistoryObject {
    std::string download_id;
    int64_t avg_cost_timestamp_of_last_30d;
};
using GetDownloadIdForFuturesTransactionHistoryResponse = std::variant<GetDownloadIdForFuturesTransactionHistoryObject, ServerError>;

struct GetFuturesTransactionHistoryDownloadLinkByIdObject {
    std::string download_id;
    std::string status;
    std::string url;
    int64_t expiration_timestamp;
    bool notified;
    bool is_expired;
};
using GetFuturesTransactionHistoryDownloadLinkByIdResponse = std::variant<GetFuturesTransactionHistoryDownloadLinkByIdObject, ServerError>;

struct GetDownloadIdForFuturesOrderHistoryObject {
    std::string download_id;
    int64_t avg_cost_timestamp_of_last_30d;
};
using GetDownloadIdForFuturesOrderHistoryResponse = std::variant<GetDownloadIdForFuturesOrderHistoryObject, ServerError>;

struct GetFuturesOrderHistoryDownloadLinkByIdObject {
    std::string download_id;
    std::string status;
    std::string url;
    int64_t expiration_timestamp;
    bool notified;
    bool is_expired;
};
using GetFuturesOrderHistoryDownloadLinkByIdResponse = std::variant<GetFuturesOrderHistoryDownloadLinkByIdObject, ServerError>;

struct GetDownloadIdForFuturesTradeHistoryObject {
    std::string download_id;
    int64_t avg_cost_timestamp_of_last_30d;
};
using GetDownloadIdForFuturesTradeHistoryResponse = std::variant<GetDownloadIdForFuturesTradeHistoryObject, ServerError>;

struct GetFuturesTradeDownloadLinkByIdObject {
    std::string download_id;
    std::string status;
    std::string url;
    int64_t expiration_timestamp;
    bool notified;
    bool is_expired;
};
using GetFuturesTradeDownloadLinkByIdResponse = std::variant<GetFuturesTradeDownloadLinkByIdObject, ServerError>;

struct ToggleBnbBurnOnFuturesTradeObject {
    std::string msg;
    int32_t code;
};
using ToggleBnbBurnOnFuturesTradeResponse = std::variant<ToggleBnbBurnOnFuturesTradeObject, ServerError>;

struct BnbBurnStatusObject {
    bool fee_burn;
};
using BnbBurnStatusResponse = std::variant<BnbBurnStatusObject, ServerError>;

//------------------------------------------------------------------------------------

// REST API Endpoints

namespace RestAPI {

NewFutureAccountTransferResponse                        new_future_account_transfer(DerivativesTrading const &api, std::string const &type, std::string const &asset, double const amount, std::string const &from_symbol, std::string const &to_symbol, int32_t const recv_window = -1);
FuturesAccountBalanceV3Response                         futures_account_balance_v3(DerivativesTrading const &api, int32_t const recv_window = -1);
FuturesAccountBalanceResponse                           futures_account_balance(DerivativesTrading const &api, int32_t const recv_window = -1);
AccountInformationV3Response                            account_information_v3(DerivativesTrading const &api, int32_t const recv_window = -1);
AccountInformationResponse                              account_information(DerivativesTrading const &api, int32_t const recv_window = -1);
GetFutureAccountTransactionHistoryListResponse          get_future_account_transaction_history_list(DerivativesTrading const &api, std::string const &type, int64_t const start_time = -1, int64_t const end_time = -1, int32_t const current = -1, int8_t const size = -1, std::string const &from_symbol = "", std::string const &to_symbol = "", int32_t const recv_window = -1);
UserCommissionRateResponse                              user_commission_rate(DerivativesTrading const &api, std::string const &symbol, int32_t const recv_window = -1);
QueryAccountConfigurationResponse                       query_account_configuration(DerivativesTrading const &api, int32_t const recv_window = -1);
QuerySymbolConfigurationResponse                        query_symbol_configuration(DerivativesTrading const &api, std::string const &symbol = "", int32_t const recv_window = -1);
QueryOrderRateLimitResponse                             query_order_rate_limit(DerivativesTrading const &api, int32_t const recv_window = -1);
NotionalAndLeverageBracketsResponse                     notional_and_leverage_brackets(DerivativesTrading const &api, std::string const &symbol = "", int32_t const recv_window = -1);
GetCurrentMultiAssetsModeResponse                       get_current_multi_assets_mode(DerivativesTrading const &api, int32_t const recv_window = -1);
GetCurrentPositionModeResponse                          get_current_position_mode(DerivativesTrading const &api, int32_t const recv_window = -1);
GetIncomeHistoryResponse                                get_income_history(DerivativesTrading const &api, std::string const &symbol = "", std::string const &income_type = "", int64_t const start_time = -1, int64_t const end_time = -1, int32_t const page = -1, int16_t const limit = -1, int32_t const recv_window = -1);
FuturesTradingQuantitativeRulesIndicatorsResponse       futures_trading_quantitative_rules_indicators(DerivativesTrading const &api, std::string const &symbol = "", int32_t const recv_window = -1);
GetDownloadIdForFuturesTransactionHistoryResponse       get_download_id_for_futures_transaction_history(DerivativesTrading const &api, int64_t const start_time, int64_t const end_time, int32_t const recv_window = -1);
GetFuturesTransactionHistoryDownloadLinkByIdResponse    get_futures_transaction_history_download_link_by_id(DerivativesTrading const &api, std::string const &download_id, int32_t const recv_window = -1);
GetDownloadIdForFuturesOrderHistoryResponse             get_download_id_for_futures_order_history(DerivativesTrading const &api, int64_t const start_time, int64_t const end_time, int32_t const recv_window = -1);
GetFuturesOrderHistoryDownloadLinkByIdResponse          get_futures_order_history_download_link_by_id(DerivativesTrading const &api, std::string const &download_id, int32_t const recv_window = -1);
GetDownloadIdForFuturesTradeHistoryResponse             get_download_if_for_futures_trade_history(DerivativesTrading const &api, int64_t const start_time, int64_t const end_time, int32_t const recv_window = -1);
GetFuturesTradeDownloadLinkByIdResponse                 get_futures_trade_download_link_by_id(DerivativesTrading const &api, std::string const &download_id, int32_t const recv_window = -1);
ToggleBnbBurnOnFuturesTradeResponse                     toggle_bnb_burn_on_futures_trade(DerivativesTrading const &api, bool const burn, int32_t const recv_window = -1);
BnbBurnStatusResponse                                   get_bnb_burn_status(DerivativesTrading const &api, int32_t const recv_window = -1);

} // namespace RestAPI

//------------------------------------------------------------------------------------

// Websocket API Endpoints

namespace WebsocketAPI {

void futures_account_balance_v2(DerivativesTrading const &api, int32_t const recv_window = -1);
void futures_account_balance(DerivativesTrading const &api, int32_t const recv_window = -1);
void account_information_v2(DerivativesTrading const &api, int32_t const recv_window = -1);
void account_information(DerivativesTrading const &api, int32_t const recv_window = -1);

} // namespace WebsocketAPI

//------------------------------------------------------------------------------------

#endif // ACCOUNT_HPP

//------------------------------------------------------------------------------------
