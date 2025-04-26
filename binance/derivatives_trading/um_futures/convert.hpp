
#ifndef CONVERT_HPP
#define CONVERT_HPP

//------------------------------------------------------------------------------------

#include "api.hpp"
#include "error.hpp"

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
using ListAllConvertedPairsResponse = API::ResponseOrError<ListAllConvertedPairsObject>;

struct SendQuoteRequestObject {
    std::string quote_id;
    std::string ratio;
    std::string inverse_ratio;
    std::string from_amount;
    std::string to_amount;
    int64_t valid_timestamp;
};
using SendQuoteRequestResponse = API::ResponseOrError<SendQuoteRequestObject>;

struct AcceptQuoteObject {
    std::string order_id;
    std::string order_status;
    int64_t create_time;
};
using AcceptQuoteResponse = API::ResponseOrError<AcceptQuoteObject>;

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
using OrderStatusResponse = API::ResponseOrError<OrderStatusObject>;

//------------------------------------------------------------------------------------

// REST API Endpoints

namespace RestAPI {

ListAllConvertedPairsResponse   list_all_converted_pairs(API &api, std::string const &from_asset = "", std::string const &to_asset = "");
SendQuoteRequestResponse        send_quote_request(API &api, std::string const &from_asset, std::string const &to_asset, double const from_amount = -1, double const to_amount = -1, std::string const valid_time = "", int32_t const recv_window = -1);
AcceptQuoteResponse             accept_quote(API &api, std::string const &quote_id, int32_t const recv_window = -1);
OrderStatusResponse             order_status(API &api, std::string const &order_id = "", std::string const &quote_id = "");

} // namespace RestAPI

//------------------------------------------------------------------------------------

// Websocket API Endpoints

namespace WebsocketAPI {



} // namespace WebsocketAPI

//------------------------------------------------------------------------------------

} // namespace Convert

//------------------------------------------------------------------------------------

#endif // CONVERT_HPP

//------------------------------------------------------------------------------------
