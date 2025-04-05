
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

//------------------------------------------------------------------------------------

#endif // DERIVATIVES_TRADING_HPP

//------------------------------------------------------------------------------------
