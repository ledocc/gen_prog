# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


set(TARGET_NAME smart_ptr_test)

#------------------------------------------------------------------------------
# include dependancies
#------------------------------------------------------------------------------
include(UseBoost)


add_definitions(-DBOOST_TEST_DYN_LINK)


set(Min_Boost_Version_For_Thread 102500)
set(Min_Boost_Version_For_Atomic 105300)


if(Boost_VERSION EQUAL Min_Boost_Version_For_Thread OR Boost_VERSION GREATER Min_Boost_Version_For_Thread)
    add_definitions(-DGEN_PROG__BOOST_THREAD_AVAILABLE)
endif()


if(Boost_VERSION EQUAL Min_Boost_Version_For_Atomic OR Boost_VERSION GREATER Min_Boost_Version_For_Atomic)
    add_definitions(-DGEN_PROG__BOOST_ATOMIC_AVAILABLE)
endif()


if(GEN_PROG__USE_CXX11)
    add_definitions(-DGEN_PROG__CXX11_AVAILABLE)
endif()


#------------------------------------------------------------------------------
# define header and source files
#------------------------------------------------------------------------------

set(REF_PTR_TEST_SRC
        accessor.cpp
        complex.cpp
        constructor.cpp
        destructor.cpp
        manipulator.cpp
        observer_ptr.cpp)

#------------------------------------------------------------------------------
# build commands
#------------------------------------------------------------------------------
add_executable( ${TARGET_NAME} ${REF_PTR_TEST_SRC} )

target_link_libraries( ${TARGET_NAME} ${Boost_LIBRARIES} )
