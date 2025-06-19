
#ifndef AUTHENTICATION_HPP
#define AUTHENTICATION_HPP

#include <string>

//------------------------------------------------------------------------------------

std::string hmac_signature(std::string_view secret, std::string_view payload);
std::string ed25519_signature(std::string_view private_key, std::string_view payload, std::string_view private_key_passphrase);

//------------------------------------------------------------------------------------

#endif // AUTHENTICATION_HPP
