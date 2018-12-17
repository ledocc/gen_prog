set( gen_prog_Boost_VERSION
    1.64.0
    )

set( gen_prog_Boost_COMPONENTS
    filesystem
    system
    thread
    )

if (ANDROID)
    set(Boost_USE_STATIC_LIBS        ON)
else()
    if(BUILD_SHARED_LIBS)
        set(Boost_USE_STATIC_LIBS        OFF)
    else()
        set(Boost_USE_STATIC_LIBS        ON)
    endif()
endif()

find_package(
    Boost
        ${gen_prog_Boost_VERSION}
    REQUIRED
    COMPONENTS
        ${gen_prog_Boost_COMPONENTS}
    )
