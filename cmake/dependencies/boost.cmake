set( gen_prog_Boost_VERSION
    1.61.0
    )

set( gen_prog_Boost_COMPONENTS
    filesystem
    system
    thread
    )

find_package(
    Boost
        ${gen_prog_Boost_VERSION}
    REQUIRED
    COMPONENTS
        ${gen_prog_Boost_COMPONENTS}
    ${FIND_PACKAGE_MODE}
    )
