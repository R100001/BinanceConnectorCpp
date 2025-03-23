#include <iostream>
#include <string>

#include "simdjson.h"

#include "lib/authentication.hpp"
#include "api.hpp"

#include "market_data.hpp"

int main() {


    std::cout << "Testing BinanceConnectorCpp\n";
    // std::cout << hmac_hashing("secret", "test") << "\n";
    // std::cout << rsa_signature("-----BEGIN RSA PRIVATE KEY-----\nMIIBOgIBAAJBAKj34GkxFhD90vcNLYLInFEX6Ppy1tPf9Cnzj4p4WGeKLs1Pt8QuKUpRKfFLfRYC9AIKjbJTWit+CqvjWYzvQwECAwEAAQJAIJLixBy2qpFoS4DSmoEmo3qGy0t6z09AIJtH+5OeRV1be+N4cDYJKffGzDa88vQENZiRm0GRq6a+HPGQMd2kTQIhAKMSvzIBnni7ot/OSie2TmJLY4SwTQAevXysE2RbFDYdAiEBCUEaRQnMnbp79mxDXDf6AU0cN/RPBjb9qSHDcWZHGzUCIG2Es59z8ugGrDY+pxLQnwfotadxd+Uyv/Ow5T0q5gIJAiEAyS4RaI9YG8EWx/2w0T67ZUVAw8eOMB6BIUg0Xcu+3okCIBOs/5OiPgoTdSy7bcF9IGpSE8ZgGKzgYQVZeN97YE00\n-----END RSA PRIVATE KEY-----", "test", "") << "\n";
    
    
    MarketData::GetFundingRateHistoryResponse response = MarketData::RestAPI::get_funding_rate_history(api);
    std::cout << "Success" << std::endl;
    if (std::holds_alternative<ServerError>(response)) {
        ServerError error = std::get<ServerError>(response);
        std::cout << "Error: " << error.code << " " << error.msg << "\n";
    } else {
        auto obj = std::get<MarketData::GetFundingRateHistoryObject>(response);
        for (auto &funding_rate : obj.funding_rates) {
            std::cout << "Symbol: " << funding_rate.symbol << "\n";
            std::cout << "Funding Rate: " << funding_rate.funding_rate << "\n";
            std::cout << "Funding Time: " << funding_rate.funding_time << "\n";
            std::cout << "Mark Price: " << funding_rate.mark_price << "\n";
            std::cout << "\n";
        }
    }

        
    return 0;
}