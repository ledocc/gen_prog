from conans import ConanFile, CMake, tools, errors, RunEnvironment
from conans.client.build.cppstd_flags import cppstd_from_settings, cppstd_default



class GenProgConan(ConanFile):
    name = "gen_prog"
    version = tools.load("version.txt").rstrip()
    author = "David Callu (callu.david at gmail.com)"
    license = "Boost Software License - Version 1.0"
    url = "https://github.com/ledocc/gen_prog"
    description = "generic programming code"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = dict( { "shared":True } )

    exports = "version.txt"
    no_copy_source = True

    generators = (("cmake"),("cmake_paths"),("virtualrunenv"))
    scm = {
        "type": "git",
        "url": "https://github.com/ledocc/gen_prog",
        "revision": "auto",
        "submodule": "recursive"
    }
    build_requires = (("cmake/3.18.4@"),
                      ("ninja/1.10.1@"))
    requires = (("boost/1.74.0@"),
                ("turtle/1.3.2@"))

    def configure(self):
        tools.check_min_cppstd(self, 14)

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

        if self.settings.os == "Windows":
            return

        env_test = {
            "CTEST_TEST_TIMEOUT": "3000",
            "BOOST_TEST_BUILD_INFO": "1",
            "BOOST_TEST_LOG_LEVEL": "message",
            "BOOST_TEST_RANDOM": "1"
        }
        env_build = RunEnvironment(self).vars
        with tools.environment_append(env_build):
            with tools.environment_append(env_test):
                cmake.test(output_on_failure=True)

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.copy("LICENSE_1_0.txt", dst="licenses", ignore_case=True)


    def _configure_cmake(self):
        cmake = CMake(self, set_cmake_flags=True)
        cmake.verbose=True
        cmake.generator="Ninja"

        cmake.definitions["Boost_USE_STATIC_LIBS"] = "FALSE" if self.options["boost"].shared else "TRUE"
        cmake.configure()

        return cmake
