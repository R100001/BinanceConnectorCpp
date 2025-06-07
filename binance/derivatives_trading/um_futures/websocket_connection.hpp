
//------------------------------------------------------------------------------------

#ifndef WEBSOCKET_CONNECTION_HPP
#define WEBSOCKET_CONNECTION_HPP

//------------------------------------------------------------------------------------

#include "api.hpp"
#include "error.hpp"

//------------------------------------------------------------------------------------

namespace WebsocketAPI {

//------------------------------------------------------------------------------------

void connect(API &api);
void disconnect(API &api);
void set_on_message_callback(API &api, API::MsgCallbackT callback);
void set_on_error_callback(API &api, API::ErrCallbackT callback);

//------------------------------------------------------------------------------------

} // namespace WebsocketAPI

//------------------------------------------------------------------------------------

namespace WebsocketUserDataStreams {

//------------------------------------------------------------------------------------

void subscribe(API &api, std::string const &stream_name);
void subscribe(API &api, std::vector<std::string> const &stream_names);
void unsubscribe(API &api, std::string const &stream_name);
void unsubscribe(API &api, std::vector<std::string> const &stream_names);
void set_on_message_callback(API &api, API::MsgCallbackT callback);
void set_on_error_callback(API &api, API::ErrCallbackT callback);

//------------------------------------------------------------------------------------

} // namespace WebsocketUserDataStreams

//------------------------------------------------------------------------------------

namespace WebsocketMarketStreams {

//------------------------------------------------------------------------------------

void start(API &api);
void stop(API &api);
void set_on_message_callback(API &api, API::MsgCallbackT callback);
void set_on_error_callback(API &api, API::ErrCallbackT callback);

//------------------------------------------------------------------------------------

} // namespace WebsocketMarketStreams

//------------------------------------------------------------------------------------

#endif // WEBSOCKET_CONNECTION_HPP

//------------------------------------------------------------------------------------
