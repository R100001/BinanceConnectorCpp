
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

//------------------------------------------------------------------------------------

#include <unordered_map>
#include <vector>
#include <string>
#include <cstdint>

#include <api_declarations.hpp>

//------------------------------------------------------------------------------------

namespace Account {

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
    int32_t bracket;
    int32_t notional_cap;
    int32_t notional_floor;
    int32_t cum;
    int16_t initial_leverage;
};

struct SymbolNotionalAndLeverageBrackets {
    std::string symbol;
    double notional_coef;
    std::vector<Bracket> brackets;
};

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

using Indicators = std::unordered_map<std::string, std::vector<Indicator>>;

struct DownloadLinkById {
    std::string download_id;
    std::string status;
    std::string url;
    int64_t expiration_timestamp;
    bool notified;
    bool is_expired;
};

struct GetDownloadId {
    std::string download_id;
    int64_t avg_cost_timestamp_of_last_30d;
};

//------------------------------------------------------------------------------------

// Response Structs

struct NewFutureAccountTransferObject {
    std::string tran_id; 
};
using NewFutureAccountTransferResponse = ResponseOrError<NewFutureAccountTransferObject>;

struct FuturesAccountBalanceV3Object {
    std::vector<FuturesAccountBalance> balances;
};
using FuturesAccountBalanceV3Response = ResponseOrError<FuturesAccountBalanceV3Object>;

struct FuturesAccountBalanceObject {
    std::vector<FuturesAccountBalance> balances;
};
using FuturesAccountBalanceResponse = ResponseOrError<FuturesAccountBalanceObject>;

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
using AccountInformationV3Response = ResponseOrError<AccountInformationV3Object>;

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
using AccountInformationResponse = ResponseOrError<AccountInformationObject>;

struct GetFutureAccountTransactionHistoryListObject {
    int32_t total;
    std::vector<Transfer> rows;
};
using GetFutureAccountTransactionHistoryListResponse = ResponseOrError<GetFutureAccountTransactionHistoryListObject>;

struct UserCommissionRateObject {
    std::string symbol;
    std::string maker_commission_rate;
    std::string taker_commission_rate;
};
using UserCommissionRateResponse = ResponseOrError<UserCommissionRateObject>;

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
using QueryAccountConfigurationResponse = ResponseOrError<QueryAccountConfigurationObject>;

struct QuerySymbolConfigurationObject {
    std::vector<SymbolConfiguration> symbols;
};
using QuerySymbolConfigurationResponse = ResponseOrError<QuerySymbolConfigurationObject>;

struct QueryOrderRateLimitObject {
    std::vector<RateLimit> rate_limits;
};
using QueryOrderRateLimitResponse = ResponseOrError<QueryOrderRateLimitObject>;

using NotionalAndLeverageBracketsObject = std::variant<SymbolNotionalAndLeverageBrackets, std::vector<SymbolNotionalAndLeverageBrackets>>;
using NotionalAndLeverageBracketsResponse = ResponseOrError<NotionalAndLeverageBracketsObject>;

struct GetCurrentMultiAssetsModeObject {
    bool multi_assets_margin;
};
using GetCurrentMultiAssetsModeResponse = ResponseOrError<GetCurrentMultiAssetsModeObject>;

struct GetCurrentPositionModeObject {
    bool dual_side_position;
};
using GetCurrentPositionModeResponse = ResponseOrError<GetCurrentPositionModeObject>;

struct GetIncomeHistoryObject {
    std::vector<IncomeHistory> history;
};
using GetIncomeHistoryResponse = ResponseOrError<GetIncomeHistoryObject>;

struct FuturesTradingQuantitativeRulesIndicatorsObject {
    uint64_t update_time;
    Indicators indicators;
};
using FuturesTradingQuantitativeRulesIndicatorsResponse = ResponseOrError<FuturesTradingQuantitativeRulesIndicatorsObject>;

using GetDownloadIdForFuturesTransactionHistoryObject = GetDownloadId;
using GetDownloadIdForFuturesTransactionHistoryResponse = ResponseOrError<GetDownloadIdForFuturesTransactionHistoryObject>;

using GetFuturesTransactionHistoryDownloadLinkByIdObject = DownloadLinkById;
using GetFuturesTransactionHistoryDownloadLinkByIdResponse = ResponseOrError<GetFuturesTransactionHistoryDownloadLinkByIdObject>;

using GetDownloadIdForFuturesOrderHistoryObject = GetDownloadId;
using GetDownloadIdForFuturesOrderHistoryResponse = ResponseOrError<GetDownloadIdForFuturesOrderHistoryObject>;

using GetFuturesOrderHistoryDownloadLinkByIdObject = DownloadLinkById;
using GetFuturesOrderHistoryDownloadLinkByIdResponse = ResponseOrError<GetFuturesOrderHistoryDownloadLinkByIdObject>;

using GetDownloadIdForFuturesTradeHistoryObject = GetDownloadId;
using GetDownloadIdForFuturesTradeHistoryResponse = ResponseOrError<GetDownloadIdForFuturesTradeHistoryObject>;

using GetFuturesTradeDownloadLinkByIdObject = DownloadLinkById;
using GetFuturesTradeDownloadLinkByIdResponse = ResponseOrError<GetFuturesTradeDownloadLinkByIdObject>;

using ToggleBnbBurnOnFuturesTradeObject = ServerMessageResponse;
using ToggleBnbBurnOnFuturesTradeResponse = ToggleBnbBurnOnFuturesTradeObject;

struct GetBnbBurnStatusObject {
    bool fee_burn;
};
using GetBnbBurnStatusResponse = ResponseOrError<GetBnbBurnStatusObject>;

//------------------------------------------------------------------------------------

} // namespace Account

//------------------------------------------------------------------------------------

#endif // ACCOUNT_HPP

//------------------------------------------------------------------------------------
