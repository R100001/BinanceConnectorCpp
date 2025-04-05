
#ifndef ERROR_HPP
#define ERROR_HPP

//------------------------------------------------------------------------------------

#include <exception>
#include <string>
#include <vector>
#include <ostream>

//------------------------------------------------------------------------------------

struct ClientError {
    int status_code;
    int error_code;
    std::string error_message;
    std::string header;
};

//------------------------------------------------------------------------------------

struct ServerMessage {
    int16_t code;
    std::string msg;
};

//------------------------------------------------------------------------------------

struct ParametersRequiredError {
    std::vector<std::string> params;
};

//------------------------------------------------------------------------------------

#endif // ERROR_HPP

//------------------------------------------------------------------------------------
