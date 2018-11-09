#define BOOST_TEST_MODULE gen_prog__type_traits__is_duration
#include <boost/test/unit_test.hpp>



#include <chrono>
#include <type_traits>

#include <gen_prog/type_traits/is_duration.hpp>



namespace gen_prog {
namespace type_traits {
namespace test {

BOOST_AUTO_TEST_CASE( not_duration_value )
{
    BOOST_TEST( is_duration< int >::value == false );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( not_duration_type )
{
    BOOST_TEST( ( std::is_same< is_duration< int >::type, std::false_type >::value ) == true );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( not_duration_type_t )
{
    BOOST_TEST( ( std::is_same< is_duration_t< int >, std::false_type >::value ) == true );
}

//--------------------------------------------------------------------------------------------------------------------//

#if __cplusplus >= 201703L

BOOST_AUTO_TEST_CASE( not_duration_type_v )
{
    BOOST_TEST( is_duration_v< int > == false );
}

#endif

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( duration_type )
{
    BOOST_TEST( is_duration< std::chrono::seconds >::value == true );
    BOOST_TEST( ( std::is_same< is_duration< std::chrono::seconds >::type, std::true_type >::value ) == true );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( duration_value )
{
    BOOST_TEST( is_duration< std::chrono::seconds >::value == true );
    BOOST_TEST( ( std::is_same< is_duration< std::chrono::seconds >::type, std::true_type >::value ) == true );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( duration_type_t )
{
    BOOST_TEST( ( std::is_same< is_duration_t< std::chrono::seconds >, std::true_type >::value ) == true );
}

//--------------------------------------------------------------------------------------------------------------------//

#if __cplusplus >= 201703L

BOOST_AUTO_TEST_CASE( duration_type_v )
{
    BOOST_TEST( is_duration_v< std::chrono::seconds > == true );
}

#endif

} // namespace test
} // namespace type_traits
} // namespace gen_prog
