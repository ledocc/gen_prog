# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)



cmut__test__boost__find_required_components(1.64.0)
cmut__test__turtle__find_required_components()


cmut__build__define_output_dir("${PROJECT_BINARY_DIR}/test")


link_libraries(gen_prog)


add_subdirectory(algorithm)
add_subdirectory(boost)
add_subdirectory(network)
add_subdirectory(thread)
add_subdirectory(type_traits)
add_subdirectory(utility)
