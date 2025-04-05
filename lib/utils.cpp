
#include "utils.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstdint>

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

simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, std::string &value, bool const any_order) {
    
    simdjson::simdjson_result<simdjson::ondemand::value> field;
    if (!any_order) field = obj.find_field(field_name);
    else field = obj[field_name];

    if (field.error()) {
        std::cout << simdjson::error_message(field.error()) << std::endl;
        return field.error();
    }

    std::string_view sv;
    if (auto error = field.get(sv)) return error;
    value = std::string(sv);

    if(any_order) obj.reset();

    return simdjson::SUCCESS;
}

// simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, double &value, bool const any_order) {
    
//     simdjson::simdjson_result<simdjson::ondemand::value> field;
//     if (!any_order) field = obj.find_field(field_name);
//     else field = obj[field_name];

//     if (field.error()) {
//         std::cout << simdjson::error_message(field.error()) << std::endl;
//         return field.error();
//     }
    
//     if (auto error = field.get(value)) return error;

//     if(any_order) obj.reset();

//     return simdjson::SUCCESS;
// }

// simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, uint64_t &value, bool const any_order) {
    
//     simdjson::simdjson_result<simdjson::ondemand::value> field;
//     if (!any_order) field = obj.find_field(field_name);
//     else field = obj[field_name];

//     if (field.error()) {
//         std::cout << simdjson::error_message(field.error()) << std::endl;
//         return field.error();
//     }
    
//     if (auto error = field.get(value)) return error;

//     if(any_order) obj.reset();

//     return simdjson::SUCCESS;
// }

// simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, int64_t &value, bool const any_order) {
    
//     simdjson::simdjson_result<simdjson::ondemand::value> field;
//     if (!any_order) field = obj.find_field(field_name);
//     else field = obj[field_name];

//     if (field.error()) {
//         std::cout << simdjson::error_message(field.error()) << std::endl;
//         return field.error();
//     }
    
//     if (auto error = field.get(value)) return error;

//     if(any_order) obj.reset();

//     return simdjson::SUCCESS;
// }

// simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, int32_t &value, bool const any_order) {
    
//     simdjson::simdjson_result<simdjson::ondemand::value> field;
//     if (!any_order) field = obj.find_field(field_name);
//     else field = obj[field_name];

//     if (field.error()) {
//         std::cout << simdjson::error_message(field.error()) << std::endl;
//         return field.error();
//     }
    
//     if (auto error = field.get(value)) return error;

//     if(any_order) obj.reset();

//     return simdjson::SUCCESS;
// }

// simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, int16_t &value, bool const any_order) {
    
//     simdjson::simdjson_result<simdjson::ondemand::value> field;
//     if (!any_order) field = obj.find_field(field_name);
//     else field = obj[field_name];

//     if (field.error()) {
//         std::cout << simdjson::error_message(field.error()) << std::endl;
//         return field.error();
//     }
    
//     if (auto error = field.get(value)) return error;

//     if(any_order) obj.reset();

//     return simdjson::SUCCESS;
// }

// simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, int8_t &value, bool const any_order) {
    
//     simdjson::simdjson_result<simdjson::ondemand::value> field;
//     if (!any_order) field = obj.find_field(field_name);
//     else field = obj[field_name];

//     if (field.error()) {
//         std::cout << simdjson::error_message(field.error()) << std::endl;
//         return field.error();
//     }
    
//     if (auto error = field.get(value)) return error;

//     if(any_order) obj.reset();

//     return simdjson::SUCCESS;
// }

// simdjson::error_code simdjson_get_value_field_name(simdjson::ondemand::object &obj, std::string_view const field_name, bool &value, bool const any_order) {

//     simdjson::simdjson_result<simdjson::ondemand::value> field;
//     if (!any_order) field = obj.find_field(field_name);
//     else field = obj[field_name];

//     if (field.error()) {
//         std::cout << simdjson::error_message(field.error()) << std::endl;
//         return field.error();
//     }
    
//     if (auto error = field.get(value)) return error;

//     if(any_order) obj.reset();

//     return simdjson::SUCCESS;
// }

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
