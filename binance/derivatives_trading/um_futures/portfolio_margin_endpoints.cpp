
#include "portfolio_margin_endpoints.hpp"
#include "portfolio_margin_endpoints_parsing_simdjson.hpp"

#include "api.hpp"

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
