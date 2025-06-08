
//------------------------------------------------------------------------------------

#ifndef API_DECLARATIONS_HPP
#define API_DECLARATIONS_HPP

//------------------------------------------------------------------------------------

#include <string>
#include <vector>
#include <variant>

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//---------------------------------------ERRORS---------------------------------------

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
//------------------------------------------------------------------------------------
//-----------------------------------ResponseTypes------------------------------------

template <typename JsonResponseStructured> 
using ResponseOrError = std::variant<JsonResponseStructured, ServerMessage>;
template <typename JsonResponseStructured>
using ArrayErrorsResponse = ResponseOrError<std::vector<ResponseOrError<JsonResponseStructured>>>;
using ServerMessageResponse = ServerMessage;

//------------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------------
