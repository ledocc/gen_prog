#define BOOST_TEST_MODULE gen_prog__utility__on_scope_exit__invalid_callable_type
#include <boost/test/unit_test.hpp>



#include <gen_prog/utility/on_scope_exit.hpp>



namespace gen_prog {
namespace utility {
namespace test {

BOOST_AUTO_TEST_CASE( invalid_callable )
{
    int x = 10;
    {
        auto reset_x = on_scope_exit( [&x]( int ) { x = 0; } );
    }
}


} // namespace test
} // namespace utility
} // namespace gen_prog
