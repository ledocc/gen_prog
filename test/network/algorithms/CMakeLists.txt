
set(TEST_SRC
    connect.test.cpp
    resolve.test.cpp
)

cmut_add_boost_tests("unit_network_algorithms" ${TEST_SRC})


set_tests_properties(
    unit_network_algorithms__connect
    PROPERTIES
        FIXTURES_REQUIRED server)
