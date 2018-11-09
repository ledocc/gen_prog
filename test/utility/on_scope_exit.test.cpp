#define BOOST_TEST_MODULE gen_prog__utility__on_scope_exit
#include <boost/test/unit_test.hpp>



#include <gen_prog/utility/on_scope_exit.hpp>



namespace gen_prog {
namespace utility {
namespace test {


BOOST_AUTO_TEST_CASE( happy_path )
{
    int x = 10;

    {
        BOOST_TEST( x == 10 );
        auto reset_x = on_scope_exit( [&x]() { x = 0; } );
        BOOST_TEST( x == 10 );
    }

    BOOST_TEST( x == 0 );
}


} // namespace test
} // namespace utility
} // namespace gen_prog
