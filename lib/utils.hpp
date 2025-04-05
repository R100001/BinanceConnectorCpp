
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

error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, std::string &value, bool const any_order = false);

template <typename T>
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, T &value, bool const any_order = false) {
    
    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!any_order) field = obj.find_field(field_name);
    else field = obj[field_name];

    if (field.error()) {
        std::cout << simdjson::error_message(field.error()) << std::endl;
        return field.error();
    }
    
    if (auto error = field.get(value)) return error;

    if(any_order) obj.reset();

    return simdjson::SUCCESS;
}

template <typename T>
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, std::vector<T> &value, bool const any_order = false) {

    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!any_order) field = obj.find_field(field_name);
    else field = obj[field_name];

    if (field.error()) {
        std::cout << "Error: " << simdjson::error_message(field.error()) << std::endl;
        return field.error();
    }

    if (auto error = field.get(value)) return error;

    if(any_order) obj.reset();

    return simdjson::SUCCESS;

}

template <>
inline error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, std::vector<std::string> &vs, bool const any_order) {
    
    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!any_order) field = obj.find_field(field_name);
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

    if(any_order) obj.reset();

    return simdjson::SUCCESS;
}

void simdjson_print_json_tree(simdjson::ondemand::value element);

//--------------------------------------SIMDJSON--------------------------------------
//------------------------------------------------------------------------------------

#endif // UTILS_HPP

//------------------------------------------------------------------------------------
