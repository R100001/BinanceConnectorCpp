
//------------------------------------------------------------------------------------

#ifndef WEBSOCKET_MARKET_STREAMS_HPP
#define WEBSOCKET_MARKET_STREAMS_HPP

//------------------------------------------------------------------------------------

#include <cstdint>

#include "api_declarations.hpp"

//------------------------------------------------------------------------------------

enum class WebsocketMarketStreamsMethod : uint8_t {
    SUBSCRIBE,
    UNSUBSCRIBE,
};

//------------------------------------------------------------------------------------

#endif // WEBSOCKET_MARKET_STREAMS_HPP
