
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

namespace simdjson {

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, std::string &v) {

    std::cout << "tag_invoke for std::string" << std::endl;

    std::string_view sv;
    if(auto error = val.get(sv)) return error;
    v = std::string(sv);

    return simdjson::SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, double &v) {

    std::cout << "tag_invoke for double" << std::endl;

    if(auto error = val.get_double(v)) return error;

    return simdjson::SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, uint64_t &v) {

    std::cout << "tag_invoke for uint64_t" << std::endl;

    if(auto error = val.get_uint64(v)) return error;

    return simdjson::SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, int64_t &v) {

    std::cout << "tag_invoke for int64_t" << std::endl;

    if(auto error = val.get_int64(v)) return error;

    return simdjson::SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, int32_t &v) {

    std::cout << "tag_invoke for int32_t" << std::endl;

    int64_t temp;
    if(auto error = val.get_int64().get(temp)) return error;
    v = static_cast<int32_t>(temp);

    return simdjson::SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, int8_t &v) {

    std::cout << "tag_invoke for int8_t" << std::endl;

    int64_t temp;
    if(auto error = val.get_int64().get(temp)) return error;
    v = static_cast<int8_t>(temp);

    return simdjson::SUCCESS;
}

template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, bool &v) {

    std::cout << "tag_invoke for bool" << std::endl;

    if(auto error = val.get_bool(v)) return error;

    return simdjson::SUCCESS;
}

template <typename simdjson_value, typename T>
auto tag_invoke(deserialize_tag, simdjson_value &val, std::vector<T> &vt) {

    std::cout << "tag_invoke for std::vector<T>" << std::endl;

    ondemand::array arr;
    if (auto error = val.get_array().get(arr)) return error;

    vt.reserve(arr.count_elements());
    for (auto obj : arr) {
        T t;
        if(auto t_error = obj.get(t)) return t_error;
        vt.emplace_back(t);
    }

    return simdjson::SUCCESS;
}

} // namespace simdjson

using namespace simdjson;

error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, std::string &value, bool const any_order = false);
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, double &value, bool const any_order = false);
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, uint64_t &value, bool const any_order = false);
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, int64_t &value, bool const any_order = false);
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, int32_t &value, bool const any_order = false);
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, int8_t &value, bool const any_order = false);
error_code simdjson_get_value_field_name(ondemand::object &obj, std::string_view const field_name, bool &value, bool const any_order = false);

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
