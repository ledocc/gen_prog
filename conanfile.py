from conans import ConanFile, CMake, tools, errors

import os
import platform



class GenProgConan(ConanFile):
    name = "gen_prog"
    version = "0.7.1"
    author = "David Callu (callu.david at gmail.com)"
    license = "Boost Software License - Version 1.0"
    url = "https://github.com/ledocc/gen_prog"
    description = "generic programming code"
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    options = {"shared": [True, False]}
    default_options = dict( { "shared":True, "*:shared":True } )


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

    def configure(self):
        if self.settings.cppstd in [ None, "98", "gnu98", "11", "gnu11" ]:
            raise errors.ConanInvalidConfiguration("Library gen_prog require C++ 14 or greater.")

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.test(output_on_failure=True)

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.copy("LICENSE_1_0.txt", dst="licenses", ignore_case=True)



    def _configure_cmake(self):
        cmake = CMake(self, set_cmake_flags=True)
        cmake.verbose=True
        if platform.system() != "Windows":
            cmake.definitions["CMAKE_CXX_STANDARD"] = cmake.definitions["CONAN_CMAKE_CXX_STANDARD"]
            cmake.definitions["CMAKE_CXX_EXTENSIONS"] = cmake.definitions["CONAN_CMAKE_CXX_EXTENSIONS"]
            cmake.definitions["CTEST_TEST_TIMEOUT"] = 3000
        cmake.configure()

        return cmake
