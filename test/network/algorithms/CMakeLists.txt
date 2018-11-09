
set(TEST_SRC
    connect.test.cpp
    resolve.test.cpp
)

cmut__test__boost__add_tests("unit__network__algorithms" ${TEST_SRC})


set_tests_properties(
    unit__network__algorithms__connect
    PROPERTIES
        FIXTURES_REQUIRED server)
