# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)



########################################################################################################################
########################################################################################################################
#
# define minimum cmake version
#
########################################################################################################################
########################################################################################################################
cmake_minimum_required(VERSION 3.6.1)
cmake_policy(VERSION 3.6)



include("${CMAKE_CURRENT_LIST_DIR}/cmake/tools/cmut/cmut.cmake")
########################################################################################################################
########################################################################################################################
#
# define project name/version
#
########################################################################################################################
########################################################################################################################
project(gen_prog)
cmut__config__print_info()
cmut__config__log_project_begin()
cmut__project__set_version_from_file("${CMAKE_CURRENT_LIST_DIR}/version.txt")

cmut__project__get_build_time(${PROJECT_NAME}_BUILD_TIME)
cmut__project__get_git_revision_count(${PROJECT_NAME}_GIT_REVISION_COUNT)
cmut__project__get_git_revision_hash(${PROJECT_NAME}_GIT_REVISION_HASH)


########################################################################################################################
########################################################################################################################
#
# define CMake Module path
#
########################################################################################################################
########################################################################################################################
list(INSERT CMAKE_MODULE_PATH 0
    ${CMAKE_HOME_DIRECTORY}/cmake
)


##--------------------------------------------------------------------------------------------------------------------##
# define build options
##--------------------------------------------------------------------------------------------------------------------##
cmut__config__option_developer_mode()
cmut__config__option_build_documentation(OFF)
cmut__config__option_build_examples(OFF)
cmut__config__option_build_shared_libs(ON)
include(CTest) # define BUILD_TESTING
cmut__config__option_ccache(ON)
cmut__config__option_clang_tidy(OFF)
cmut__config__option_cppcheck(OFF)
cmut__config__option_include_what_you_use(OFF)

cmut__config__default_build_type(Release)

option(BUILD_DEPENDENCIES "use conan to install/build dependencies" OFF)
option(Boost_USE_STATIC_LIBS "Use boost's libraries statically linked." ${BUILD_SHARED_LIBS})
option(GEN_PROG__FORCE_INCLUDE_CONAN_PATHS_CMAKE "Include \"conan_paths.cmake\" generated in binary directory by used with conan." OFF)


##--------------------------------------------------------------------------------------------------------------------##
# install dependencies
##--------------------------------------------------------------------------------------------------------------------##
if(BUILD_DEPENDENCIES)
    cmut__conan__download_cmake_conan()
    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_check(VERSION 1.0.0 REQUIRED)

    if(BUILD_SHARED_LIBS)
        set(CONAN_CMAKE_RUN__OPTIONS OPTIONS "*:shared=True")
    else()
        set(CONAN_CMAKE_RUN__OPTIONS OPTIONS "*:shared=False")
    endif()

    conan_cmake_run(
        CONANFILE conanfile.py
        BUILD missing
        ${CONAN_CMAKE_RUN__OPTIONS}
        )
endif()
if( BUILD_DEPENDENCIES OR CONAN_EXPORTED OR GEN_PROG__FORCE_INCLUDE_CONAN_PATHS_CMAKE)
    include( "${CMAKE_BINARY_DIR}/conan_paths.cmake" )
endif()

########################################################################################################################
########################################################################################################################
#
# find dependencies
#
########################################################################################################################
########################################################################################################################
include("${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies/include_all.cmake")



########################################################################################################################
########################################################################################################################
#
# define build policies
#
########################################################################################################################
########################################################################################################################

set(CMAKE_DEBUG_POSTFIX "d")

# define CMAKE_*_OUTPUT_DIRECTORY
cmut__build__define_output_dir()

# add option to enable build with all cpu's core when use Visual Studio or nmake
cmut__build__msvc__option_use_mp()

# enable C++14
cmut__build__enable_cxx_standard(14)

# enable warning
cmut__build__enable_warning(AGGRESSIVE)

# use RUNPATH instead of depreciated RPATH
cmut__build__enable_runpath_link()

cmut__build__set_cxx_visibility(hidden)

if (MSVC)
    add_definitions(-DUNICODE)
endif()



########################################################################################################################
########################################################################################################################
#
# add subdirectories
#
########################################################################################################################
########################################################################################################################

add_subdirectory(src)

if(BUILD_DOC)
#    add_subdirectory(doc)
endif()

if(BUILD_TESTING)
    add_subdirectory(test)
endif()



########################################################################################################################
########################################################################################################################
#
# define install policies
#
########################################################################################################################
########################################################################################################################

cmut__install__install_config_and_version()
cmut__install__install_config_directory(
    DIRECTORY       "cmake/dependencies"
    DESTINATION     "dependencies/"
)


########################################################################################################################
########################################################################################################################
#
# define uninstall policies
#
########################################################################################################################
########################################################################################################################

#include(cmut_define_uninstall_target)


cmut__config__log_project_end()
