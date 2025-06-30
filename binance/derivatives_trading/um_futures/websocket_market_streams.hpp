
//------------------------------------------------------------------------------------

#ifndef WEBSOCKET_MARKET_STREAMS_HPP
#define WEBSOCKET_MARKET_STREAMS_HPP

//------------------------------------------------------------------------------------

#include <cstdint>
#include <string>
#include <vector>

#include "api_declarations.hpp"

#include "market_data.hpp"

//------------------------------------------------------------------------------------

enum class WebsocketMarketStreamsMethod : uint8_t {
    SUBSCRIBE,
    UNSUBSCRIBE,
};

//------------------------------------------------------------------------------------

namespace WebsocketMarketStreams {

struct AggregateTradeStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
    uint64_t a;
    std::string p;
    std::string q;
    uint64_t f;
    uint64_t l;
    uint64_t T;
    bool m;
};

struct MarkPriceStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
    std::string p;
    std::string i;
    std::string P;
    std::string r;
    uint64_t T;
};

struct MarkPriceStreamForAllMarketStreamObject {
    std::vector<MarkPriceStreamObject> data;
};

struct KLine {
    uint64_t t;
    uint64_t T;
    std::string s;
    std::string i;
    uint64_t f;
    uint64_t L;
    std::string o;
    std::string c;
    std::string h;
    std::string l;
    std::string v;
    std::string q;
    std::string V;
    std::string Q;
    std::string B;
    uint32_t n;
    bool x;
};
struct KLineStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
    KLine k;
};

struct ContinuousKLine {
    uint64_t t;
    uint64_t T;
    std::string i;
    uint64_t f;
    uint64_t L;
    std::string o;
    std::string c;
    std::string h;
    std::string l;
    std::string v;
    std::string q;
    std::string V;
    std::string Q;
    std::string B;
    uint32_t n;
    bool x;
};
struct ContinuousKLineStreamObject {
    std::string e;
    uint64_t E;
    std::string ps;
    std::string ct;
    ContinuousKLine k;
};

struct MiniTicker24hrStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
    std::string c;
    std::string o;
    std::string h;
    std::string l;
    std::string v;
    std::string q;
};

struct MiniTickerAll24hrStreamObject {
    std::vector<MiniTicker24hrStreamObject> data;
};

struct Ticker24hrStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
    std::string p;
    std::string P;
    std::string w;
    std::string c;
    std::string Q;
    std::string o;
    std::string h;
    std::string l;
    std::string v;
    std::string q;
    uint64_t O;
    uint64_t C;
    uint64_t F;
    uint64_t L;
    uint32_t n;
};

struct TickerAll24hrStreamObject {
    std::vector<Ticker24hrStreamObject> data;
};

struct BookTickerStreamObject {
    std::string e;
    uint64_t u;
    uint64_t E;
    uint64_t T;
    std::string s;
    std::string b;
    std::string B;
    std::string a;
    std::string A;
};

using BookTickerAllStreamObject = BookTickerStreamObject;

struct LiquidationOrder {
    std::string s;
    std::string S;
    std::string o;
    std::string f;
    std::string q;
    std::string p;
    std::string ap;
    std::string X;
    std::string l;
    std::string z;
    uint64_t T;
};
struct ForceOrderStreamObject {
    std::string e;
    uint64_t E;
    LiquidationOrder o;
};

using ForceOrderAllStreamObject = ForceOrderStreamObject;

struct DepthUpdatePartialStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    std::string s;
    uint64_t U;
    uint64_t u;
    uint64_t pu;
    std::vector<MarketData::BidAskEntry> a;
    std::vector<MarketData::BidAskEntry> b;
};

using DepthUpdateDiffStreamObject = DepthUpdatePartialStreamObject;

struct CompositeIndexComposition {
    std::string b;
    std::string q;
    std::string w;
    std::string W;
    std::string i;
};
struct CompositeIndexStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
    std::string p;
    std::string C;
    std::vector<CompositeIndexComposition> c;
};

struct ContractInfoBrackets {
    uint32_t bs;
    uint32_t bnf;
    uint32_t bnc;
    float mmr;
    uint32_t cf;
    uint16_t mi;
    uint16_t ma;
};
struct ContractInfoStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
    std::string ps;
    std::string ct;
    uint64_t dt;
    uint64_t ot;
    std::string cs;
    std::vector<ContractInfoBrackets> bks;
};

struct AssetIndexUpdate {
    std::string e;
    uint64_t E;
    std::string s;
    std::string i;
    std::string b;
    std::string a;
    std::string B;
    std::string A;
    std::string q;
    std::string g;
    std::string Q;
    std::string G;
};
struct AssetIndexUpdateStreamObject {
    std::vector<AssetIndexUpdate> data;
};

//------------------------------------------------------------------------------------

} // namespace WebsocketMarketStreams

//------------------------------------------------------------------------------------

#endif // WEBSOCKET_MARKET_STREAMS_HPP

//------------------------------------------------------------------------------------
