
#ifndef DERIVATIVES_TRADING_HPP
#define DERIVATIVES_TRADING_HPP

//------------------------------------------------------------------------------------

#include "api.hpp"
#include "lib/utils.hpp"

//------------------------------------------------------------------------------------

class DerivativesTrading : public API {

public: // Constructors

    DerivativesTrading(
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

};

template <typename JsonResponseStructured>
std::variant<JsonResponseStructured, ServerError> parse_api_response(simdjson::ondemand::parser &parser, std::string &json_response_str) {

    auto doc = parser.iterate(json_response_str);
    DEBUG_ASSERT(!doc.error());

#ifndef NDEBUG
    simdjson_print_json_tree(doc);
    doc.rewind();
#endif

    auto obj = doc.get_object();
    if(!obj.error()) {

        auto code_field = obj.find_field("code");
        if (code_field.error() == simdjson::SUCCESS) {
            
            ServerError server_error;
            auto code = code_field.get_int64();
            DEBUG_ASSERT(!code.error());
            
            server_error.code = static_cast<int>(code.value_unsafe());

            auto error = simdjson_get_value_field_name(obj.value_unsafe(), "msg", server_error.msg);
            DEBUG_ASSERT(!error);

            return server_error;
        }
    }

    doc.rewind();
    
    JsonResponseStructured response;
    auto error = doc.get(response);
    std::cout << "Error: " << simdjson::error_message(error) << std::endl;
    DEBUG_ASSERT(!error);
    
    return response;
}

//------------------------------------------------------------------------------------

#endif // DERIVATIVES_TRADING_HPP

//------------------------------------------------------------------------------------
