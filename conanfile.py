from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake

class BinanceConnectorCppConan(ConanFile):
    name = "binanceconnectorcpp"
    version = "1.0"
    settings = "os", "arch", "compiler", "build_type"
    requires = [
        "boost/1.87.0",
        "openssl/3.4.1",
        "simdjson/3.11.5"
    ]
    generators = "CMakeDeps", "CMakeToolchain"
    options = {
        "shared": [True, False]
    }
    default_options = {
        "shared": False,
        "boost/*:without_test": True,
        "boost/*:without_python": True
    }

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()