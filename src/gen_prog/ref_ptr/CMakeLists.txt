# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


set(target ref_ptr)

#------------------------------------------------------------------------------
# define header files
#------------------------------------------------------------------------------

set(${target}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/gen_prog/ref_ptr)

set(${target}_HEADER_FILES
        ${${target}_INCLUDE_DIR}/config.cpp
        ${${target}_INCLUDE_DIR}/observer.cpp
        ${${target}_INCLUDE_DIR}/observer_ptr.cpp
        ${${target}_INCLUDE_DIR}/ref_ptr.cpp
        ${${target}_INCLUDE_DIR}/referenced.cpp
        ${${target}_INCLUDE_DIR}/referenced_definition.cpp
        ${${target}_INCLUDE_DIR}/referenced_fwd.cpp
        ${${target}_INCLUDE_DIR}/policy/delete_handler/no_delete_handler.cpp
        ${${target}_INCLUDE_DIR}/policy/delete_handler/local_delete_handler.cpp
        ${${target}_INCLUDE_DIR}/policy/delete_handler/static_delete_handler.cpp
        ${${target}_INCLUDE_DIR}/policy/thread/boost_atomic.cpp
        ${${target}_INCLUDE_DIR}/policy/thread/boost_mutex.cpp
        ${${target}_INCLUDE_DIR}/policy/thread/single_thread.cpp
        ${${target}_INCLUDE_DIR}/policy/thread/std_atomic.cpp)

add_library(${target} INTERFACE)
#target_sources(${target} ${target}_HEADER_FILES)

#------------------------------------------------------------------------------
# install command
#------------------------------------------------------------------------------
#install_library( ${TARGET_NAME} INCLUDE_DIRS ${${target}_INCLUDE_DIR})
