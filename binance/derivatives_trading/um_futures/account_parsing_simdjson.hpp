
//-----------------------------------------------------------------------------

#ifndef ACCOUNT_PARSING_SIMDJSON_HPP
#define ACCOUNT_PARSING_SIMDJSON_HPP

//------------------------------------------------------------------------------------

#include "account.hpp"

#include "utils.hpp"

//------------------------------------------------------------------------------------

namespace simdjson {

using namespace Account;

// ---------- New Future Account Transfer ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, NewFutureAccountTransferObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "tranId", response.tran_id)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Futures Account Balance V3 ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, FuturesAccountBalance &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "accountAlias", response.account_alias)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "asset", response.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "balance", response.balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "crossWalletBalance", response.cross_wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "crossUnPnl", response.cross_un_pnl)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "availableBalance", response.available_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxWithdrawAmount", response.max_withdraw_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginAvailable", response.margin_available)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, FuturesAccountBalanceV3Object &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "balances", response.balances)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Futures Account Balance ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, FuturesAccountBalanceObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "balances", response.balances)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Account Information V3 ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SingleAssetMode &asset) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "asset", asset.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "walletBalance", asset.wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "unrealizedProfit", asset.unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginBalance", asset.margin_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maintMargin", asset.maint_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "initialMargin", asset.initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionInitialMargin", asset.position_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "openOrderInitialMargin", asset.open_order_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "crossWalletBalance", asset.cross_wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "crossUnPnl", asset.cross_un_pnl)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "availableBalance", asset.available_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxWithdrawAmount", asset.max_withdraw_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", asset.update_time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MultiAssetsMode &asset) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "asset", asset.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "walletBalance", asset.wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "unrealizedProfit", asset.unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginBalance", asset.margin_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maintMargin", asset.maint_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "initialMargin", asset.initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionInitialMargin", asset.position_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "openOrderInitialMargin", asset.open_order_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "crossWalletBalance", asset.cross_wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "crossUnPnl", asset.cross_un_pnl)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "availableBalance", asset.available_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxWithdrawAmount", asset.max_withdraw_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginAvailable", asset.margin_available)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", asset.update_time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Asset &asset) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    const size_t num_fields = obj.count_fields();

    if (num_fields == 13) {
        SingleAssetMode single_asset_mode;
        val.get(single_asset_mode);
        asset = single_asset_mode;
    }
    else {
        MultiAssetsMode multi_assets_mode;
        val.get(multi_assets_mode);
        asset = multi_assets_mode;
    }

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Position &position) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", position.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", position.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionAmt", position.position_amt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "unrealizedProfit", position.unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isolatedMargin", position.isolated_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "notional", position.notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isolatedWallet", position.isolated_wallet)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "initialMargin", position.initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maintMargin", position.maint_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", position.update_time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountInformationV3Object &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "totalInitialMargin", response.total_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalMaintMargin", response.total_maint_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalWalletBalance", response.total_wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalUnrealizedProfit", response.total_unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalMarginBalance", response.total_margin_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalPositionInitialMargin", response.total_position_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalOpenOrderInitialMargin", response.total_open_order_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalCrossWalletBalance", response.total_cross_wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalCrossUnPnl", response.total_cross_un_pnl)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "availableBalance", response.available_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxWithdrawAmount", response.max_withdraw_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "assets", response.assets)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positions", response.positions)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Account Information ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, PositionOld &position) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", position.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "initialMargin", position.initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maintMargin", position.maint_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "unrealizedProfit", position.unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionInitialMargin", position.position_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "openOrderInitialMargin", position.open_order_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "leverage", position.leverage)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isolated", position.isolated)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "entryPrice", position.entry_price)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxNotional", position.max_notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bidNotional", position.bid_notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "askNotional", position.ask_notional)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionSide", position.position_side)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positionAmt", position.position_amt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", position.update_time)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountInformationObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "feeTier", response.fee_tier)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "feeBurn", response.fee_burn)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "canDeposit", response.can_deposit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "canWithdraw", response.can_withdraw)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "multiAssetsMargin", response.multi_assets_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "tradeGroupId", response.trade_group_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalInitialMargin", response.total_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalMaintMargin", response.total_maint_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalWalletBalance", response.total_wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalUnrealizedProfit", response.total_unrealized_profit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalMarginBalance", response.total_margin_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalPositionInitialMargin", response.total_position_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalOpenOrderInitialMargin", response.total_open_order_initial_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalCrossWalletBalance", response.total_cross_wallet_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "totalCrossUnPnl", response.total_cross_un_pnl)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "availableBalance", response.available_balance)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxWithdrawAmount", response.max_withdraw_amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "assets", response.assets)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "positions", response.positions)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Get Future Account Transaction History List ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Transfer &transfer) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "asset", transfer.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "amount", transfer.amount)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "type", transfer.type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", transfer.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "tranId", transfer.tran_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "timestamp", transfer.timestamp)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetFutureAccountTransactionHistoryListObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "total", response.total)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "rows", response.rows)) return error;

    return SUCCESS;
}
// -----------------------------------------------------------------

// ---------- User Commission Rate ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, UserCommissionRateObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", response.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "makerCommissionRate", response.maker_commission_rate)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "takerCommissioRate", response.taker_commission_rate)) return error;

    return SUCCESS;
}
// ------------------------------------------

// ---------- Query Account Configuration ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryAccountConfigurationObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "feeTier", response.fee_tier)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "canTrade", response.can_trade)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "canDeposit", response.can_deposit)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "canWithdraw", response.can_withdraw)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "dualSidePosition", response.dual_side_position)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "multiAssetsMargin", response.multi_assets_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "tradeGroupId", response.trade_group_id)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Query Symbol Configuration ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SymbolConfiguration &symbol) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", symbol.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "marginType", symbol.margin_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isAutoAddMargin", symbol.is_auto_add_margin)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "leverage", symbol.leverage)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxNotionalValue", symbol.max_notional_value)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, QuerySymbolConfigurationObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbols", response.symbols)) return error;

    return SUCCESS;
}
// -------------------------------------------------

// ---------- Query Order Rate Limit ----------
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
auto tag_invoke(deserialize_tag, simdjson_value &val, QueryOrderRateLimitObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "rateLimits", response.rate_limits)) return error;

    return SUCCESS;
}
// --------------------------------------------

// ---------- Notional and Leverage Brackets ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Bracket &bracket) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "bracket", bracket.bracket)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "initialLeverage", bracket.initial_leverage)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "notionalCap", bracket.notional_cap)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "notionalFloor", bracket.notional_floor)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maintMarginRatio", bracket.maint_margin_ratio)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cum", bracket.cum)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, SymbolNotionalAndLeverageBrackets &symbol) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", symbol.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "notionalCoefficient", symbol.notional_coef)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "brackets", symbol.brackets)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, NotionalAndLeverageBracketsObject &response) {
    
    ondemand::object obj;
    auto error = val.get_object().get(obj);
    
    if (error) {
        std::vector<SymbolNotionalAndLeverageBrackets> brackets;
        if (auto error = val.get(brackets)) return error;
        response = brackets;
    }
    else {
        SymbolNotionalAndLeverageBrackets brackets;
        if (auto error = val.get(brackets)) return error;
        response = brackets;
    }
    
    return SUCCESS;
}
// ----------------------------------------------------

// ---------- Get Current Multi Assets Mode ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetCurrentMultiAssetsModeObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "multiAssetsMargin", response.multi_assets_margin)) return error;

    return SUCCESS;
}
// ---------------------------------------------------

// ---------- Get Current Position Mode ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetCurrentPositionModeObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "dualSidePosition", response.dual_side_position)) return error;

    return SUCCESS;
}
// -----------------------------------------------

// ---------- Get Income History ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, IncomeHistory &income) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "symbol", income.symbol)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "incomeType", income.income_type)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "income", income.income)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "asset", income.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "info", income.info)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "time", income.time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "tranId", income.tran_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "tradeId", income.trade_id)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetIncomeHistoryObject &response) {
    
    if (auto error = val.get(response.history)) return error;
 
    return SUCCESS;
}
// -------------------------------------------------

// ---------- Futures Trading Quantitative Rules Indicators ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Indicator &indicator) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "isLocked", indicator.is_locked)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "plannedRecoverTime", indicator.planned_recover_time)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "indicator", indicator.indicator)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "value", indicator.value)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "triggerValue", indicator.trigger_value)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Indicators &indicators) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;
    
    for (auto field : obj) {
        std::vector<Indicator> indicator;
        std::string_view field_name = field.escaped_key();
        if (auto error = field.value().get<std::vector<Indicator>>().get(indicator)) return error;
        indicators.insert({std::string(field_name), indicator});
    }

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, FuturesTradingQuantitativeRulesIndicatorsObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "indicators", response.indicators)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "updateTime", response.update_time)) return error;

    return SUCCESS;
}
// -------------------------------------------------------------------

// ---------- Get Download ID ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetDownloadId &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "avgCostTimestampOfLast30d", response.avg_cost_timestamp_of_last_30d)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "downloadId", response.download_id)) return error;

    return SUCCESS;
}
// ---------------------------------------------------------------------

// ---------- Download Link by ID ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, DownloadLinkById &download_link_id) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "downloadId", download_link_id.download_id)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "status", download_link_id.status)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "url", download_link_id.url)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "notified", download_link_id.notified)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "expirationTimestamp", download_link_id.expiration_timestamp)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "isExpired", download_link_id.is_expired)) return error;

    return SUCCESS;
}

// ---------- Get Download ID For Futures Transaction History ----------
// Get Download ID
// ---------------------------------------------------------------------

// ---------- Get Futures Transaction History Download Link by ID ----------
// Get Download Link by ID
// -------------------------------------------------------------------------

// ---------- Get Download ID for Futures Order History ----------
// Get Download ID
// ---------------------------------------------------------------

// ---------- Get Futures Order History Download Link by ID ----------
// Get Download Link by ID
// -------------------------------------------------------------------

// ---------- Get Download ID for Futures Trade History ----------
// Get Download ID
// --------------------------------------------------------------

// ---------- Get Futures Trade Download Link by ID ----------
// Get Download Link by ID
// -----------------------------------------------------------

// ---------- Toggle BNB Burn On Futures Trade ----------
// API::ServerMessageResponse
//-------------------------------------------------------

// ---------- Get BNB Burn Status ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GetBnbBurnStatusObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "feeBurn", response.fee_burn)) return error;

    return SUCCESS;
}
// -----------------------------------------

} // namespace simdjson

//-----------------------------------------------------------------------------

#endif // ACCOUNT_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------
