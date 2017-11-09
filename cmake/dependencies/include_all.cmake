
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

file(GLOB DEPENDENCY_FILES "${_DIR}/*.cmake")

list(REMOVE_ITEM DEPENDENCY_FILES "${CMAKE_CURRENT_LIST_FILE}")


foreach(f ${DEPENDENCY_FILES})
    include(${f})
endforeach()
