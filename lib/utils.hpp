
#ifndef UTILS_HPP
#define UTILS_HPP

//------------------------------------------------------------------------------------

#include <string>

#include "simdjson.h"

//------------------------------------------------------------------------------------

#ifndef NDEBUG
#define DEBUG_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
            assert(false); \
        } \
    } while (0)
#else
#define DEBUG_ASSERT(condition) ((void)0)
#endif

bool check_required_parameter(std::string const &parameter, std::string_view const name);

int64_t get_timestamp();

//------------------------------------------------------------------------------------
//--------------------------------------SIMDJSON--------------------------------------

using namespace simdjson;

template <bool unordered_search = false>
error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, std::string &value) {
    
    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!unordered_search) field = obj.find_field(field_name);
    else field = obj[field_name];

    if (field.error()) {
        std::cout << simdjson::error_message(field.error()) << std::endl;
        return field.error();
    }

    std::string_view sv;
    if (auto error = field.get(sv)) return error;
    value = std::string(sv);

    if(unordered_search) obj.reset();

    return simdjson::SUCCESS;
}

template <typename T, bool unordered_search = false>
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, T &value) {
    
    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!unordered_search) field = obj.find_field(field_name);
    else field = obj[field_name];

    if (field.error()) {
        std::cout << simdjson::error_message(field.error()) << std::endl;
        return field.error();
    }
    
    if (auto error = field.get(value)) return error;

    if(unordered_search) obj.reset();

    return simdjson::SUCCESS;
}

template <typename T, bool unordered_search = false>
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, std::vector<T> &value) {

    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!unordered_search) field = obj.find_field(field_name);
    else field = obj[field_name];

    if (field.error()) {
        std::cout << "Error: " << simdjson::error_message(field.error()) << std::endl;
        return field.error();
    }

    if (auto error = field.get(value)) return error;

    if(unordered_search) obj.reset();

    return simdjson::SUCCESS;

}

template <bool unordered_search = false>
inline error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, std::vector<std::string> &vs) {
    
    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!unordered_search) field = obj.find_field(field_name);
    else field = obj[field_name];

    if (field.error()) {
        std::cout << simdjson::error_message(field.error()) << std::endl;
        return field.error();
    }

    ondemand::array arr;
    if (auto error = field.get_array().get(arr)) return error;

    vs.reserve(arr.count_elements());
    for (auto obj : arr) {
        std::string_view sv;
        if(auto t_error = obj.get(sv)) return t_error;
        vs.emplace_back(sv);
    }

    if(unordered_search) obj.reset();

    return simdjson::SUCCESS;
}

void simdjson_print_json_tree(simdjson::ondemand::value element);

//--------------------------------------SIMDJSON--------------------------------------
//------------------------------------------------------------------------------------

#endif // UTILS_HPP

//------------------------------------------------------------------------------------
