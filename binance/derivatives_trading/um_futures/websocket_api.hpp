
//------------------------------------------------------------------------------------

#ifndef WEBSOCKET_API_HPP
#define WEBSOCKET_API_HPP

//------------------------------------------------------------------------------------

#include "api_declarations.hpp"

#include "account.hpp"
#include "market_data.hpp"
#include "trade.hpp"

//------------------------------------------------------------------------------------

struct SessionObject {
    std::string api_key;
    int64_t authorized_since;
    int64_t connected_since;
    uint64_t server_time;
    bool return_rate_limits;
};

//------------------------------------------------------------------------------------

namespace Account {

//------------------------------------------------------------------------------------

using FuturesAccountBalanceStreamObject = Account::FuturesAccountBalanceObject;
using AccountInformationV3StreamObject = Account::AccountInformationV3Object;
using AccountInformationStreamObject = Account::AccountInformationObject;

//------------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------------

namespace MarketData {

//------------------------------------------------------------------------------------

using OrderBookStreamObject = MarketData::OrderBookObject;
using SymbolPriceTickerStreamObject = MarketData::SymbolPriceTickerObject;
using SymbolOrderBookTickerStreamObject = MarketData::SymbolOrderBookTickerObject;

//------------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------------

namespace Trade {

//------------------------------------------------------------------------------------

struct NewOrderStreamObject {
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
    int64_t update_time;
    std::string working_type;
    std::string price_match;
    std::string self_trade_prevention_mode;
    int64_t good_till_date;
    bool reduce_only;
    bool price_protect;
    bool close_position;
};

struct ModifyOrderStreamObject {
    int64_t order_id;
    std::string symbol;
    std::string status;
    std::string client_order_id;
    std::string price;
    std::string avg_price;
    std::string orig_qty;
    std::string executed_qty;
    std::string cum_qty;
    std::string cum_quote;
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

using CancelOrderStreamObject = Trade::CancelOrderObject;

struct QueryOrderStreamObject {
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
    bool reduce_only;
    bool close_position;
    bool price_protect;
};

using PositionInformationV2StreamObject = Trade::PositionInformationV3Object;
using PositionInformationStreamObject = Trade::PositionInformationV2Object;

//------------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------------

#endif // WEBSOCKET_API_HPP

//------------------------------------------------------------------------------------
