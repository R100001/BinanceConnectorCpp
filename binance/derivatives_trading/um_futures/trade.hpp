
#ifndef TRADE_HPP
#define TRADE_HPP

//------------------------------------------------------------------------------------

#include "api_declarations.hpp"

//------------------------------------------------------------------------------------

namespace Trade {

//------------------------------------------------------------------------------------

// Response Objects

struct PriceQtyChange {
    std::string before;
    std::string after;
};

struct Amendment {
    PriceQtyChange price;
    PriceQtyChange orig_qty;
    int32_t count;
};

struct OrderModificationInfo {
    int64_t amending_id;
    std::string symbol;
    std::string pair;
    int64_t order_id;
    std::string client_order_id;
    int64_t time;
    Amendment amendment;
};

struct ForceOrder {
    int64_t order_id;
    std::string symbol;
    std::string status;
    std::string client_order_id;
    std::string price;
    std::string avg_price;
    std::string orig_qty;
    std::string executed_qty;
    std::string cum_quote;
    std::string time_in_force;
    std::string type;
    std::string side;
    std::string position_side;
    std::string stop_price;
    std::string working_type;
    std::string orig_type;
    int64_t time;
    int64_t update_time;
    bool reduce_only;
    bool close_position;
};

struct AccountTrade {
    std::string commission;
    std::string commission_asset;
    int64_t id;
    int64_t order_id;
    std::string price;
    std::string qty;
    std::string quote_qty;
    std::string realized_pnl;
    std::string side;
    std::string position_side;
    std::string symbol;
    int64_t time;
    bool buyer;
    bool maker;
};

struct PositionInfoV2 {
    std::string entry_price;
    std::string break_even_price;
    std::string margin_type;
    std::string is_auto_add_margin;
    std::string isolated_margin;
    std::string leverage;
    std::string liquidation_price;
    std::string mark_price;
    std::string max_notional_value;
    std::string position_amt;
    std::string notional;
    std::string isolated_wallet;
    std::string symbol;
    std::string unrealized_profit;
    std::string position_side;
    int64_t update_time;
};

struct PositionInfoV3 {
    std::string symbol;
    std::string position_side;
    std::string position_amt;
    std::string entry_price;
    std::string break_even_price;
    std::string mark_price;
    std::string unrealized_profit;
    std::string liquidation_price;
    std::string isolated_margin;
    std::string notional;
    std::string margin_asset;
    std::string isolated_wallet;
    std::string initial_margin;
    std::string maint_margin;
    std::string position_initial_margin;
    std::string open_order_initial_margin;
    std::string bid_notional;
    std::string ask_notional;
    int64_t update_time;
    int8_t adl;
};

struct AdlQuantile {
    int8_t hedge;
    int8_t long_;
    int8_t short_;
};

struct AdlQuantileEstimation {
    std::string symbol;
    AdlQuantile adl_quantile;
};

struct PositionMarginChange {
    std::string symbol;
    std::string delta_type;
    std::string amount;
    std::string asset;
    std::string position_side;
    int64_t time;
    int32_t type;
};

//------------------------------------------------------------------------------------

// Response Structs

struct NewOrderObject {
    std::string client_order_id;
    std::string cum_qty;
    std::string cum_quote;
    std::string executed_qty;
    int64_t order_id;
    std::string avg_price;
    std::string orig_qty;
    std::string price;
    std::string side;
    std::string position_side;
    std::string status;
    std::string stop_price;
    std::string symbol;
    std::string time_in_force;
    std::string type;
    std::string orig_type;
    std::string activate_price;
    std::string price_rate;
    int64_t update_time;
    std::string working_type;
    std::string price_match;
    std::string self_trade_prevention_mode;
    int64_t good_till_date;
    bool reduce_only;
    bool price_protect;
    bool close_position;
};
using NewOrderResponse = ResponseOrError<NewOrderObject>;

struct PlaceMultipleOrdersObject {
    std::string client_order_id;
    std::string cum_qty;
    std::string cum_quote;
    std::string executed_qty;
    int64_t order_id;
    std::string avg_price;
    std::string orig_qty;
    std::string price;
    std::string side;
    std::string position_side;
    std::string status;
    std::string stop_price;
    std::string symbol;
    std::string time_in_force;
    std::string type;
    std::string orig_type;
    std::string activate_price;
    std::string price_rate;
    int64_t update_time;
    std::string working_type;
    std::string price_match;
    std::string self_trade_prevention_mode;
    int64_t good_till_date;
    bool reduce_only;
    bool price_protect;
};
using PlaceMultipleOrdersObjectOrError = ResponseOrError<PlaceMultipleOrdersObject>;
using PlaceMultipleOrdersResponse = ArrayErrorsResponse<PlaceMultipleOrdersObject>;

struct ModifyOrderObject {
    int64_t order_id;
    std::string symbol;
    std::string pair;
    std::string status;
    std::string client_order_id;
    std::string price;
    std::string avg_price;
    std::string orig_qty;
    std::string executed_qty;
    std::string cum_qty;
    std::string cum_base;
    std::string time_in_force;
    std::string type;
    std::string side;
    std::string position_side;
    std::string stop_price;
    std::string working_type;
    std::string orig_type;
    std::string price_match;
    std::string self_trade_prevention_mode;
    int64_t good_till_date;
    int64_t update_time;
    bool reduce_only;
    bool close_position;
    bool price_protect;
};
using ModifyOrderResponse = ResponseOrError<ModifyOrderObject>;

using ModifyMultipleOrdersObject = ModifyOrderObject;
using ModifyMultipleOrdersObjectOrError = ResponseOrError<ModifyMultipleOrdersObject>;
using ModifyMultipleOrdersResponse = ArrayErrorsResponse<ModifyMultipleOrdersObject>;

struct GetOrderModifyHistoryObject {
    std::vector<OrderModificationInfo> order_modification_info;
};
using GetOrderModifyHistoryResponse = ResponseOrError<GetOrderModifyHistoryObject>;

struct CancelOrderObject {
    std::string client_order_id;
    std::string cum_qty;
    std::string cum_quote;
    std::string executed_qty;
    int64_t order_id;
    std::string orig_qty;
    std::string orig_type;
    std::string price;
    std::string side;
    std::string position_side;
    std::string status;
    std::string stop_price;
    std::string symbol;
    std::string time_in_force;
    std::string type;
    std::string activate_price;
    std::string price_rate;
    int64_t update_time;
    std::string working_type;
    std::string price_match;
    std::string self_trade_prevention_mode;
    int64_t good_till_date;
    bool reduce_only;
    bool close_position;
    bool price_protect;
};
using CancelOrderResponse = ResponseOrError<CancelOrderObject>;

using CancelMultipleOrdersObject = CancelOrderObject;
using CancelMultipleOrdersObjectOrError = ResponseOrError<CancelMultipleOrdersObject>;
using CancelMultipleOrdersResponse = ArrayErrorsResponse<CancelMultipleOrdersObject>;

using CancelAllOpenOrdersObject = ServerMessageResponse;
using CancelAllOpenOrdersResponse = CancelAllOpenOrdersObject;

struct AutoCancelAllOpenOrdersObject {
    std::string symbol;
    int64_t countdown_time;
};
using AutoCancelAllOpenOrdersResponse = ResponseOrError<AutoCancelAllOpenOrdersObject>;

struct QueryOrderObject {
    std::string avg_price;
    std::string client_order_id;
    std::string cum_quote;
    std::string executed_qty;
    int64_t order_id;
    std::string orig_qty;
    std::string orig_type;
    std::string price;
    std::string side;
    std::string position_side;
    std::string status;
    std::string stop_price;
    std::string symbol;
    int64_t time;
    std::string time_in_force;
    std::string type;
    std::string activate_price;
    std::string price_rate;
    int64_t update_time;
    std::string working_type;
    std::string price_match;
    std::string self_trade_prevention_mode;
    int64_t good_till_date;
    bool reduce_only;
    bool close_position;
    bool price_protect;
};
using QueryOrderResponse = ResponseOrError<QueryOrderObject>;

struct QueryAllOrdersObject {
    std::vector<QueryOrderObject> orders;
};
using QueryAllOrdersResponse = ResponseOrError<QueryAllOrdersObject>;

struct QueryCurrentAllOpenOrdersObject {
    std::vector<QueryOrderObject> orders;
};
using QueryCurrentAllOpenOrdersResponse = ResponseOrError<QueryCurrentAllOpenOrdersObject>;

struct QueryCurrentOpenOrderObject {
    QueryOrderObject order;
};
using QueryCurrentOpenOrderResponse = ResponseOrError<QueryCurrentOpenOrderObject>;

struct QueryUsersForceOrdersObject {
    std::vector<ForceOrder> force_orders;
};
using QueryUsersForceOrdersResponse = ResponseOrError<QueryUsersForceOrdersObject>;

struct QueryAccountTradeListObject {
    std::vector<AccountTrade> trades;
};
using QueryAccountTradeListResponse = ResponseOrError<QueryAccountTradeListObject>;

using ChangeMarginTypeObject = ServerMessageResponse;
using ChangeMarginTypeResponse = ChangeMarginTypeObject;

using ChangePositionModeObject = ServerMessageResponse;
using ChangePositionModeResponse = ChangePositionModeObject;

struct ChangeInitialLeverageObject {
    std::string max_notional_value;
    std::string symbol;
    int16_t leverage;
};
using ChangeInitialLeverageResponse = ResponseOrError<ChangeInitialLeverageObject>;

using ChangeMultiAssetsModeObject = ServerMessageResponse;
using ChangeMultiAssetsModeResponse = ChangeMarginTypeObject;

struct ModifyIsolatedPositionMarginObject {
    ServerMessageResponse message;
    double amount;
    int32_t type;
};
using ModifyIsolatedPositionMarginResponse = ResponseOrError<ModifyIsolatedPositionMarginObject>;

struct PositionInformationV2Object {
    std::vector<PositionInfoV2> positions;
};
using PositionInformationV2Response = ResponseOrError<PositionInformationV2Object>;

struct PositionInformationV3Object {
    std::vector<PositionInfoV3> positions;
};
using PositionInformationV3Response = ResponseOrError<PositionInformationV3Object>;

struct PositionAdlQuantileEstimationObject {
    std::vector<AdlQuantileEstimation> adl_quantile_estimations;
};
using PositionAdlQuantileEstimationResponse = ResponseOrError<PositionAdlQuantileEstimationObject>;

struct GetPositionMarginChangeHistoryObject {
    std::vector<PositionMarginChange> position_margin_changes;
};
using GetPositionMarginChangeHistoryResponse = ResponseOrError<GetPositionMarginChangeHistoryObject>;

struct TestNewOrderObject {
    NewOrderObject order;
};
using TestNewOrderResponse = ResponseOrError<TestNewOrderObject>;

//------------------------------------------------------------------------------------

// Structs

struct NewOrder {
    std::string symbol;
    std::string type;
    std::string side;
    std::string position_side = "";
    double price = -1;
    double quantity = -1;
    std::string time_in_force = "";
    double stop_price = -1;
    std::string new_client_order_id = "";
    double activation_price = -1;
    double callback_rate = -1;
    std::string working_type = "";
    std::string new_order_resp_type = "";
    std::string price_match = "";
    std::string self_trade_prevention_mode = "";
    int64_t good_till_date = -1;
    bool reduce_only = false;
    bool price_protect = false;
};

struct ModifyOrder {
    std::string symbol;
    std::string side;
    double price = -1;
    double quantity = -1;
    int64_t const order_id = -1;
    std::string orig_client_order_id = "";
    std::string price_match = "";
};

//-------------------------------------------------------------------------------------

} // namespace Trade

//------------------------------------------------------------------------------------

#endif // TRADE_HPP

//------------------------------------------------------------------------------------
