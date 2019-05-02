# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

set(target gen_prog)

add_library( ${target} INTERFACE )
cmut__project__setup_library( ${target}
    CXX_FEATURES cxx_std_14
    )

set(${target}_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${target}")

#set(
#    ${target}_HEADERS
#    "${${target}_INCLUDE_DIR}/environ.hpp"
#)

cmut__install__install_target( ${target}
    INCLUDE_DIRECTORIES ${${target}_INCLUDE_DIR}
    )
