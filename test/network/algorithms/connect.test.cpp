#define BOOST_TEST_MODULE gen_prog__network__algorithms__connect
#include <boost/test/unit_test.hpp>

#include <ciso646>

#include <gen_prog/network/algorithms/connect.hpp>
#include <vector>



namespace gen_prog {
namespace network {
namespace algorithms {
namespace test {

struct Fixture
{
    ~Fixture()
    {
        _work_guard.reset();
        if ( _thread.joinable() ) { _thread.join(); }
    }

    boost::asio::io_context                                                    _io_context;
    boost::asio::executor_work_guard< boost::asio::io_context::executor_type > _work_guard =
        boost::asio::make_work_guard( _io_context );
    std::thread _thread{ [this]() { _io_context.run(); } };

    boost::asio::ip::tcp::socket       _socket{ _io_context };
    boost::asio::high_resolution_timer _timer{ _io_context };

    boost::asio::ip::address_v4 unknownIPv4 = boost::asio::ip::address_v4::from_string( "0.0.0.1" );
    boost::asio::ip::tcp::endpoint unknown_endpoint{ unknownIPv4, 22222 };

    boost::asio::ip::address_v4 localhostIPv4 = boost::asio::ip::address_v4::from_string( "127.0.0.1" );
    boost::asio::ip::tcp::endpoint localhost_endpoint{ localhostIPv4, 22222 };

    std::vector< boost::asio::ip::tcp::endpoint > _unknown_endpoints{ { unknown_endpoint } };
    std::vector< boost::asio::ip::tcp::endpoint > _localhost_endpoints{ { localhost_endpoint } };
};



//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//



BOOST_FIXTURE_TEST_SUITE( connect_with_timeout, Fixture )

BOOST_AUTO_TEST_CASE( invalid_hostname )
{
    BOOST_CHECK_THROW( connect( _socket, _timer, _unknown_endpoints, std::chrono::hours( 1 ) ),
                       boost::system::system_error );
}

// TODO
// BOOST_AUTO_TEST_CASE( timeout )
//{
//    auto connector_ =
//        make_connector( _socket, std::vector< boost::asio::ip::tcp::endpoint >{ { localhost_endpoint } } );

//    // Occasionally, timer is scheduled after resolve, so timeout is not triggered and test fail
//    // do it 10 time so almost one will success as we want
//    BOOST_CHECK_EXCEPTION( for ( int i = 0; i < 100; ++i ) { connector_.apply( std::chrono::nanoseconds( 0 ) ); },
//                           std::system_error,
//                           []( const std::system_error & exception ) {
//                               return exception.code()
//                                      == boost::asio::error::make_error_code( boost::asio::error::operation_aborted );
//                           } );
//}

BOOST_AUTO_TEST_CASE( happy_path )
{
    auto result = connect( _socket, _timer, _localhost_endpoints, std::chrono::hours( 1 ) );
    BOOST_TEST( result == localhost_endpoint );
    BOOST_TEST( _socket.remote_endpoint() == localhost_endpoint );
}

BOOST_AUTO_TEST_SUITE_END() // connect_with_timeout



//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//



BOOST_FIXTURE_TEST_SUITE( connect_with_timeout_with_error_code, Fixture )


BOOST_AUTO_TEST_CASE( invalid_hostname )
{
    boost::system::error_code ec;
    BOOST_CHECK_NO_THROW( connect( _socket, _timer, _unknown_endpoints, std::chrono::hours( 1 ), ec ) );
    BOOST_CHECK( ec );
}

// TODO
// BOOST_AUTO_TEST_CASE( timeout )
//{
//}

BOOST_AUTO_TEST_CASE( happy_path )
{
    boost::system::error_code ec;
    BOOST_CHECK_NO_THROW( connect( _socket, _timer, _localhost_endpoints, std::chrono::hours( 1 ), ec ) );
    BOOST_CHECK( not ec );
}

BOOST_AUTO_TEST_SUITE_END() // connect_with_timeout_with_error_code



//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//



BOOST_FIXTURE_TEST_SUITE( cancel, Fixture )

// TODO
// BOOST_AUTO_TEST_CASE( happy_path )
//{
//}

BOOST_AUTO_TEST_SUITE_END() // connect_with_timeout_with_error_code


} // namespace test
} // namespace algorithms
} // namespace network
} // namespace gen_prog
