
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

//------------------------------------------------------------------------------------

class API {

public: // Typedefs

    using Parameter = std::variant<bool, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, double, std::string>;
    using Parameters = std::vector<std::pair<std::string, Parameter>>;
    using APIResponse = std::variant<simdjson::ondemand::object, ServerError>;

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

public: // Public methods

    std::string query(std::string const &url, Parameters const &payload = {});
    std::string limit_request(std::string const &http_method, std::string const &url, Parameters const &payload);
    std::string sign_request(std::string const &http_method, std::string const &url, Parameters &payload, bool const special = false);
    std::string limited_encoded_sign_request(std::string const &http_method, std::string &url, Parameters &payload);
    std::string send_request(std::string const &http_method, std::string const &url, Parameters const &payload = {}, bool const special = false);

    simdjson::ondemand::parser &get_parser() { return this->_parser; }

private: // Private methods

    std::string prepare_params(Parameters const &params, bool const special = false) const;
    std::string get_sign(std::string const &payload) const;
    std::string dispach_request(std::string const &http_method, std::string const &url, std::string const &payload) const;
    API::APIResponse handle_exception(std::string &response);
    Parameters handle_response(std::string const &response) const;    

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

#endif // API_HPP

//------------------------------------------------------------------------------------
