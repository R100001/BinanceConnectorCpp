
#ifndef PORTFOLIO_MARGIN_ENDPOINTS_HPP
#define PORTFOLIO_MARGIN_ENDPOINTS_HPP

//------------------------------------------------------------------------------------

#include "derivatives_trading.hpp"
#include "error.hpp"

//------------------------------------------------------------------------------------

// Response Structs

struct ClassicPortfolioMarginAccountInformationObject {
    std::string max_withdrawal_amount_usd;
    std::string asset;
    std::string max_withdrawal_amount;
}
using ClassicPortfolioMarginAccountInformationResponse = API::ResponseOrError<ClassicPortfolioMarginAccountInformationObject>;

//-------------------------------------------------------------------------------------

#endif // PORTFOLIO_MARGIN_ENDPOINTS_HPP

//------------------------------------------------------------------------------------
