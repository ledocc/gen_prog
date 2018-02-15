# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)




include(cmut_boost_test)

cmut_test__find_boost_test(1.64.0)
cmut_test__find_turtle()

if(NOT Boost_UNIT_TEST_FRAMEWORK_FOUND OR NOT TURTLE_FOUND)
    return()
endif()


include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )

cmut__build__define_output_dir("${PROJECT_BINARY_DIR}/test")



add_subdirectory(algorithm)
#add_subdirectory(ref_ptr)
