

set(TEST_SRC
    atomic_try_mutex.test.cpp
)

cmut__test__boost__add_tests("unit_thread" ${TEST_SRC})
