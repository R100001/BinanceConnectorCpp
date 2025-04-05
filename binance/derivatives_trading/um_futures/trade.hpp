
#ifndef TRADE_HPP
#define TRADE_HPP

//------------------------------------------------------------------------------------

#include "derivatives_trading.hpp"
#include "error.hpp"

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
using NewOrderResponse = API::ResponseOrError<NewOrderObject>;

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
using PlaceMultipleOrdersResponse = API::ArrayErrorsResponse<PlaceMultipleOrdersObject>;

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
using ModifyOrderResponse = API::ResponseOrError<ModifyOrderObject>;

using ModifyMultipleOrdersObject = ModifyOrderObject;
using ModifyMultipleOrdersResponse = API::ArrayErrorsResponse<ModifyMultipleOrdersObject>;

struct GetOrderModifyHistoryObject {
    std::vector<OrderModificationInfo> order_modification_info;
};
using GetOrderModifyHistoryResponse = API::ResponseOrError<GetOrderModifyHistoryObject>;

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
using CancelOrderResponse = API::ResponseOrError<CancelOrderObject>;

using CancelMultipleOrdersObject = CancelOrderObject;
using CancelMultipleOrdersResponse = API::ArrayErrorsResponse<CancelMultipleOrdersObject>;

using CancelAllOpenOrdersObject = API::ServerMessageResponse;
using CancelAllOpenOrdersResponse = CancelAllOpenOrdersObject;

struct AutoCancelAllOpenOrdersObject {
    std::string symbol;
    int64_t countdown_time;
};
using AutoCancelAllOpenOrdersResponse = API::ResponseOrError<AutoCancelAllOpenOrdersObject>;

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
using QueryOrderResponse = API::ResponseOrError<QueryOrderObject>;

struct QueryAllOrdersObject {
    std::vector<QueryOrderObject> orders;
};
using QueryAllOrdersResponse = API::ResponseOrError<QueryAllOrdersObject>;

struct QueryCurrentAllOpenOrdersObject {
    std::vector<QueryOrderObject> orders;
};
using QueryCurrentAllOpenOrdersResponse = API::ResponseOrError<QueryCurrentAllOpenOrdersObject>;

struct QueryCurrentOpenOrderObject {
    QueryOrderObject order;
};
using QueryCurrentOpenOrderResponse = API::ResponseOrError<QueryCurrentOpenOrderObject>;

struct QueryUsersForceOrdersObject {
    std::vector<ForceOrder> force_orders;
};
using QueryUsersForceOrdersResponse = API::ResponseOrError<QueryUsersForceOrdersObject>;

struct QueryAccountTradeListObject {
    std::vector<AccountTrade> trades;
};
using QueryAccountTradeListResponse = API::ResponseOrError<QueryAccountTradeListObject>;

using ChangeMarginTypeObject = API::ServerMessageResponse;
using ChangeMarginTypeResponse = ChangeMarginTypeObject;

using ChangePositionModeObject = API::ServerMessageResponse;
using ChangePositionModeResponse = ChangePositionModeObject;

struct ChangeInitialLeverageObject {
    std::string max_notional_value;
    std::string symbol;
    int16_t leverage;
};
using ChangeInitialLeverageResponse = API::ResponseOrError<ChangeInitialLeverageObject>;

using ChangeMultiAssetsModeObject = API::ServerMessageResponse;
using ChangeMultiAssetsModeResponse = ChangeMarginTypeObject;

struct ModifyIsolatedPositionMarginObject {
    API::ServerMessageResponse message;
    double amount;
    int32_t type;
};
using ModifyIsolatedPositionMarginResponse = API::ResponseOrError<ModifyIsolatedPositionMarginObject>;

struct PositionInformationV2Object {
    std::vector<PositionInfoV2> positions;
};
using PositionInformationV2Response = API::ResponseOrError<PositionInformationV2Object>;

struct PositionInformationV3Object {
    std::vector<PositionInfoV3> positions;
};
using PositionInformationV3Response = API::ResponseOrError<PositionInformationV3Object>;

struct PositionAdlQuantileEstimationObject {
    std::vector<AdlQuantileEstimation> adl_quantile_estimations;
};
using PositionAdlQuantileEstimationResponse = API::ResponseOrError<PositionAdlQuantileEstimationObject>;

struct GetPositionMarginChangeHistoryObject {
    std::vector<PositionMarginChange> position_margin_changes;
};
using GetPositionMarginChangeHistoryResponse = API::ResponseOrError<GetPositionMarginChangeHistoryObject>;

struct TestNewOrderObject {
    NewOrderObject order;
};
using TestNewOrderResponse = API::ResponseOrError<TestNewOrderObject>;

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

//------------------------------------------------------------------------------------

// REST API Endpoints

namespace RestAPI {

NewOrderResponse                        new_order(DerivativesTrading &api, NewOrder const &order, bool const close_position = false, int32_t const recv_window = -1);
PlaceMultipleOrdersResponse             place_multiple_orders(DerivativesTrading &api, std::vector<NewOrder> const &orders, int32_t const recv_window = -1);
ModifyOrderResponse                     modify_order(DerivativesTrading &api, ModifyOrder const &order, int32_t const recv_window = -1);
ModifyMultipleOrdersResponse            modify_multiple_orders(DerivativesTrading &api, std::vector<ModifyOrder> const &orders, int32_t const recv_window = -1);
GetOrderModifyHistoryResponse           get_order_modify_history(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int64_t const start_time = -1, int64_t const end_time = -1, int8_t const limit = -1, int32_t const recv_window = -1);
CancelOrderResponse                     cancel_order(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
CancelMultipleOrdersResponse            cancel_multiple_orders(DerivativesTrading &api, std::string const &symbol, std::vector<int64_t> const &order_ids, std::vector<std::string> const &orig_client_order_ids, int32_t const recv_window = -1);
CancelAllOpenOrdersResponse             cancel_all_open_orders(DerivativesTrading &api, std::string const &symbol, int32_t const recv_window = -1);
AutoCancelAllOpenOrdersResponse         auto_cancel_all_open_orders(DerivativesTrading &api, std::string const &symbol, int64_t const countdown_time, int32_t const recv_window = -1);
QueryOrderResponse                      query_order(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
QueryAllOrdersResponse                  query_all_orders(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, int64_t const start_time = -1, int64_t const end_time = -1, int16_t const limit = -1, int32_t const recv_window = -1);
QueryCurrentAllOpenOrdersResponse       query_current_all_open_orders(DerivativesTrading &api, std::string const &symbol = "", int32_t const recv_window = -1);
QueryCurrentOpenOrderResponse           query_current_open_order(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
QueryUsersForceOrdersResponse           query_users_force_orders(DerivativesTrading &api, std::string const &symbol = "", std::string const &auto_close_type = "", int64_t const start_time = -1, int64_t const end_time = -1, int8_t const limit = -1, int32_t const recv_window = -1);
QueryAccountTradeListResponse           query_account_trade_list(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, int64_t const start_time = -1, int64_t const end_time = -1, int64_t const from_id = -1, int16_t const limit = -1, int32_t const recv_window = -1);
ChangeMarginTypeResponse                change_margin_type(DerivativesTrading &api, std::string const &symbol, std::string const &margin_type, int32_t const recv_window = -1);
ChangePositionModeResponse              change_position_mode(DerivativesTrading &api, std::string const &dual_side_position, int32_t const recv_window = -1);
ChangeInitialLeverageResponse           change_initial_leverage(DerivativesTrading &api, std::string const &symbol, int8_t const leverage, int32_t const recv_window = -1);
ChangeMultiAssetsModeResponse           change_multi_assets_mode(DerivativesTrading &api, std::string const &multi_assets_margin, int32_t const recv_window = -1);
ModifyIsolatedPositionMarginResponse    modify_isolated_position_margin(DerivativesTrading &api, std::string const &symbol, double const amount, int8_t const type, std::string const &position_side, int32_t const recv_window = -1);
PositionInformationV2Response           position_information_v2(DerivativesTrading &api, std::string const &symbol = "", int32_t const recv_window = -1);
PositionInformationV3Response           position_information_v3(DerivativesTrading &api, std::string const &symbol = "", int32_t const recv_window = -1);
PositionAdlQuantileEstimationResponse   position_adl_quantile_estimation(DerivativesTrading &api, std::string const &symbol = "", int32_t const recv_window = -1);
GetPositionMarginChangeHistoryResponse  get_position_margin_change_history(DerivativesTrading &api, std::string const &symbol, int8_t const type, int64_t const start_time = -1, int64_t const end_time = -1, int32_t const limit = -1, int32_t const recv_window = -1);
TestNewOrderResponse                    test_new_order(DerivativesTrading &api, NewOrder const &order, bool const close_position = false, int32_t const recv_window = -1);

} // namespace RestAPI

//------------------------------------------------------------------------------------

// Websocket API Endpoints

namespace WebsocketAPI {

void new_order(DerivativesTrading &api, NewOrder const &order, bool const close_position = false, int32_t const recv_window = -1);
void modify_order(DerivativesTrading &api, ModifyOrder const &order, int32_t const recv_window = -1);
void cancel_order(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
void query_order(DerivativesTrading &api, std::string const &symbol, int64_t const order_id = -1, std::string const orig_client_order_id = "", int32_t const recv_window = -1);
void position_information_v2(DerivativesTrading &api, std::string const &symbol = "", int32_t const recv_window = -1);
void position_information(DerivativesTrading &api, std::string const &symbol = "", int32_t const recv_window = -1);

} // namespace WebsocketAPI

//------------------------------------------------------------------------------------

} // namespace Trade

//------------------------------------------------------------------------------------

#endif // TRADE_HPP

//------------------------------------------------------------------------------------
