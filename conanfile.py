from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake

class BinanceConnectorCppConan(ConanFile):
    name = "binanceconnectorcpp"
    version = "1.0"
    settings = "os", "arch", "compiler", "build_type"
    requires = "openssl/3.4.1", "libcurl/8.11.1", "simdjson/3.11.5"
    generators = "CMakeDeps", "CMakeToolchain"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()