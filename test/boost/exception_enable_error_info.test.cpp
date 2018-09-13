#define BOOST_TEST_MODULE gen_prog/boost__exception_enable_error_info
#include <boost/test/unit_test.hpp>



#include <boost/throw_exception.hpp>

#include <gen_prog/boost/exception_enable_error_info.hpp>


void throwStdRuntimeExceptionWithBoostThrowException()
{
    BOOST_THROW_EXCEPTION( std::runtime_error{"test"} );
}

BOOST_AUTO_TEST_CASE(is_same_as_boost_throw_exception)
{
    BOOST_CHECK_THROW( throwStdRuntimeExceptionWithBoostThrowException(),
                       boost::boost_exception_enable_error_info_t<std::runtime_error> );
}
