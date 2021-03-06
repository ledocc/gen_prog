#define BOOST_TEST_MODULE gen_prog__version
#include <boost/test/unit_test.hpp>



#include <iomanip>
#include <iostream>

#include <boost/mpl/list.hpp>

#include <gen_prog/utility/version.hpp>


namespace gen_prog {
namespace test {


using types_to_test = boost::mpl::list< char, unsigned char, short, unsigned short, int, unsigned int >;


BOOST_AUTO_TEST_CASE_TEMPLATE( ctor, T, types_to_test )
{
    simple_version< T > v{ 1, 2, 3 };

    BOOST_CHECK( v.get_major() == 1 );
    BOOST_CHECK( v.get_minor() == 2 );
    BOOST_CHECK( v.get_patch() == 3 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( ctor2, T, types_to_test )
{
    simple_version< T > v = { 1, 2, 3 };

    BOOST_CHECK( v.get_major() == 1 );
    BOOST_CHECK( v.get_minor() == 2 );
    BOOST_CHECK( v.get_patch() == 3 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( equal, T, types_to_test )
{
    simple_version< T > v{ 1, 2, 3 };
    simple_version< T > v2{ 1, 2, 3 };

    BOOST_CHECK( v == v2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( less_major, T, types_to_test )
{
    simple_version< T > v  = { 1, 2, 3 };
    simple_version< T > v2 = { 2, 2, 3 };

    BOOST_CHECK( v < v2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( less_minor, T, types_to_test )
{
    simple_version< T > v  = { 1, 2, 3 };
    simple_version< T > v2 = { 1, 3, 3 };

    BOOST_CHECK( v < v2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( less_patch, T, types_to_test )
{
    simple_version< T > v  = { 1, 2, 3 };
    simple_version< T > v2 = { 1, 2, 4 };

    BOOST_CHECK( v < v2 );
}


BOOST_AUTO_TEST_CASE_TEMPLATE( assign, T, types_to_test )
{
    simple_version< T > v;
    v.set( 1, 2, 3 );

    BOOST_CHECK( v.get_major() == 1 );
    BOOST_CHECK( v.get_minor() == 2 );
    BOOST_CHECK( v.get_patch() == 3 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( stream, T, types_to_test )
{
    simple_version< T > v;
    v.set( 1, 2, 3 );

    std::stringstream ss;
    ss << v;

    BOOST_CHECK( ss.str() == "1.2.3" );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( stream_major, T, types_to_test )
{
    simple_version< T > v;
    v.set( 1, 2, 3 );

    std::stringstream ss;
    ss << std::setprecision( 1 ) << v;

    BOOST_CHECK( ss.str() == "1" );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( stream_major_minor, T, types_to_test )
{
    simple_version< T > v;
    v.set( 1, 2, 3 );

    std::stringstream ss;
    ss << std::setprecision( 2 ) << v;

    BOOST_CHECK( ss.str() == "1.2" );
}

}  // namespace test
}  // namespace gen_prog
