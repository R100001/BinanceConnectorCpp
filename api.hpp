
#ifndef API_HPP
#define API_HPP

//------------------------------------------------------------------------------------

#include <string>
#include <unordered_map>
#include <vector>
#include <variant>
#include <memory>

#include "lib/HTTPClient.hpp"
#include "simdjson.h"

#include "error.hpp"
#include "lib/utils.hpp"

//------------------------------------------------------------------------------------

class API {

public: // Typedefs

    using Parameter = std::variant<bool, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, double, std::string>;
    using Parameters = std::vector<std::pair<std::string, Parameter>>;
    using APIResponse = std::variant<simdjson::ondemand::object, ServerMessage>;

public: // Constructors

    API(
        std::string const &base_url,
        std::string const &key,
        std::string const &secret = "",
        int32_t const timeout = -1,
        std::string const &proxy = "",
        bool const show_limit_usage = false,
        bool const show_header = false,
        std::string const &private_key = "",
        std::string const &private_key_passphrase = ""
    );

public: // Public requests

    std::string query(std::string const &url, Parameters const &payload = {});
    std::string limit_request(std::string const &http_method, std::string const &url, Parameters const &payload);
    std::string sign_request(std::string const &http_method, std::string const &url, Parameters &payload, bool const special = false);
    std::string limited_encoded_sign_request(std::string const &http_method, std::string &url, Parameters &payload);
    std::string send_request(std::string const &http_method, std::string const &url, Parameters const &payload = {}, bool const special = false);
    

public: // Public message parsing

    /*----- Parsing Tags -----*/
    struct ArrayErrors {};
    struct ResponseIsServerMessage {};

    /*----- Parsing Responses -----*/
    template <typename JsonResponseStructured> 
    using ResponseOrError = std::variant<JsonResponseStructured, ServerMessage>;
    template <typename JsonResponseStructured>
    using ArrayErrorsResponse = ResponseOrError<std::vector<ResponseOrError<JsonResponseStructured>>>;
    using ServerMessageResponse = ServerMessage;

    /*----- Parsing Functions -----*/
    template <typename JsonResponseStructured> 
    ResponseOrError<JsonResponseStructured> parse_response(std::string &response);

    template <typename JsonResponseStructured>
    ArrayErrorsResponse<JsonResponseStructured> parse_response(std::string &response, ArrayErrors const);

    ServerMessageResponse parse_response(std::string &response, ResponseIsServerMessage const);

    std::optional<ServerMessageResponse> read_server_message(simdjson::ondemand::object &obj) const;

    simdjson::ondemand::parser &get_parser() { return this->_parser; }

private: // Private message parsing

    template <typename JsonResponseStructured>
    ResponseOrError<JsonResponseStructured> parse_json_value(simdjson::ondemand::value value);
 
private: // Private methods

    std::string prepare_params(Parameters const &params, bool const special = false) const;
    std::string get_sign(std::string const &payload) const;
    std::string dispach_request(std::string const &http_method, std::string const &url, std::string const &payload) const;
    
private: // Private variables

    std::string _key;
    std::string _secret;
    std::string _base_url;
    int32_t _timeout;
    std::string _proxy;
    bool _show_limit_usage;
    bool _show_header;
    std::string _private_key;
    std::string _private_key_passphrase;
    HTTPClient _session;

private: // Parsing variables

    simdjson::ondemand::parser _parser;
};

//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
API::ResponseOrError<JsonResponseStructured> API::parse_json_value(simdjson::ondemand::value value) {
    
    auto obj = value.get_object();
    if (!obj.error()) {
        if (std::optional<ServerMessageResponse> res = read_server_message(obj.value_unsafe())) {
            return res.value();
        }
    }
    
    JsonResponseStructured response_struct;
    auto error = value.get(response_struct);
    std::cout << "Error: " << simdjson::error_message(error) << std::endl;
    DEBUG_ASSERT(!error);

    return response_struct;
}

//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
API::ResponseOrError<JsonResponseStructured> API::parse_response(std::string &response) {
    
    auto doc = get_parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

    return parse_json_value<JsonResponseStructured>(doc);
}

//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
API::ArrayErrorsResponse<JsonResponseStructured> API::parse_response(std::string &response, ArrayErrors const) {

    auto doc = get_parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

#ifndef NDEBUG
    simdjson_print_json_tree(doc);
    doc.rewind();
#endif

    auto obj = doc.get_object();
    if(!obj.error()) {
        std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());
        DEBUG_ASSERT(res.has_value());

        return res.value();
    }
    doc.rewind();

    simdjson::ondemand::array arr;
    auto error = doc.get_array().get(arr);
    DEBUG_ASSERT(!error);

    std::vector<ResponseOrError<JsonResponseStructured>> response_structs;
    for(simdjson::ondemand::value item : arr) {
        response_structs.push_back(
            parse_json_value<JsonResponseStructured>(item)
        );
    }
    
    return response_structs;
}

//------------------------------------------------------------------------------------

#endif // API_HPP

//------------------------------------------------------------------------------------
