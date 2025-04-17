
#ifndef PORTFOLIO_MARGIN_ENDPOINTS_HPP
#define PORTFOLIO_MARGIN_ENDPOINTS_HPP

//------------------------------------------------------------------------------------

#include "derivatives_trading.hpp"
#include "error.hpp"

//------------------------------------------------------------------------------------

namespace PortfolioMarginEndpoints {

//------------------------------------------------------------------------------------

// Response Structs

struct ClassicPortfolioMarginAccountInformationObject {
    std::string max_withdrawal_amount_usd;
    std::string asset;
    std::string max_withdrawal_amount;
};
using ClassicPortfolioMarginAccountInformationResponse = API::ResponseOrError<ClassicPortfolioMarginAccountInformationObject>;

//------------------------------------------------------------------------------------

// REST API Endpoints

namespace RestAPI {

ClassicPortfolioMarginAccountInformationResponse classic_portfolio_margin_account_information(DerivativesTrading &api, std::string const &asset, int32_t const recv_window = -1);

} // namespace RestAPI


//-------------------------------------------------------------------------------------

} // namespace PortfolioMarginEndpoints

//------------------------------------------------------------------------------------

#endif // PORTFOLIO_MARGIN_ENDPOINTS_HPP

//------------------------------------------------------------------------------------
