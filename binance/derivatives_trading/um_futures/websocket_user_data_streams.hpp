
//------------------------------------------------------------------------------------

#ifndef WEBSOCKET_USER_DATA_STREAMS_HPP
#define WEBSOCKET_USER_DATA_STREAMS_HPP

//------------------------------------------------------------------------------------

#include <cstdint>

#include "api_declarations.hpp"

//------------------------------------------------------------------------------------

namespace WebsocketUserDataStreams {

struct ListenKeyExpiredStreamObject {
    std::string e;
    uint64_t E;
    std::string s;
};

struct AccountUpdateBalances {
    std::string a;
    std::string wb;
    std::string cw;
    std::string bc;
};
struct AccountUpdatePositions {
    std::string s;
    std::string pa;
    std::string ep;
    std::string bep;
    std::string up;
    std::string mt;
    std::string iw;
    std::string ps;
};
struct AccountUpdateUpdateData {
    std::string m;
    std::vector<AccountUpdateBalances> B;
    std::vector<AccountUpdatePositions> P;
};
struct AccountUpdateStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    AccountUpdateUpdateData a;
};

struct MarginCallPosition {
    std::string s;
    std::string ps;
    std::string pa;
    std::string mt;
    std::string iw;
    std::string mp;
    std::string up;
    std::string mm;
};
struct MarginCallStreamObject {
    std::string e;
    uint64_t E;
    std::string cw;
    std::vector<MarginCallPosition> p;
};

struct OrderTradeUpdateOrder {
    std::string s;
    std::string c;
    std::string S;
    std::string o;
    std::string f;
    std::string q;
    std::string p;
    std::string ap;
    std::string sp;
    std::string x;
    std::string X;
    uint64_t i;
    std::string l;
    std::string z;
    std::string L;
    std::string N;
    std::string n;
    uint64_t T;
    uint64_t t;
    std::string b;
    std::string a;
    std::string wt;
    std::string ot;
    std::string ps;
    std::string AP;
    std::string cr;
    uint64_t si;
    uint64_t ss;
    std::string rp;
    std::string V;
    std::string pm;
    uint64_t gtd;
    bool m;
    bool R;
    bool cp;
    bool pP;
};
struct OrderTradeUpdateStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    OrderTradeUpdateOrder o;
};

struct TradeLiteStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    std::string s;
    std::string q;
    std::string p;
    std::string c;
    std::string S;
    std::string l;
    uint64_t t;
    uint64_t i;
    bool m;
};

struct AccountConfigUpdateAC {
    std::string s;
    uint8_t l;
};
struct AccountConfigUpdateAI {
    bool j;
};
struct AccountConfigUpdateStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    std::variant<AccountConfigUpdateAC, AccountConfigUpdateAI> a;
};

struct StrategyUpdateUpdate {
    uint64_t si;
    std::string st;
    std::string ss;
    std::string s;
    uint64_t ut;
    uint16_t c;
};
struct StrategyUpdateStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    StrategyUpdateUpdate su;
};

struct GridUpdateUpdate {
    uint64_t si;
    std::string st;
    std::string ss;
    std::string s;
    std::string r;
    std::string up;
    std::string uq;
    std::string uf;
    std::string mp;
    uint64_t ut;
};
struct GridUpdateStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    GridUpdateUpdate gu;
};

struct ConditionalOrderTriggerRejectOrder {
    std::string s;
    uint64_t i;
    std::string r;
};
struct ConditionalOrderTriggerRejectStreamObject {
    std::string e;
    uint64_t E;
    uint64_t T;
    ConditionalOrderTriggerRejectOrder o;
};

} // namespace WebsocketUserDataStreams

//------------------------------------------------------------------------------------

#endif // WEBSOCKET_USER_DATA_STREAMS_HPP

//------------------------------------------------------------------------------------
