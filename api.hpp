
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

    enum class RequestType {
        GET,
        POST,
        PUT,
        DELETE
    };

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

    template <RequestType req_type> std::string sign_request(std::string const &url, Parameters &payload);
    template <RequestType req_type> std::string send_request(std::string const &url, Parameters const &payload = {});
    

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

    static std::optional<ServerMessageResponse> read_server_message(simdjson::ondemand::object &obj);

private:
    simdjson::ondemand::parser &parser() { return this->_parser; }

private: // Private methods

    std::string prepare_params(Parameters const &params) const;
    std::string sign_message(std::string const &message) const;
    template<RequestType req_type> std::string dispach_request(std::string_view const url, std::string_view const endpoint, std::string const &payload) const;
    
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
API::ResponseOrError<JsonResponseStructured> API::parse_response(std::string &response) {
    
    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

    auto obj = doc.get_object();
    if (!obj.error()) {
        std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());

        if(res.has_value()) return res.value();
    }

    doc.rewind();
    
    JsonResponseStructured response_struct;
    auto error = doc.get(response_struct);
    std::cout << "Error: " << simdjson::error_message(error) << std::endl;
    DEBUG_ASSERT(!error);

    return response_struct;
}

//------------------------------------------------------------------------------------

template <typename JsonResponseStructured>
API::ArrayErrorsResponse<JsonResponseStructured> API::parse_response(std::string &response, ArrayErrors const) {

    auto doc = parser().iterate(response);
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
        response_structs.emplace_back();
        auto error = item.get(response_structs.back());
        DEBUG_ASSERT(!error);
    }
    
    return response_structs;
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::sign_request(std::string const &url, Parameters &payload)
{
    payload.emplace_back(std::make_pair("timestamp", std::to_string(get_timestamp())));
    payload.emplace_back(std::make_pair("signature", this->sign_message(this->prepare_params(payload))));
    return this->send_request<req_type>(url, payload);
}

//------------------------------------------------------------------------------------

template <API::RequestType req_type>
std::string API::send_request(std::string const &endpoint, Parameters const &payload)
{
    std::string response = this->dispach_request<req_type>(this->_base_url, endpoint, this->prepare_params(payload));
    
    return response;
}

//------------------------------------------------------------------------------------

template<API::RequestType req_type>
std::string API::dispach_request(std::string_view const url, std::string_view const endpoint, std::string const &payload) const
{
    std::string const &request = payload.empty() ? std::string(endpoint) : std::string(endpoint) + "?" + payload;

    switch(req_type) {
        case API::RequestType::GET:
            return this->_session.get(url, request, this->_timeout, this->_proxy);
        case API::RequestType::POST:
            return this->_session.post(url, request, this->_timeout, this->_proxy);
        case API::RequestType::PUT:
            return this->_session.put(url, request, this->_timeout, this->_proxy);
        case API::RequestType::DELETE:
            return this->_session.del(url, request, this->_timeout, this->_proxy);
        default:
            throw std::runtime_error("Unsupported HTTP method!");
    }
}

//------------------------------------------------------------------------------------

#endif // API_HPP

//------------------------------------------------------------------------------------
