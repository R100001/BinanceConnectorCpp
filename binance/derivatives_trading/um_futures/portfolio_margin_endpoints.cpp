
#include "portfolio_margin_endpoints.hpp"

#include "lib/utils.hpp"
#include "api.hpp"

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

//------------------------------------------------------------------------------------

ClassicPortfolioMarginAccountInformationResponse API::classic_portfolio_margin_account_information(std::string const &asset, int32_t const recv_window) {
    std::string const url = "/fapi/v1/pmAccountInfo";

    Parameters params;
    params.emplace_back("asset", asset);
    if (recv_window != -1) params.emplace_back("recvWindow", recv_window);

    std::string response = sign_request<RequestType::GET>(url, params);

    return parse_response<ClassicPortfolioMarginAccountInformationObject>(response);
}

//------------------------------------------------------------------------------------
