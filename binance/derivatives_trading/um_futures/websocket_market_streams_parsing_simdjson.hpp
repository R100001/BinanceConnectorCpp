
//-----------------------------------------------------------------------------

#ifndef WEBSOCKET_MARKET_STREAMS_PARSING_SIMDJSON_HPP
#define WEBSOCKET_MARKET_STREAMS_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------

#include "websocket_market_streams.hpp"

#include "market_data_parsing_simdjson.hpp"
#include "utils.hpp"

//-----------------------------------------------------------------------------

namespace simdjson {

using namespace WebsocketMarketStreams;

// ---------- Aggregate Trade ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AggregateTradeStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "a", response.a)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "f", response.f)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "m", response.m)) return error;

    return SUCCESS;
}
// -------------------------------------

// ---------- Mark Price ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MarkPriceStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "P", response.P)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "r", response.r)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;

    return SUCCESS;

}
// --------------------------------

// ---------- Mark Price for All Market ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MarkPriceStreamForAllMarketStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "data", response.data)) return error;

    return SUCCESS;
}
// -----------------------------------------------

// ---------- KLine ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, KLine &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "t", response.t)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "f", response.f)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "L", response.L)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "h", response.h)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "v", response.v)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "V", response.V)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "Q", response.Q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "B", response.B)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "n", response.n)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "x", response.x)) return error;

    return SUCCESS;

}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, KLineStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "k", response.k)) return error;

    return SUCCESS;
}
// ---------------------------

// ---------- Continuous KLine ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ContinuousKLine &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "t", response.t)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "f", response.f)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "L", response.L)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "h", response.h)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "v", response.v)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "V", response.V)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "Q", response.Q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "B", response.B)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "n", response.n)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "x", response.x)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ContinuousKLineStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ps", response.ps)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ct", response.ct)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "k", response.k)) return error;

    return SUCCESS;
}
// --------------------------------------

// ---------- Mini Ticker 24hr ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MiniTicker24hrStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "h", response.h)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "v", response.v)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;

    return SUCCESS;
}
// --------------------------------------

// ---------- Mini Ticker All 24hr ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, MiniTickerAll24hrStreamObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "data", response.data)) return error;

    return SUCCESS;
}
// ------------------------------------------

// ---------- Ticker 24hr ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, Ticker24hrStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "P", response.P)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "w", response.w)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "Q", response.Q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "h", response.h)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "v", response.v)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "O", response.O)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "C", response.C)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "F", response.F)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "L", response.L)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "n", response.n)) return error;

    return SUCCESS;
}
// ---------------------------------

// ---------- Ticker All 24hr ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, TickerAll24hrStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "data", response.data)) return error;

    return SUCCESS;
}
// -------------------------------------

// ---------- BookTicker ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, BookTickerStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "u", response.u)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "b", response.b)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "B", response.B)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "a", response.a)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "A", response.A)) return error;

    return SUCCESS;
}
// --------------------------------

// ---------- BookTicker for All Market ----------
// BookTicker
// -----------------------------------------------

// ---------- Force Order ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, LiquidationOrder &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "S", response.S)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "f", response.f)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ap", response.ap)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "X", response.X)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "l", response.l)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "z", response.z)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ForceOrderStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "o", response.o)) return error;

    return SUCCESS;
}
// ---------------------------------

// ---------- Force Order for All Market ----------
// ForceOrder
// ------------------------------------------------

// ---------- Depth Update Partial ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, DepthUpdatePartialStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "T", response.T)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "U", response.U)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "u", response.u)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "pu", response.pu)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "b", response.b)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "a", response.a)) return error;

    return SUCCESS;
}
// ------------------------------------------

// ---------- Depth Update Diff ----------
// DepthUpdatePartial
// ---------------------------------------

// ---------- Composite Index ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CompositeIndexComposition &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "b", response.b)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "w", response.w)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "W", response.W)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, CompositeIndexStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "p", response.p)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "C", response.C)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "c", response.c)) return error;

    return SUCCESS;
}
// -------------------------------------

// ---------- Contract Info ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ContractInfoBrackets &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "bs", response.bs)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bnf", response.bnf)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bnc", response.bnc)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "mmr", response.mmr)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cf", response.cf)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "mi", response.mi)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ma", response.ma)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ContractInfoStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ps", response.ps)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ct", response.ct)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "dt", response.dt)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "ot", response.ot)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "cs", response.cs)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "bks", response.bks)) return error;

    return SUCCESS;
}
// -----------------------------------

// ---------- Asset Index Update ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AssetIndexUpdate &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "e", response.e)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "E", response.E)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "s", response.s)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "i", response.i)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "b", response.b)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "a", response.a)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "B", response.B)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "A", response.A)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "q", response.q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "g", response.g)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "Q", response.Q)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "G", response.G)) return error;

    return SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, AssetIndexUpdateStreamObject &response) {

    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "data", response.data)) return error;

    return SUCCESS;
}
// ----------------------------------------

} // namespace simdjson

//-----------------------------------------------------------------------------

#endif // WEBSOCKET_MARKET_STREAMS_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------
