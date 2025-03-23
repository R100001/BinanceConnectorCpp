
#ifndef AUTHENTICATION_HPP
#define AUTHENTICATION_HPP

#include <string>

//------------------------------------------------------------------------------------

std::string hmac_hashing(std::string const &secret, std::string const &payload);
std::string rsa_signature(std::string const &private_key, std::string const &payload, std::string const &private_key_passphrase);

//------------------------------------------------------------------------------------

#endif // AUTHENTICATION_HPP
