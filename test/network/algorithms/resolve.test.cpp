#define BOOST_TEST_MODULE gen_prog__network__algorithms__resolve
#include <boost/test/unit_test.hpp>



#include <ciso646>

#include <boost/asio/ts/internet.hpp>
#include <boost/asio/ts/io_context.hpp>
#include <boost/asio/ts/timer.hpp>
#include <boost/range/algorithm/count.hpp>

#include <turtle/mock.hpp>

#include <gen_prog/network/algorithms/resolve.hpp>



namespace gen_prog {
namespace network {
namespace algorithms {
namespace test {

struct Fixture
{
    using resolver_type = boost::asio::ip::tcp::resolver;


    ~Fixture()
    {
        _work_guard.reset();
        if ( _thread.joinable() ) { _thread.join(); }
    }

    boost::asio::io_context                                                    _io_context;
    boost::asio::executor_work_guard< boost::asio::io_context::executor_type > _work_guard =
        boost::asio::make_work_guard( _io_context );
    std::thread _thread{ [this]() { _io_context.run(); } };

    std::string _localhostName{ "localhost" };
    std::string _httpPort = "80";

    boost::asio::ip::address_v4 _localhostV4 = boost::asio::ip::address_v4::from_string( "127.0.0.1" );
    boost::asio::ip::address_v6 _localhostV6 = boost::asio::ip::address_v6::from_string( "::1" );

    boost::asio::ip::tcp::endpoint _httpLocalV4Endpoint{ _localhostV4, 80 };
    boost::asio::ip::tcp::endpoint _httpLocalV6Endpoint{ _localhostV6, 80 };

    resolver_type                      _resolver{ _io_context };
    boost::asio::high_resolution_timer _timer{ _io_context };
};

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

BOOST_FIXTURE_TEST_SUITE( apply_with_timeout, Fixture )

BOOST_AUTO_TEST_CASE( invalid_hostname )
{
    BOOST_CHECK_THROW( resolve( _resolver, _timer, "unknown.unknown", _httpPort, std::chrono::hours( 1 ) ),
                       boost::system::system_error );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( timeout )
{
    // Occasionally, timer is scheduled after resolve, so timeout is not triggered and test fail
    // do it 10 time so almost one will success as we want
    BOOST_CHECK_EXCEPTION(
        for ( int i = 0; i < 10; ++i ) {
            auto results = resolve( _resolver, _timer, _localhostName, _httpPort, std::chrono::nanoseconds( 0 ) );
        },
        boost::system::system_error,
        []( const boost::system::system_error & exception ) {
            return exception.code() == boost::asio::error::make_error_code( boost::asio::error::operation_aborted );
        } );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( happy_path )
{
    auto results = resolve( _resolver, _timer, _localhostName, _httpPort, std::chrono::hours( 1 ) );

    BOOST_TEST_REQUIRE( results.empty() == false );
    BOOST_TEST( ( ( boost::count( results, _httpLocalV4Endpoint ) >= 1 )
                  || ( boost::count( results, _httpLocalV6Endpoint ) >= 1 ) ) );
}

BOOST_AUTO_TEST_SUITE_END() // apply_with_timeout

////--------------------------------------------------------------------------------------------------------------------//
////--------------------------------------------------------------------------------------------------------------------//
////--------------------------------------------------------------------------------------------------------------------//

BOOST_FIXTURE_TEST_SUITE( apply_with_timeout_with_errorCode, Fixture )

BOOST_AUTO_TEST_CASE( invalid_hostname )
{
    boost::system::error_code errorCode;
    BOOST_CHECK_NO_THROW(
        resolve( _resolver, _timer, "unknown.unknown", _httpPort, std::chrono::hours( 1 ), errorCode ) );
    BOOST_CHECK( errorCode );
}

BOOST_AUTO_TEST_CASE( timeout )
{
    std::vector< boost::system::error_code > errorCodes{ 10 };

    // Occasionally, timer is scheduled after resolve, so timeout is not triggered and test fail
    // do it 10 time so almost one will success as we want
    for ( std::size_t i = 0; i < errorCodes.size(); ++i )
    {
        BOOST_CHECK_NO_THROW(
            resolve( _resolver, _timer, "unknown.unknown", _httpPort, std::chrono::nanoseconds( 0 ), errorCodes[i] ) );
    }

    BOOST_CHECK( std::any_of( errorCodes.begin(), errorCodes.end(), []( const auto & value ) {
        return value == boost::asio::error::make_error_code( boost::asio::error::operation_aborted );
    } ) );
}

BOOST_AUTO_TEST_CASE( happy_path )
{
    boost::system::error_code errorCode;
    auto results = resolve( _resolver, _timer, _localhostName, _httpPort, std::chrono::hours( 1 ), errorCode );

    BOOST_CHECK( not errorCode );
    BOOST_TEST_REQUIRE( results.empty() == false );
    BOOST_TEST( ( ( boost::count( results, _httpLocalV4Endpoint ) >= 1 )
                  || ( boost::count( results, _httpLocalV6Endpoint ) >= 1 ) ) );
}

BOOST_AUTO_TEST_SUITE_END() // apply_with_timeout_with_errorCode

////--------------------------------------------------------------------------------------------------------------------//
////--------------------------------------------------------------------------------------------------------------------//
////--------------------------------------------------------------------------------------------------------------------//

struct FixtureForAsyncCall : public Fixture
{

    using results_type    = resolver_type::results_type;
    using resolve_handler = std::function< void( const boost::system::error_code &, results_type ) >;

    resolve_handler getResolveHandler()
    {
        return [this]( const boost::system::error_code & errorCode_, results_type results ) {
            _errorCode = errorCode_;
            if ( not _errorCode ) { _results = results; }
            _promise.set_value();
        };
    }

    std::error_code      _errorCode;
    results_type         _results;
    std::promise< void > _promise;
};

BOOST_FIXTURE_TEST_SUITE( async_apply_with_timeout, FixtureForAsyncCall )

BOOST_AUTO_TEST_CASE( invalid_hostname )
{
    BOOST_CHECK_NO_THROW( async_resolve(
        _resolver, _timer, "unknown.unknown", _httpPort, std::chrono::hours( 1 ), getResolveHandler() ) );

    _promise.get_future().get();
    BOOST_CHECK( _errorCode );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( timeout )
{
    std::vector< std::error_code > errorCodes{ 10 };

    // Occasionally, timer is scheduled after resolve, so timeout is not triggered and test fail
    // do it 10 time so almost one will success as we want
    for ( std::size_t i = 0; i < errorCodes.size(); ++i )
    {
        _promise = std::promise< void >{};
        BOOST_CHECK_NO_THROW( async_resolve(
            _resolver, _timer, _localhostName, _httpPort, std::chrono::nanoseconds( 0 ), getResolveHandler() ) );
        _promise.get_future().get();

        errorCodes[i] = _errorCode;
    }

    BOOST_CHECK( std::any_of( errorCodes.begin(), errorCodes.end(), []( const auto & value ) {
        return value == boost::asio::error::make_error_code( boost::asio::error::operation_aborted );
    } ) );
}

//--------------------------------------------------------------------------------------------------------------------//

BOOST_AUTO_TEST_CASE( happy_path )
{
    BOOST_CHECK_NO_THROW(
        async_resolve( _resolver, _timer, _localhostName, _httpPort, std::chrono::hours( 1 ), getResolveHandler() ) );

    _promise.get_future().get();
    BOOST_REQUIRE( not _errorCode );
    BOOST_TEST_REQUIRE( _results.empty() == false );
    BOOST_TEST( ( ( boost::count( _results, _httpLocalV4Endpoint ) >= 1 )
                  || ( boost::count( _results, _httpLocalV6Endpoint ) >= 1 ) ) );
}

BOOST_AUTO_TEST_SUITE_END() // apply_with_timeout_with_error_code

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

BOOST_FIXTURE_TEST_SUITE( cancel, Fixture )

// TODO find a way to test this
// BOOST_FIXTURE_TEST_CASE( during_sync_resolve, Fixture )
//{
//    tcp_resolver resolver{ _io_context, "unknown.unknown", _httpPort };
//    std::thread  thread( [&resolver]() {
//        std::error_code errorCode;
//        resolver.apply( errorCode );

//        BOOST_CHECK( errorCode == boost::asio::error::make_error_code( boost::asio::error::operation_aborted ) );
//    } );

//    resolver.cancel();

//    if ( thread.joinable() ) { thread.join(); }
//}

BOOST_AUTO_TEST_SUITE_END() // cancel

} // namespace test
} // namespace algorithms
} // namespace network
} // namespace gen_prog
