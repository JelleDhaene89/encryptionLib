from conans import ConanFile, CMake
import os

class EncryptionLibConan(ConanFile):
    name = "encryption-lib"
    scm = {
        "type": "git",
        "subfolder": "hello",
        "url": "auto",
        "revision": "auto"
    }
    url = "https://github.com/JelleDhaene89/encryptionLib"
    license = "MIT"
    description = "encryption library"
    settings = "os", "compiler", "build_type", "arch"
    options = {}
    default_options = ""
    generators = "cmake"
    exports_sources = "*", "!build/*", "!ninja.zip"
    build_policy = "missing"

    def config_options(self):
        if self.settings.compiler == 'gcc' and float(self.settings.compiler.version.value) >= 5.1:
            self.settings.compiler.libcxx = 'libstdc++11'

    requires = (
    )

    def configure(self):
        if self.settings.os == "Windows":
            self.requires("openssl/3.2.0")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CODE_COVERAGE"] = (self.settings.os == "Linux" and self.settings.build_type == "Debug" and self.settings.compiler == "gcc")
        cmake.definitions["MIN_COVERAGE"] = 50
        cmake.configure(source_folder=".")
        cmake.parallel = False
        cmake.build()
        cmake.test(output_on_failure=True)
        cmake.install()
        if self.settings.os == "Linux" and self.settings.build_type == "Debug" and self.settings.compiler == "gcc":
            self.run("cmake --build . --target coverage-check")

#    def package(self):
#         nothing to do here. All is handled by cmake.install() above.

    def package_info(self):
        self.cpp_info.libs = ["DI1Core"]
