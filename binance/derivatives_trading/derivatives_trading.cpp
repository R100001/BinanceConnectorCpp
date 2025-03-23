
#include "derivatives_trading.hpp"

//------------------------------------------------------------------------------------

DerivativesTrading::DerivativesTrading(
    std::string const &base_url,
    std::string const &key,
    std::string const &secret,
    int32_t const timeout,
    std::string const &proxy,
    bool const show_limit_usage,
    bool const show_header,
    std::string const &private_key,
    std::string const &private_key_passphrase)
    : API(base_url, key, secret, timeout, proxy, show_limit_usage, show_header, private_key, private_key_passphrase)
{
}

//------------------------------------------------------------------------------------
