
//------------------------------------------------------------------------------------

#include "api.hpp"

#include <sstream>

#include "lib/utils.hpp"
#include "lib/authentication.hpp"

//------------------------------------------------------------------------------------

API::API(
    std::string const &base_url,
    std::string const &key,
    std::string const &secret,
    int32_t const timeout,
    std::string const &proxy,
    bool const show_limit_usage,
    bool const show_header,
    std::string const &private_key,
    std::string const &private_key_passphrase)
    : _key(key),
      _secret(secret),
      _base_url(base_url),
      _timeout(timeout),
      _proxy(proxy),
      _show_limit_usage(show_limit_usage),
      _show_header(show_header),
      _private_key(private_key),
      _private_key_passphrase(private_key_passphrase),
      _session(HTTPClient(key))
{
}

//------------------------------------------------------------------------------------

template<typename T>
inline static void append_number(char* buffer, size_t& pos, T value) 
{
    auto result = std::to_chars(buffer + pos, buffer + pos + 32, value);
    pos = result.ptr - buffer;
}

//------------------------------------------------------------------------------------

std::string API::prepare_query_string(API::Parameters const &params) const 
{
    constexpr size_t buffer_size = 4096;
    std::array<char, buffer_size> buffer;
    size_t pos = 0;

    for (const auto& [name, value] : params) {
        std::memcpy(buffer.data() + pos, name.data(), name.size());
        pos += name.size();
        buffer[pos++] = '=';

        switch (static_cast<ParameterTypeIndex>(value.index())) {
        case ParameterTypeIndex::BOOL:
            std::memcpy(buffer.data() + pos, std::get<bool>(value) ? "true" : "false", 4);
            pos += 4;
            break;
        case ParameterTypeIndex::INT8:
            append_number(buffer.data(), pos, std::get<int8_t>(value));
            break;
        case ParameterTypeIndex::INT16:
            append_number(buffer.data(), pos, std::get<int16_t>(value));
            break;
        case ParameterTypeIndex::INT32:
            append_number(buffer.data(), pos, std::get<int32_t>(value));
            break;
        case ParameterTypeIndex::INT64:
            append_number(buffer.data(), pos, std::get<int64_t>(value));
            break;
        case ParameterTypeIndex::UINT8:
            append_number(buffer.data(), pos, std::get<uint8_t>(value));
            break;
        case ParameterTypeIndex::UINT16:
            append_number(buffer.data(), pos, std::get<uint16_t>(value));
            break;
        case ParameterTypeIndex::UINT32:
            append_number(buffer.data(), pos, std::get<uint32_t>(value));
            break;
        case ParameterTypeIndex::UINT64:
            append_number(buffer.data(), pos, std::get<uint64_t>(value));
            break;
        case ParameterTypeIndex::DOUBLE:
            append_number(buffer.data(), pos, std::get<double>(value));
            break;
        case ParameterTypeIndex::STRING: {
            std::string_view str_value = std::get<std::string>(value);
            std::memcpy(buffer.data() + pos, str_value.data(), str_value.size());
            pos += str_value.size();
            break;
            }
        }
        buffer[pos++] = '&';
    }

    return std::string(buffer.data(), pos - 1); // -1 to remove the last '&'
}

//------------------------------------------------------------------------------------

std::string API::prepare_json_string(API::Parameters const &params) const
{
    constexpr size_t buffer_size = 4096;
    std::array<char, buffer_size> buffer;
    size_t pos = 0;

    buffer[pos++] = '{';

    for (const auto& [name, value] : params) {

        buffer[pos++] = '"';
        std::memcpy(buffer.data() + pos, name.data(), name.size());
        pos += name.size();
        buffer[pos++] = '"';
        buffer[pos++] = ':';

        switch (static_cast<ParameterTypeIndex>(value.index())) {
        case ParameterTypeIndex::BOOL:
            std::memcpy(buffer.data() + pos, std::get<bool>(value) ? "true" : "false", 4);
            pos += 4;
            break;
        case ParameterTypeIndex::INT8:
            append_number(buffer.data(), pos, std::get<int8_t>(value));
            break;
        case ParameterTypeIndex::INT16:
            append_number(buffer.data(), pos, std::get<int16_t>(value));
            break;
        case ParameterTypeIndex::INT32:
            append_number(buffer.data(), pos, std::get<int32_t>(value));
            break;
        case ParameterTypeIndex::INT64:
            append_number(buffer.data(), pos, std::get<int64_t>(value));
            break;
        case ParameterTypeIndex::UINT8:
            append_number(buffer.data(), pos, std::get<uint8_t>(value));
            break;
        case ParameterTypeIndex::UINT16:
            append_number(buffer.data(), pos, std::get<uint16_t>(value));
            break;
        case ParameterTypeIndex::UINT32:
            append_number(buffer.data(), pos, std::get<uint32_t>(value));
            break;
        case ParameterTypeIndex::UINT64:
            append_number(buffer.data(), pos, std::get<uint64_t>(value));
            break;
        case ParameterTypeIndex::DOUBLE:
            append_number(buffer.data(), pos, std::get<double>(value));
            break;
        case ParameterTypeIndex::STRING: {
            buffer[pos++] = '"';
            std::string_view str_value = std::get<std::string>(value);
            std::memcpy(buffer.data() + pos, str_value.data(), str_value.size());
            pos += str_value.size();
            buffer[pos++] = '"';
            break;
            }
        }

        buffer[pos++] = ',';
    }

    if(pos > 1) buffer[pos - 1] = '}';

    return std::string(buffer.data(), pos);
}

//------------------------------------------------------------------------------------

std::string API::sign_message(std::string const &message) const
{
    if(this->_private_key.empty()) {
        return hmac_hashing(this->_secret, message);
    } else {
        return rsa_signature(this->_private_key, message, this->_private_key_passphrase);
    }
}

//------------------------------------------------------------------------------------

std::optional<API::ServerMessageResponse> API::read_server_message(simdjson::ondemand::object &obj) {

    auto iterator = obj.begin();
    if (iterator != obj.end() && (*iterator).key() == "code") {
        
        ServerMessage server_error;
        auto code = (*iterator).value().get_int64();
        DEBUG_ASSERT(!code.error());
        server_error.code = static_cast<int>(code.value_unsafe());
        
        ++iterator;
        DEBUG_ASSERT(iterator != obj.end());
        DEBUG_ASSERT((*iterator).key() == "msg");

        std::string_view msg;
        auto error = (*iterator).value().get_string().get(msg);
        DEBUG_ASSERT(!error);
        server_error.msg = std::string(msg);

        return server_error;
    }

    return std::nullopt;
}

//------------------------------------------------------------------------------------

API::ServerMessageResponse API::parse_response(std::string &response, ResponseIsServerMessage const) {
   
    auto doc = parser().iterate(response);
    DEBUG_ASSERT(!doc.error());

#ifndef NDEBUG
    simdjson_print_json_tree(doc);
    doc.rewind();
#endif

    auto obj = doc.get_object();
    DEBUG_ASSERT(!obj.error());

    std::optional<ServerMessageResponse> const res = read_server_message(obj.value_unsafe());
    DEBUG_ASSERT(res.has_value());

    return res.value();
}

//------------------------------------------------------------------------------------
