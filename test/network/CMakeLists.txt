
find_package(Threads)

link_libraries(Threads::Threads)

set(TEST_SRC
    connector.test.cpp
)

#cmut__test__boost__add_tests("unit_network" ${TEST_SRC})

add_test( NAME unit_network__run_python_http_server
          COMMAND python3 "${PROJECT_SOURCE_DIR}/test/scripts/run_server.py" --port 22222
)

add_test( NAME unit_network__stop_python_http_server
          COMMAND python3 "${PROJECT_SOURCE_DIR}/test/scripts/stop_server.py"
)


set_tests_properties(
    unit_network__run_python_http_server
    PROPERTIES
        FIXTURES_SETUP server)

set_tests_properties(
    unit_network__stop_python_http_server
    PROPERTIES
        FIXTURES_CLEANUP server)

add_subdirectory(algorithms)
