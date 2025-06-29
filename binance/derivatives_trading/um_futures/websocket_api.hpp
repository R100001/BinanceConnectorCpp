
//------------------------------------------------------------------------------------

#ifndef WEBSOCKET_API_HPP
#define WEBSOCKET_API_HPP

//------------------------------------------------------------------------------------

#include "api_declarations.hpp"

#include "account.hpp"
#include "market_data.hpp"
#include "trade.hpp"

//------------------------------------------------------------------------------------

struct SessionStreamObject {
    std::string api_key;
    int64_t authorized_since;
    int64_t connected_since;
    uint64_t server_time;
    bool return_rate_limits;
};

//------------------------------------------------------------------------------------

#endif // WEBSOCKET_API_HPP

//------------------------------------------------------------------------------------
