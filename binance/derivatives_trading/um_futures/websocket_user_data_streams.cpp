
//------------------------------------------------------------------------------------

#include "websocket_user_data_streams.hpp"
#include "websocket_user_data_streams_parsing_simdjson.hpp"

#include "api.hpp"

//------------------------------------------------------------------------------------
//-----------------------Handle Websocket User Data Stream Event----------------------
//------------------------------------------------------------------------------------

static API::UserDataStreamEventTypes ws_user_data_streams_detect_event_type(simdjson::ondemand::value val) {

    simdjson::ondemand::object obj;
    {auto error = val.get_object().get(obj); DEBUG_ASSERT(!error);}

    std::string_view event_type;
    {auto error = obj.find_field("e").get_string().get(event_type); DEBUG_ASSERT(!error);}

    if (event_type == "listenKeyExpired") {
        return API::UserDataStreamEventTypes::LISTEN_KEY_EXPIRED;
    }
    else if (event_type == "ACCOUNT_UPDATE") {
        return API::UserDataStreamEventTypes::ACCOUNT_UPDATE;
    }
    else if (event_type == "MARGIN_CALL") {
        return API::UserDataStreamEventTypes::MARGIN_CALL;
    }
    else if (event_type == "ORDER_TRADE_UPDATE") {
        return API::UserDataStreamEventTypes::ORDER_TRADE_UPDATE;
    }
    else if (event_type == "TRADE_LITE") {
        return API::UserDataStreamEventTypes::TRADE_LITE;
    }
    else if (event_type == "ACCOUNT_CONFIG_UPDATE") {
        return API::UserDataStreamEventTypes::ACCOUNT_CONFIG_UPDATE;
    }
    else if (event_type == "STRATEGY_UPDATE") {
        return API::UserDataStreamEventTypes::STRATEGY_UPDATE;
    }
    else if (event_type == "GRID_UPDATE") {
        return API::UserDataStreamEventTypes::GRID_UPDATE;
    }
    else if (event_type == "CONDITIONAL_ORDER_TRIGGER_REJECT") {
        return API::UserDataStreamEventTypes::CONDITIONAL_ORDER_TRIGGER_REJECT;
    }

    DEBUG_ASSERT(false && "Unknown User Data Stream Event Type");
    return {};
}

//------------------------------------------------------------------------------------

API::UserDataStreamResponse API::ws_user_data_streams_parse_response(std::string &response) {

    simdjson::ondemand::document doc;
    {auto error = _parser.iterate(response).get(doc); DEBUG_ASSERT(!error);}

    UserDataStreamEventTypes const event_type = ws_user_data_streams_detect_event_type(doc);
    doc.rewind();

    switch (event_type) {
    case UserDataStreamEventTypes::LISTEN_KEY_EXPIRED: 
    {
        WebsocketUserDataStreams::ListenKeyExpiredStreamObject listen_key_expired;
        {auto error = doc.get(listen_key_expired); DEBUG_ASSERT(!error);}
        return listen_key_expired;
    }
    case UserDataStreamEventTypes::ACCOUNT_UPDATE: 
    {
        WebsocketUserDataStreams::AccountUpdateStreamObject account_update;
        {auto error = doc.get(account_update); DEBUG_ASSERT(!error);}
        return account_update;
    }
    case UserDataStreamEventTypes::MARGIN_CALL: 
    {
        WebsocketUserDataStreams::MarginCallStreamObject margin_call;
        {auto error = doc.get(margin_call); DEBUG_ASSERT(!error);}
        return margin_call;
    }
    case UserDataStreamEventTypes::ORDER_TRADE_UPDATE: 
    {
        WebsocketUserDataStreams::OrderTradeUpdateStreamObject order_trade_update;
        {auto error = doc.get(order_trade_update); DEBUG_ASSERT(!error);}
        return order_trade_update;
    }
    case UserDataStreamEventTypes::TRADE_LITE:
    {
        WebsocketUserDataStreams::TradeLiteStreamObject trade_lite;
        {auto error = doc.get(trade_lite); DEBUG_ASSERT(!error);}
        return trade_lite;
    }
    case UserDataStreamEventTypes::ACCOUNT_CONFIG_UPDATE: 
    {
        WebsocketUserDataStreams::AccountConfigUpdateStreamObject account_config_update;
        {auto error = doc.get(account_config_update); DEBUG_ASSERT(!error);}
        return account_config_update;
    }
    case UserDataStreamEventTypes::STRATEGY_UPDATE:
    {
        WebsocketUserDataStreams::StrategyUpdateStreamObject strategy_update;
        {auto error = doc.get(strategy_update); DEBUG_ASSERT(!error);}
        return strategy_update;
    }
    case UserDataStreamEventTypes::GRID_UPDATE:
    {
        WebsocketUserDataStreams::GridUpdateStreamObject grid_update;
        {auto error = doc.get(grid_update); DEBUG_ASSERT(!error);}
        return grid_update;
    }
    case UserDataStreamEventTypes::CONDITIONAL_ORDER_TRIGGER_REJECT:
    {
        WebsocketUserDataStreams::ConditionalOrderTriggerRejectStreamObject conditional_order_trigger_reject;
        {auto error = doc.get(conditional_order_trigger_reject); DEBUG_ASSERT(!error);}
        return conditional_order_trigger_reject;
    }
    default:
        DEBUG_ASSERT(false && "Unknown User Data Stream Event Type");
    }
    return {};
}

//------------------------------------------------------------------------------------
//------------------------WebSocket User Data Streams Handling------------------------
//------------------------------------------------------------------------------------

void API::ws_user_data_streams_connect() {
    _websocket_user_data_streams->connect();
}

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_disconnect() {
    _websocket_user_data_streams->disconnect();
}

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_message_callback(MsgCallbackT callback) {
    _websocket_user_data_streams->set_on_message_callback(std::move(callback));
}

//------------------------------------------------------------------------------------

void API::ws_user_data_streams_error_callback(ErrCallbackT callback) {
    _websocket_user_data_streams->set_on_error_callback(std::move(callback));
}

//------------------------------------------------------------------------------------
