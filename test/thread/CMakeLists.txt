

set(TEST_SRC
    atomic_try_mutex.test.cpp
)

cmut_add_boost_tests("unit_thread" ${TEST_SRC})
