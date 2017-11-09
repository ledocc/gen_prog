# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


#------------------------------------------------------------------------------
# define CMAKE_*_OUTPUT_DIRECTORY
#------------------------------------------------------------------------------


include( determine_lib_postfix )

macro( DEFINE_OUTPUT_DIRECTORY )

    if( NOT DEFINED LIB_POSTFIX )
        determine_lib_postfix()
    endif()

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    if(WIN32)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    else(WIN32)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib${LIB_POSTFIX})
    endif(WIN32)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib${LIB_POSTFIX})

endmacro( DEFINE_OUTPUT_DIRECTORY )
