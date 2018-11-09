

set(TEST_SRC
    on_scope_exit.test.cpp
    version.test.cpp
)

cmut__test__boost__add_tests("unit__utility" ${TEST_SRC})

cmut__test__add_build_failure_test(
    NAMESPACE "unit__utility"
    NAME on_scope_exit__invalid_callable_type
)
