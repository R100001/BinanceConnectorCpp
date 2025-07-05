
# BinanceConnectorCpp

---

## About

This project is a wrapper for the Binance API (currently it only supports USD-M futures).

It implements both Rest API and Websocket connections (Websocket API, Websocket Market Data Streams, Websocket User Data Streams), providing full functionality.

There are projects similar to this in other programming languages and can be found in [Binance's Github](https://github.com/binance)!

The goal of this project is to push for more performance, low latency calls, blazing fast response parsing and ease of use! There is no need for the user of this project to know how to use any of the underlying libraries. The only knowledge you will need is how to use C++ (if you are here, you probably know)!

This project is still a work in progress. It hasn't been tested thoroughly for bugs or even performance. A lot of plans and enchancements are being developed and changes will be pushed in the near future changing even the core of this!

Any contribution or feedback is welcomed and encouraged!

---

## Preparation

Below are the steps recommended to use this project! If you are confident with building this project yourself you can skip this part.

To use this project, you will need:

- A **[C++ Compiler (GCC)](https://gcc.gnu.org/)** and **[Python](https://www.python.org/)**

- **[Miniconda](https://www.anaconda.com/download/success)** (*Optional but strongly recommended*)

- **[Conan](https://conan.io/)** (Can be installed with Conda.. Instructions below!)

- **[CMake](https://cmake.org/download/)**

- **[Git](https://git-scm.com/downloads)**

If you need any help with installation or anything else you can raise an issue and someone will help you. I will consider adding instructions for different operating systems and distributions in the future.

---

## How to use this project

**Clone the repo:**

```bash
git clone https://github.com/R100001/BinanceConnectorCpp.git
```

**Setup a Conda env:**

```bash
conda create -n binanceconnectorcpp python
conda activate binanceconnectorcpp
```

**Setup Conan:**

Conan can be installed into the conda environment we created and activated with:

```bash
pip install conan
```

To use Conan we need a profile!
There is a Conan profile in *config* folder. This profile is specifically for the *Linux* os.
For different os you can copy the profile and change the settings based on your needs.
Different profiles will be tested and be included in the future.
You can contribute your profiles too!

To run Conan using the profile use:

```bash
conan install . --output-folder=build --build=missing --profile=./config/binanceconnectorcpp
```

**Build and Run:**

To build the project using CMAKE run:

```bash
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

Then you can run it with:

```bash
./BinanceConnectorCpp
```

**Create HMAC and Ed25519 Keys:**

- Go to [Binance's API Management](https://www.binance.com/en/my/settings/api-management).
- Click "*Create API*" on the upper right corner.
- For *HMAC* choose "*System generated*" and follow the steps.
- For *Ed25519* choose "*Self-generated*", go to Binance's [asymetric-key-generator](https://github.com/binance/asymmetric-key-generator/releases) repo, then to Binance's [key generation instructions](https://www.binance.com/en/support/faq/detail/6b9a63f1e3384cf48a2eedb82767a69a) and follow the steps to generate Ed25519 keys!

The are examples of how to use these keys below!

---

## Examples

### Read HMAC, Ed25519 keys and construct the API

```C++

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "api.hpp"

static std::string readFile(std::string const &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

int main() {

    std::cout << "BinanceConnectorCpp\n";

    std::filesystem::path const config_path = std::filesystem::path("..") / "config";
    std::string const hmac_api_key = readFile(config_path / "hmacapikey");
    std::string const hmac_api_secret = readFile(config_path / "hmacapisecret");
    std::string const ed25519_api_key = readFile(config_path / "ed25519apikey");
    std::string const ed25519_private_key = readFile(config_path / "ed25519privatekey");
    std::string ed25519_passphrase;
    std::cout << "ED25519 Passphrase (press Enter for no passphrase): ";
    std::getline(std::cin, ed25519_passphrase);

    API api(hmac_api_key, hmac_api_secret, ed25519_api_key, ed25519_private_key, ed25519_passphrase);

    return 0;
}

```

### REST API

```C++
void print_server_time(API &api) {

    MarketData::CheckServerTimeResponse server_time = api.check_server_time();
    if (std::holds_alternative<ServerMessage>(server_time)) {
        ServerMessage error = std::get<ServerMessage>(server_time);
        std::cout << error.code << " " << error.msg << "\n";
    } else {
        auto obj = std::get<MarketData::CheckServerTimeObject>(server_time);
        std::cout << "Server Time: " << obj.server_time << "\n";
    }
}
```

### Websocket API

```C++
void get_order_book_from_stream(API &api) {

    api.ws_api_connect();
    api.ws_api_message_callback([](std::string_view message) {
        std::cout << "API Message: " << message << "\n";
    });
    api.ws_api_error_callback([](std::string_view error) {
        std::cerr << "API Error: " << error << "\n";
    });
    api.ws_api_session_logon();
    api.order_book_stream("btcusdt", 5);
    api.ws_api_session_logout();
}
```

### Websocket Market Data Streams

```C++
void connect_to_websocket_market_data_streams(API &api) {
    
    api.ws_market_streams_connect();
    api.ws_market_streams_message_callback([](std::string_view message) {
        std::cout << "Received message: " << message << "\n";
    });
    api.ws_market_streams_error_callback([](std::string_view error) {
        std::cerr << "Error: " << error << "\n";
    });

    api.kline_candlestick_streams(WebsocketMarketStreamsMethod::SUBSCRIBE, "btcusdt", "1m");
    api.ws_market_streams_disconnect();
}
```

### Websocket User Data Streams

```C++

void handle_websocket_user_data_streams(API &api) {

    api.ws_user_data_streams_message_callback([](std::string_view message) {
        std::cout << "User Data Stream Message: " << message << "\n";
    });
    api.ws_user_data_streams_error_callback([](std::string_view error) {
        std::cerr << "User Data Stream Error: " << error << "\n";
    });

    api.ws_user_data_streams_connect();
    api.ws_user_data_streams_disconnect();

}

```

---

## Important Note

The current REST API implementation returns a std::variant object that holds either the expected response or an error message.
All Websocket Streams implementations return a std::string_view.
All of these are subject to change.

This is an early version. The library will change and evolve. You should expect many changes that will break probably any code build on top.
