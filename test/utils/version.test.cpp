#define BOOST_TEST_MODULE gen_prog__version
#include <boost/test/unit_test.hpp>



#include <iomanip>
#include <iostream>

#include <boost/mpl/list.hpp>

#include <gen_prog/utils/version.hpp>



using types_to_test = boost::mpl::list<char, unsigned char, short, unsigned short, int, unsigned int>;


BOOST_AUTO_TEST_CASE_TEMPLATE( ctor, T, types_to_test)
{
    gen_prog::simple_version< T > v{ 1, 2, 3 };

    BOOST_CHECK( v.getMajor() == 1 );
    BOOST_CHECK( v.getMinor() == 2 );
    BOOST_CHECK( v.getPatch() == 3 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( assign , T, types_to_test )
{
    gen_prog::simple_version< T > v;
    v.set( 1, 2, 3 );

    BOOST_CHECK( v.getMajor() == 1 );
    BOOST_CHECK( v.getMinor() == 2 );
    BOOST_CHECK( v.getPatch() == 3 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( stream , T, types_to_test )
{
    gen_prog::simple_version< T > v;
    v.set( 1, 2, 3 );

    std::stringstream ss;
    ss << v;

    BOOST_CHECK( ss.str() == "1.2.3" );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( stream_major , T, types_to_test )
{
    gen_prog::simple_version< T > v;
    v.set( 1, 2, 3 );

    std::stringstream ss;
    ss << std::setprecision( 1 ) << v;

    BOOST_CHECK( ss.str() == "1" );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( stream_major_minor , T, types_to_test )
{
    gen_prog::simple_version< T > v;
    v.set( 1, 2, 3 );

    std::stringstream ss;
    ss << std::setprecision( 2 ) << v;

    BOOST_CHECK( ss.str() == "1.2" );
}
