
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

std::string API::query(std::string const &url, Parameters const &payload)
{
    return this->send_request("GET", url, payload);
}

//------------------------------------------------------------------------------------

std::string API::limit_request(std::string const &http_method, std::string const &url, Parameters const &payload)
{
    check_required_parameter(this->_key, "apiKey");
    return this->send_request(http_method, url, payload);
}

//------------------------------------------------------------------------------------

std::string API::sign_request(std::string const &http_method, std::string const &url, Parameters &payload, bool const special)
{
    payload.emplace_back(std::make_pair("timestamp", std::to_string(get_timestamp())));
    payload.emplace_back(std::make_pair("signature", this->get_sign(this->prepare_params(payload, special))));
    return this->send_request(http_method, url, payload, special);
}

//------------------------------------------------------------------------------------

std::string API::limited_encoded_sign_request(std::string const &http_method, std::string &url, Parameters &payload)
{
    payload.emplace_back(std::make_pair("timestamp", std::to_string(get_timestamp()))); 
    std::string params = this->prepare_params(payload);
    url += "?" + params + "&signature=" + this->get_sign(params);
    return this->send_request(http_method, url);
}

//------------------------------------------------------------------------------------

std::string API::send_request(std::string const &http_method, std::string const &url, Parameters const &payload, bool const special)
{
    std::string const full_url = this->_base_url + url;

    std::string response = this->dispach_request(http_method, full_url, this->prepare_params(payload, special));
    
    return response;
}

//------------------------------------------------------------------------------------

std::string API::prepare_params(Parameters const &params, bool const special) const
{
    std::stringstream ss;
    for(auto const &[name, value] : params) {
        ss << name << "=";
        std::visit([&ss](auto const &v) {
            ss << v;
        }, value);
        ss << "&";
    }

    std::string params_str = ss.str();
    if (!params_str.empty()) {
        params_str.pop_back();
    }

    return params_str;
}

//------------------------------------------------------------------------------------

std::string API::get_sign(std::string const &payload) const
{
    if(this->_private_key.empty()) {
        return hmac_hashing(this->_secret, payload);
    } else {
        return rsa_signature(this->_private_key, payload, this->_private_key_passphrase);
    }
}

//------------------------------------------------------------------------------------

std::string API::dispach_request(std::string const &http_method, std::string const &url, std::string const &payload) const
{
    if(http_method == "GET") {
        return this->_session.get(url + "?" + payload, this->_timeout, this->_proxy);
    } else if(http_method == "POST") {
        return this->_session.post(url + "?" + payload, this->_timeout, this->_proxy);
    } else if(http_method == "PUT") {
        return this->_session.put(url + "?" + payload, this->_timeout, this->_proxy);
    } else if(http_method == "DELETE") {
        return this->_session.del(url + "?" + payload, this->_timeout, this->_proxy);
    } else {
        throw std::runtime_error("Unsupported HTTP method: " + http_method);
    }
}

//------------------------------------------------------------------------------------

std::optional<API::ServerMessageResponse> API::read_server_message(simdjson::ondemand::object &obj) const {

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
   
    auto doc = get_parser().iterate(response);
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
