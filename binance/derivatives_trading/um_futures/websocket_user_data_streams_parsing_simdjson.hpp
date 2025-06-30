
//-----------------------------------------------------------------------------

#ifndef WEBSOCKET_USER_DATA_STREAMS_PARSING_SIMDJSON_HPP
#define WEBSOCKET_USER_DATA_STREAMS_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------

#include "websocket_user_data_streams.hpp"

#include "utils.hpp"

//-----------------------------------------------------------------------------

namespace simdjson {

using namespace WebsocketUserDataStreams;

// ---------- Listen Key Expired ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ListenKeyExpiredStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;

    return SUCCESS;
}
// ----------------------------------------

// ---------- Account Update ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountUpdateBalances &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "a", response.a)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "wb", response.wb)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cw", response.cw)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bc", response.bc)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountUpdatePositions &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pa", response.pa)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ep", response.ep)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bep", response.bep)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "up", response.up)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "mt", response.mt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "iw", response.iw)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ps", response.ps)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountUpdateUpdateData &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "m", response.m)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "B", response.B)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "P", response.P)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountUpdateStreamObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "a", response.a)) return error;

    return SUCCESS;
}
// ------------------------------------

// ---------- Margin Call ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MarginCallPosition &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ps", response.ps)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pa", response.pa)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "mt", response.mt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "iw", response.iw)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "mp", response.mp)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "up", response.up)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "mm", response.mm)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MarginCallStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cw", response.cw)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;

    return SUCCESS;
}
// ---------------------------------

// ---------- Order Trade Update ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OrderTradeUpdateOrder &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "S", response.S)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "f", response.f)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ap", response.ap)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "sp", response.sp)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "x", response.x)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "X", response.X)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "z", response.z)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "L", response.L)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "N", response.N)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "n", response.n)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "t", response.t)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "b", response.b)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "a", response.a)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "wt", response.wt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ot", response.ot)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ps", response.ps)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "AP", response.AP)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cr", response.cr)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "si", response.si)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ss", response.ss)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "rp", response.rp)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "V", response.V)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pm", response.pm)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "gtd", response.gtd)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "m", response.m)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "R", response.R)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cp", response.cp)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pP", response.pP)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, OrderTradeUpdateStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;

    return SUCCESS;
}
// ----------------------------------------

// ---------- Trade Lite ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, TradeLiteStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "S", response.S)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "t", response.t)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "m", response.m)) return error;

    return SUCCESS;
}
// --------------------------------

// ---------- Account Config Update ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountConfigUpdateAC &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountConfigUpdateAI &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "j", response.j)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AccountConfigUpdateStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    auto iter = obj.begin();

    std::string_view event_type;
    if (auto error = (*iter).value().get(event_type)) return error; ++iter;
    response.e = std::string(event_type);
    if (auto error = (*iter).value().get(response.E)) return error; ++iter;
    if (auto error = (*iter).value().get(response.T)) return error; ++iter;
    std::string_view account_config_type;
    if ((*iter).key() == "ac") {
        AccountConfigUpdateAC ac;
        if (auto error = (*iter).value().get(ac)) return error; ++iter;
        response.a = std::move(ac);
    }
    else if ((*iter).key() == "ai") {
        AccountConfigUpdateAI ai;
        if (auto error = (*iter).value().get(ai)) return error; ++iter;
        response.a = std::move(ai);
    }

    return SUCCESS;
}
// -------------------------------------------

// ---------- Strategy Update ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, StrategyUpdateUpdate &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "si", response.si)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "st", response.st)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ss", response.ss)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ut", response.ut)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, StrategyUpdateStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "su", response.su)) return error;

    return SUCCESS;
}
// -------------------------------------

// ---------- Grid Update ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GridUpdateUpdate &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "si", response.si)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "st", response.st)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ss", response.ss)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "r", response.r)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "up", response.up)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "uq", response.uq)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "uf", response.uf)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "mp", response.mp)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ut", response.ut)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, GridUpdateStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "gu", response.gu)) return error;

    return SUCCESS;
}
// ---------------------------------

// ---------- Conditional Order Trigger Reject ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ConditionalOrderTriggerRejectOrder &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "r", response.r)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ConditionalOrderTriggerRejectStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;

    return SUCCESS;
}
// ------------------------------------------------------

} // namespace simdjson

//-----------------------------------------------------------------------------

#endif // WEBSOCKET_USER_DATA_STREAMS_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------
