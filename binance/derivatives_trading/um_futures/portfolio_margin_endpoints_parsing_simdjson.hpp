
//-----------------------------------------------------------------------------

#ifndef PORTFOLIO_MARGIN_ENDPOINTS_PARSING_SIMDJSON_HPP
#define PORTFOLIO_MARGIN_ENDPOINTS_PARSING_SIMDJSON_HPP

//-----------------------------------------------------------------------------

#include "portfolio_margin_endpoints.hpp"
#include "utils.hpp"

//------------------------------------------------------------------------------------

namespace simdjson {
    
using namespace PortfolioMarginEndpoints;

// ---------- Classic Portfolio Margin Account Information ----------
template <typename simdjson_value>
auto tag_invoke(deserialize_tag, simdjson_value &val, ClassicPortfolioMarginAccountInformationObject &response) {
    
    ondemand::object obj;
    if (auto error = val.get_object().get(obj)) return error;

    if (auto error = simdjson_get_value_field_name(obj, "maxWithdrawalAmountUSD", response.max_withdrawal_amount_usd)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "asset", response.asset)) return error;
    if (auto error = simdjson_get_value_field_name(obj, "maxWithdrawalAmount", response.max_withdrawal_amount)) return error;

    return SUCCESS;
}
// ------------------------------------------------------------------

} // namespace simdjson

//-----------------------------------------------------------------------------

#endif // PORTFOLIO_MARGIN_ENDPOINTS_PARSING_SIMDJSON_HPP
