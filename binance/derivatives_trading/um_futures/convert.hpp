
#ifndef CONVERT_HPP
#define CONVERT_HPP

//------------------------------------------------------------------------------------

#include "api_declarations.hpp"

//------------------------------------------------------------------------------------

namespace Convert {

//------------------------------------------------------------------------------------

// Response Objects

struct ConvertPairs {
    std::string from_asset;
    std::string to_asset;
    std::string from_asset_min_amount;
    std::string from_asset_max_amount;
    std::string to_asset_min_amount;
    std::string to_asset_max_amount;
};

//------------------------------------------------------------------------------------

// Response Structs

struct ListAllConvertedPairsObject {
    std::vector<ConvertPairs> pairs;
};
using ListAllConvertedPairsResponse = ResponseOrError<ListAllConvertedPairsObject>;

struct SendQuoteRequestObject {
    std::string quote_id;
    std::string ratio;
    std::string inverse_ratio;
    std::string from_amount;
    std::string to_amount;
    int64_t valid_timestamp;
};
using SendQuoteRequestResponse = ResponseOrError<SendQuoteRequestObject>;

struct AcceptQuoteObject {
    std::string order_id;
    std::string order_status;
    int64_t create_time;
};
using AcceptQuoteResponse = ResponseOrError<AcceptQuoteObject>;

struct OrderStatusObject {
    int64_t order_id;
    std::string order_status;
    std::string from_asset;
    std::string from_amount;
    std::string to_asset;
    std::string to_amount;
    std::string ratio;
    std::string inverse_ratio;
    int64_t create_time;
};
using OrderStatusResponse = ResponseOrError<OrderStatusObject>;

//------------------------------------------------------------------------------------

} // namespace Convert

//------------------------------------------------------------------------------------

#endif // CONVERT_HPP

//------------------------------------------------------------------------------------
