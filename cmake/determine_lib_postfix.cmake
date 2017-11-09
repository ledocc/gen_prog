# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


#------------------------------------------------------------------------------
# determine the LIB_POSTFIX variable
#------------------------------------------------------------------------------


macro( DETERMINE_LIB_POSTFIX )

    if(CMAKE_SIZEOF_VOID_P MATCHES "8")
        set(SYSTEM_ARCHITECTURE "64bits")
        if(UNIX AND NOT WIN32 AND NOT APPLE)
            set(LIB_POSTFIX "64")
        endif(UNIX AND NOT WIN32 AND NOT APPLE)
    else(CMAKE_SIZEOF_VOID_P MATCHES "8")
        set(SYSTEM_ARCHITECTURE "32bits")
        set(LIB_POSTFIX "")
    endif(CMAKE_SIZEOF_VOID_P MATCHES "8")
    mark_as_advanced(LIB_POSTFIX)

endmacro( DETERMINE_LIB_POSTFIX )
