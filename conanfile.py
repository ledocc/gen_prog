from conans import ConanFile, CMake
import os

class GenProgConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "boost/1.67.0@conan/stable" # comma-separated list of requirements
    generators = "cmake_paths"
    default_options = ""

    def build(self):
        cmake = CMake(self, generator="Ninja")
        cmake.verbose=True
        for var, val in os.environ.items():
            print("[{0}] = {1}".format(var,val))
        for var, val in cmake.definitions.items():
            print("[{0}] = {1}".format(var,val))
        print(cmake.command_line)
        cmake.configure()
        cmake.build()
        cmake.test()

    def imports(self):
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)
