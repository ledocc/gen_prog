


option(BUILD_DEPENDENCIES "use conan to install/build dependencies" OFF)
option(ADESS__FORCE_INCLUDE_CONAN_PATHS_CMAKE "Include \"conan_paths.cmake\" generated in binary directory by used with conan." OFF)


if(BUILD_DEPENDENCIES)

    cmut__lang__set_if_not_defined(CMAKE_CXX_STANDARD 14)

    cmut__conan__download_cmake_conan()
    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_check(VERSION 1.2.0 REQUIRED)

    cmut__cmake_conan__get_shared_options(shared_options)
    cmut__cmake_conan__get_cppstd_settings(cppstd_settings)

    conan_cmake_run(
        CONANFILE conanfile.py
        BUILD missing
        ${cppstd_settings}
        ${shared_options}
        )
endif()

if( BUILD_DEPENDENCIES OR CONAN_EXPORTED OR ADESS__FORCE_INCLUDE_CONAN_PATHS_CMAKE)
    if(CONAN_EXPORTED OR ADESS__FORCE_INCLUDE_CONAN_PATHS_CMAKE)
        cmut__conan__capture_cxx_standard()
    endif()
    include( "${CMAKE_BINARY_DIR}/conan_paths.cmake" )
endif()
