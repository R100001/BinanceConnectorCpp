
#ifndef PORTFOLIO_MARGIN_ENDPOINTS_HPP
#define PORTFOLIO_MARGIN_ENDPOINTS_HPP

//------------------------------------------------------------------------------------

#include "api_declarations.hpp"

//------------------------------------------------------------------------------------

namespace PortfolioMarginEndpoints {

//------------------------------------------------------------------------------------

// Response Structs

struct ClassicPortfolioMarginAccountInformationObject {
    std::string max_withdrawal_amount_usd;
    std::string asset;
    std::string max_withdrawal_amount;
};
using ClassicPortfolioMarginAccountInformationResponse = ResponseOrError<ClassicPortfolioMarginAccountInformationObject>;

//-------------------------------------------------------------------------------------

} // namespace PortfolioMarginEndpoints

//------------------------------------------------------------------------------------

#endif // PORTFOLIO_MARGIN_ENDPOINTS_HPP

//------------------------------------------------------------------------------------
