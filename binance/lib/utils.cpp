
#include "utils.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstdint>
#include <functional>

//------------------------------------------------------------------------------------

template<typename T, uint64_t MaxSize>
class RandomAccessQueue {

private: // Typedefs

    using QueueT = std::array<T, MaxSize>;
    using IndexT = uint32_t;

    struct QueueElement {
        T elem;
        IndexT next;
        IndexT prev;
    };

public: // Constructors and destructors

    RandomAccessQueue() : _first_free(0), _last_free(MaxSize - 1) {
        _queue[0].next = 1;
        _queue[0].prev = MaxSize - 1;
        for (IndexT i = 1; i < MaxSize - 1; ++i) {
            _queue[i].next = i + 1;
            _queue[i].prev = i - 1;
        }
        _queue[MaxSize - 1].next = 0;
        _queue[MaxSize - 1].prev = MaxSize - 2;
    }

    IndexT push(T const& elem) {

        if(_first_free == _last_free) {
            _last_free = MaxSize;
        }

        _queue[_first_free].elem = elem;
        
        IndexT next_free = _queue[_first_free].next;
        _queue[next_free].prev = _first_free;
        _first_free = _queue[_first_free].next;
        
        return next_free;
    }

    void pop(IndexT index) {
           
    }
        

private: // Members
    QueueT _queue;
    IndexT _first_free;
    IndexT _last_free;
};

//------------------------------------------------------------------------------------

template<uint64_t MaxMessages = 1 << 20, uint64_t MaxId = 1 << 10>
class ResponseHandler {

private: // Typedefs

    using ResponseFunc = std::function<void(std::string_view)>;
    using ResponseIdT = uint64_t;

    struct ResponseListFirstLast {
        ResponseIdT first;
        ResponseIdT last;
    };

    struct ResponseForwardList {
        std::string message;
        ResponseIdT next;
    };

    struct FunctionsForwardList {
        ResponseFunc func;
        ResponseIdT next;
    };

    using ResponseIdFirstLast = ResponseListFirstLast;  

public: // Constructors and destructors
    ResponseHandler() : _next_free_index{0, MaxMessages - 1}, _next_free_id{0, MaxId - 1} {
        
        for(ResponseIdT i = 0; i < MaxMessages - 1; ++i) {
            _response_list[i].next = i + 1;
        }
        _response_list[MaxMessages - 1].next = 0;
        
        std::fill(_response_id_first_last.begin(), _response_id_first_last.end(), ResponseListFirstLast{-1, -1});
        
        std::fill(_response_funcs.begin(), _response_funcs.end(), nullptr);
    }

    ~ResponseHandler() = default;
    ResponseHandler(ResponseHandler const&) = delete;
    ResponseHandler& operator=(ResponseHandler const&) = delete;
    ResponseHandler(ResponseHandler&&) = delete;
    ResponseHandler& operator=(ResponseHandler&&) = delete;

public: // Operations

    ResponseIdT add_handler(ResponseFunc func) {
        ResponseIdT id = _next_free_id.first;
        return id;
    }


private:
    std::array<ResponseForwardList, MaxMessages> _response_list;          // Response list with next index
    ResponseListFirstLast                        _next_free_index;        // Pointers to next free response

    std::array<ResponseListFirstLast, MaxId>     _response_id_first_last; // Pointers to different response types
    std::array<FunctionsForwardList, MaxId>      _response_funcs;         // Functions for each response type
    ResponseIdFirstLast                          _next_free_id;           // Pointers to next free response id
};

//------------------------------------------------------------------------------------

template<typename T>
inline static void append_number(char* buffer, size_t& pos, T value) 
{
    auto result = std::to_chars(buffer + pos, buffer + pos + 32, value);
    pos = result.ptr - buffer;
}

//------------------------------------------------------------------------------------

std::string prepare_query_string(Parameters const &params) 
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
        case ParameterTypeIndex::VECTOR_STRING: {
            const auto &vec_value = std::get<std::vector<std::string>>(value);
            buffer[pos++] = '[';
            for (const auto& str : vec_value) {
                std::memcpy(buffer.data() + pos, str.data(), str.size());
                pos += str.size();
                buffer[pos++] = ',';
            }
            if (!vec_value.empty()) --pos;
            buffer[pos++] = ']';
            break;
            }
        }
        buffer[pos++] = '&';
    }
    
    if(!pos) return {};
    
    return std::string(buffer.data(), pos - 1); // -1 to remove the last '&'
}

//------------------------------------------------------------------------------------

std::string prepare_json_string(Parameters const &params, bool const no_quotes_in_params)
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
            if(!no_quotes_in_params || name != "params") buffer[pos++] = '"';
            std::string_view str_value = std::get<std::string>(value);
            std::memcpy(buffer.data() + pos, str_value.data(), str_value.size());
            pos += str_value.size();
            if(!no_quotes_in_params || name != "params") buffer[pos++] = '"';
            break;
            }
        case ParameterTypeIndex::VECTOR_STRING: {
            const auto &vec_value = std::get<std::vector<std::string>>(value);
            buffer[pos++] = '[';
            for (const auto& str : vec_value) {
                buffer[pos++] = '"';
                std::memcpy(buffer.data() + pos, str.data(), str.size());
                pos += str.size();
                buffer[pos++] = '"';
                buffer[pos++] = ',';
            }
            if (!vec_value.empty()) --pos;
            buffer[pos++] = ']';
            break;
            }
        }

        buffer[pos++] = ',';
    }

    if(pos > 1) buffer[pos - 1] = '}';

    return std::string(buffer.data(), pos);
}

//------------------------------------------------------------------------------------

bool check_required_parameter(std::string const &parameter, std::string_view const name)
{
    if (parameter.empty()) {
        std::cout << "Parameter " << name << " is required but is empty\n";
    }
    return !parameter.empty();
}

//------------------------------------------------------------------------------------

int64_t get_timestamp() 
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

//------------------------------------------------------------------------------------
//--------------------------------------SIMDJSON--------------------------------------

void simdjson_print_json_tree(simdjson::ondemand::value element) {
    bool add_comma;
    switch (element.type()) {
    case ondemand::json_type::array:
    {
        std::cout << "[";
        add_comma = false;
        int i = 0;
        for (auto child : element.get_array()) {
            if (add_comma) {
                std::cout << ",";
            }
            // We need the call to value() to get
            // an ondemand::value type.
            simdjson_print_json_tree(child.value());
            add_comma = true;
            if(i++ > 10) {
                std::cout << "...";
                break;
            }
        }
        std::cout << "]";
        break;
    }
    case ondemand::json_type::object:
        std::cout << "{";
        add_comma = false;
        for (auto field : element.get_object()) {
            if (add_comma) {
                std::cout << ",";
            }
            // key() returns the key as it appears in the raw
            // JSON document, if we want the unescaped key,
            // we should do field.unescaped_key().
            // We could also use field.escaped_key() if we want
            // a std::string_view instance, but we do not need
            // escaping.
            std::cout << "\"" << field.key() << "\": ";
            simdjson_print_json_tree(field.value());
            add_comma = true;
        }
        std::cout << "}\n";
        break;
    case ondemand::json_type::number:
        // assume it fits in a double
        std::cout << "Number: " << element.get_double();
        break;
    case ondemand::json_type::string:
        // get_string() would return escaped string, but
        // we are happy with unescaped string.
        std::cout << "String: " << element.get_string();
        break;
    case ondemand::json_type::boolean:
        std::cout << "Boolean: " << (element.get_bool() ? "true" : "false");
        break;
    case ondemand::json_type::null:
        // We check that the value is indeed null
        // otherwise: an error is thrown.
        if (element.is_null()) {
            std::cout << "null";
        }
        break;
    }
}

//--------------------------------------SIMDJSON--------------------------------------
//------------------------------------------------------------------------------------
