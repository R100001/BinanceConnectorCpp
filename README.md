
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
pip install conan
```

**Setup Conan:**

```bash
conan profile detect --name binanceconnectorcpp
```

Change compiler.cppstd=gnuXX to compiler.cppstd=gnu23 from ~/.conan2/profiles/binanceconnectorcpp

Run only the first time: 
conan install . --output-folder=build -s build_type=Debug --build=missing --profile:host binanceconnectorcpp --profile:build=binanceconnectorcpp

**Create HMAC and Ed25519 Keys:**

- Go to [Binance's API Management](https://www.binance.com/en/my/settings/api-management).
- Click "*Create API*" on the upper right corner.
- For *HMAC* choose "*System generated*" and follow the steps.
- For *Ed25519* choose "*Self-generated*", go to Binance's [asymetric-key-generator](https://github.com/binance/asymmetric-key-generator/releases) repo, then to Binance's [key generation instructions](https://www.binance.com/en/support/faq/detail/6b9a63f1e3384cf48a2eedb82767a69a) and follow the steps to generate Ed25519 keys!

The are examples of how to use these keys below!

---

## Examples

### HMAC and Ed25519 keys

```bash

```

### REST API

```bash

```

### Websocket API

```bash

```

### Websocket Market Data Streams

```bash

```

### Websocket User Data Streams

```bash

```