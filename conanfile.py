from conans import ConanFile, CMake, tools
import os

class GenProgConan(ConanFile):
    name = "gen_prog"
    version = "0.7.1"
    author = "David Callu (callu.david at gmail.com)"
    license = "Boost Software License - Version 1.0"
    url = "https://github.com/ledocc/gen_prog"
    description = "generic programming code"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": True}
    generators = "cmake_paths"
    scm = {
        "type": "git",
        "url": "https://github.com/ledocc/gen_prog.git",
        "revision": "auto",
        "submodule": "recursive"
    }
    build_requires = "cmake_installer/3.13.0@conan/stable"
    requires = (("boost/1.69.0@conan/stable"),
                ("turtle/master-1b5d8c8@ledocc/stable"))


    def build(self):
        cmake = CMake(self)
        cmake.verbose=True
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("LICENSE_1_0.txt", dst="licenses", ignore_case=True)

    def package_id(self):
        self.info.header_only()
