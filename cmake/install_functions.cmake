# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


#-----------------------------------------------------------------------------
# common install command for simple project
#-----------------------------------------------------------------------------

include(parse_functions)
include( determine_lib_postfix )


# Prototype : 
# INSTALL_LIBRARY( TARGET_NAME [ INCLUDE_DIRS include_dir1 [include_dir2 [...]] ]
#                               [ INCLUDE_FILES include_file1 [include_file2 [...]] ]
#                               [ INSTALL_PDB TRUE|FALSE ] )
function( INSTALL_LIBRARY TARGET_NAME )

    set( ARG_LIST ${ARGV} )
    set( TYPES_NAME_ARG_LIST INCLUDE_DIRS INCLUDE_FILES INSTALL_PDB)

    
    if( NOT DEFINED LIB_POSTFIX )
        determine_lib_postfix()
    endif()
    
    #-----------------------------------------------------------------------------
    # define install directory
    #-----------------------------------------------------------------------------
    set( INSTALL_INCDIR include )
    set( INSTALL_BINDIR bin )
    if(WIN32)
        set(INSTALL_LIBDIR ${INSTALL_BINDIR})
        set(INSTALL_ARCHIVEDIR lib)
    else()
        set(INSTALL_LIBDIR lib${LIB_POSTFIX})
        set(INSTALL_ARCHIVEDIR lib${LIB_POSTFIX})
    endif()

    
    
    #-----------------------------------------------------------------------------
    # install target
    #-----------------------------------------------------------------------------
    install(
        TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${INSTALL_BINDIR}
        LIBRARY DESTINATION ${INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVEDIR}
    )

    
    #-----------------------------------------------------------------------------
    # install include directories if required
    #-----------------------------------------------------------------------------
    parse_args( INCLUDE_DIRS ARG_LIST TYPES_NAME_ARG_LIST INCLUDE_DIRS_TO_INSTALL )
    list( LENGTH INCLUDE_DIRS_TO_INSTALL NUM_INCLUDE_DIRS_TO_INSTALL )
    if( NUM_INCLUDE_DIRS_TO_INSTALL GREATER 0 )
        install( DIRECTORY ${INCLUDE_DIRS_TO_INSTALL} DESTINATION ${INSTALL_INCDIR} )
    endif()
    
    
    #-----------------------------------------------------------------------------
    # install include files if required
    #-----------------------------------------------------------------------------
    parse_args( INCLUDE_FILES ARG_LIST TYPES_NAME_ARG INCLUDE_FILES_TO_INSTALL )
    list( LENGTH INCLUDE_FILES_TO_INSTALL NUM_INCLUDE_FILES_TO_INSTALL )
    if( NUM_INCLUDE_FILES_TO_INSTALL GREATER 0 )
        install( FILES ${INCLUDE_FILES_TO_INSTALL} DESTINATION ${INSTALL_INCDIR} )
    endif()
    
    
    #-----------------------------------------------------------------------------
    # install pdb file if required
    #-----------------------------------------------------------------------------
    if( MSVC )
        parse_args( INSTALL_PDB ARG_LIST TYPES_NAME_ARG INSTALL_PDB_FILES )
        if( INSTALL_PDB_FILES )
            get_property( TARGET_LIB_NAME_DEBUG_LOCATION TARGET ${TARGET_NAME} PROPERTY DEBUG_LOCATION )
            get_filename_component( DEBUG_PDB_FILE_LOCATION ${TARGET_LIB_NAME_DEBUG_LOCATION} PATH )
            get_filename_component( DEBUG_PDB_FILE_NAME ${TARGET_LIB_NAME_DEBUG_LOCATION} NAME_WE )
            set( DEBUG_PDB_FILE_LOCATION ${DEBUG_PDB_FILE_LOCATION}/${DEBUG_PDB_FILE_NAME}.pdb )
            #MESSAGE("DEBUG_PDB_FILE_LOCATION = ${DEBUG_PDB_FILE_LOCATION}")
            install(
                FILES ${DEBUG_PDB_FILE_LOCATION}
                DESTINATION ${INSTALL_BINDIR}
                CONFIGURATIONS Debug
            )
        endif()
    endif()
    
endfunction()


# Prototype : 
# INSTALL_EXECUTABLE( TARGET_NAME [ INSTALL_PDB TRUE|FALSE ] )
function( INSTALL_EXECUTABLE TARGET_NAME )


    set( ARG_LIST ${ARGV} )
    set( TYPES_NAME_ARG_LIST INSTALL_PDB )

    #-----------------------------------------------------------------------------
    # define install directory
    #-----------------------------------------------------------------------------
    set( INSTALL_BINDIR bin )

    
    #-----------------------------------------------------------------------------
    # install target
    #-----------------------------------------------------------------------------
    install(
        TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION ${INSTALL_BINDIR}
    )
    
        
    #-----------------------------------------------------------------------------
    # install pdb file if required
    #-----------------------------------------------------------------------------
    if( MSVC )
        parse_args( INSTALL_PDB ARG_LIST TYPES_NAME_ARG INSTALL_PDB_FILES )
        if( INSTALL_PDB_FILES )
            get_property( TARGET_NAME_DEBUG_LOCATION TARGET ${TARGET_NAME} PROPERTY DEBUG_LOCATION )
            get_filename_component( DEBUG_PDB_FILE_LOCATION ${TARGET_NAME_DEBUG_LOCATION} PATH )
            get_filename_component( DEBUG_PDB_FILE_NAME ${TARGET_NAME_DEBUG_LOCATION} NAME_WE )
            set( DEBUG_PDB_FILE_LOCATION ${DEBUG_PDB_FILE_LOCATION}/${DEBUG_PDB_FILE_NAME}.pdb )
            #MESSAGE("DEBUG_PDB_FILE_LOCATION = ${DEBUG_PDB_FILE_LOCATION}")
            install(
                FILES ${DEBUG_PDB_FILE_LOCATION}
                DESTINATION ${INSTALL_BINDIR}
                CONFIGURATIONS Debug
            )
        endif()
    endif()
    
endfunction()


# Prototype :
# INSTALL_LIBRARY_FILE( FILENAME )
function( INSTALL_LIBRARY_FILE FILENAME )

    if( NOT DEFINED LIB_POSTFIX )
        determine_lib_postfix()
    endif()

    #-----------------------------------------------------------------------------
    # define install directory
    #-----------------------------------------------------------------------------
    set( INSTALL_BINDIR bin )
    if(WIN32)
        set(INSTALL_LIBDIR ${INSTALL_BINDIR})
    else()
        set(INSTALL_LIBDIR lib${LIB_POSTFIX})
    endif()



    #-----------------------------------------------------------------------------
    # install target
    #-----------------------------------------------------------------------------
    install(
        FILES ${FILENAME}
        DESTINATION ${INSTALL_LIBDIR}
    )

endfunction()


function( DEFINE_UNINSTALL_TARGET )

    if(NOT CMAKEMODULES_UNINSTALL_CMAKE_IN)
        find_file(CMAKEMODULES_UNINSTALL_CMAKE_IN cmake_uninstall.cmake.in 
                  PATHS ${CMAKE_MODULE_PATH}
                  DOC "source file used to generate uninstall target"
                  NO_DEFAULT_PATH)
        mark_as_advanced(FORCE CMAKEMODULES_UNINSTALL_CMAKE_IN)
    else()
        message( AUTHOR_WARNING "define_uninstall_target already called, skipped." )
    endif()
#-----------------------------------------------------------------------------
### uninstall target
#-----------------------------------------------------------------------------
    configure_file(
      ${CMAKEMODULES_UNINSTALL_CMAKE_IN}
      "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
      IMMEDIATE @ONLY)
    add_custom_target(uninstall
      "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
endfunction()