#ifndef gen_prog__network__algorithms__connect_hpp
#define gen_prog__network__algorithms__connect_hpp



#include <type_traits>

#include <boost/asio/ts/socket.hpp>

#include <gen_prog/network/algorithms/detail/connect_operator.hpp>



namespace gen_prog {
namespace network {
namespace algorithms {

template < typename Protocol, typename Timer, typename EndpointSequence, typename Duration >
typename Protocol::endpoint
connect( boost::asio::basic_socket< Protocol > & socket,
         Timer &                                 timer,
         const EndpointSequence &                endpoints,
         Duration                                duration,
         typename std::enable_if< boost::asio::is_endpoint_sequence< EndpointSequence >::value >::type * = 0 )
{
    boost::system::error_code ec;
    auto                      result = detail::make_connect_operator( socket, timer ).apply( endpoints, duration, ec );
    if ( ec ) { BOOST_THROW_EXCEPTION( boost::system::system_error( ec, "connect" ) ); }
    return result;
}

template < typename Protocol, typename Timer, typename EndpointSequence, typename Duration >
typename Protocol::endpoint
connect( boost::asio::basic_socket< Protocol > & socket,
         Timer &                                 timer,
         const EndpointSequence &                endpoints,
         Duration                                duration,
         boost::system::error_code &           ec,
         typename std::enable_if< boost::asio::is_endpoint_sequence< EndpointSequence >::value >::type * = 0 )
{
    return detail::make_connect_operator( socket, timer ).apply( endpoints, duration, ec );
}


template < typename Protocol, typename Timer, typename Iterator, typename Duration >
Iterator connect( boost::asio::basic_socket< Protocol > & socket,
                  Timer &                                 timer,
                  Iterator                                begin,
                  Duration                                duration,
                  typename std::enable_if< not boost::asio::is_endpoint_sequence< Iterator >::value >::type * = 0 )
{
    return connect( socket, timer, begin, Iterator{}, duration );
}

template < typename Protocol, typename Timer, typename Iterator, typename Duration >
Iterator connect( boost::asio::basic_socket< Protocol > & socket,
                  Timer &                                 timer,
                  Iterator                                begin,
                  Duration                                duration,
                  boost::system::error_code &           ec,
                  typename std::enable_if< not boost::asio::is_endpoint_sequence< Iterator >::value >::type * = 0 )
{
    return connect( socket, timer, begin, Iterator{}, duration, ec );
}

template < typename Protocol, typename Timer, typename Iterator, typename Duration >
Iterator connect( boost::asio::basic_socket< Protocol > & socket,
                  Timer &                                 timer,
                  Duration                                duration,
                  Iterator                                begin,
                  Iterator                                end )
{
    boost::system::error_code ec;
    auto                      result = detail::make_connect_operator( socket, timer ).apply( begin, end, duration, ec );
    if ( ec ) { BOOST_THROW_EXCEPTION( boost::system::system_error( ec, "connect" ) ); }
    return result;
}


template < typename Protocol, typename Timer, typename Iterator, typename Duration >
Iterator connect( boost::asio::basic_socket< Protocol > & socket,
                  Timer &                                 timer,
                  Iterator                                begin,
                  Iterator                                end,
                  Duration                                duration,
                  boost::system::error_code &           ec )
{
    return detail::make_connect_operator( socket, timer ).apply( begin, end, duration, ec );
}



template < typename Protocol,
           typename Timer,
           typename EndpointSequence,
           typename Duration,
           typename RangeConnectHandler >
void async_connect(
    boost::asio::basic_socket< Protocol > & socket,
    Timer &                                 timer,
    const EndpointSequence &                endpoints,
    Duration                                duration,
    RangeConnectHandler &&                  handler,
    typename std::enable_if< boost::asio::is_endpoint_sequence< EndpointSequence >::value >::type * = 0 )
{
    return detail::make_connect_operator( socket, timer )
        .async_apply( endpoints, duration, std::forward< RangeConnectHandler >( handler ) );
}

template < typename Protocol, typename Timer, typename Iterator, typename Duration, typename RangeConnectHandler >
void async_connect( boost::asio::basic_socket< Protocol > & socket,
                    Timer &                                 timer,
                    Iterator                                begin,
                    Duration                                duration,
                    RangeConnectHandler &&                  handler,
                    typename std::enable_if< not boost::asio::is_endpoint_sequence< Iterator >::value >::type * = 0 )
{
    return async_connect( socket, timer, begin, Iterator{}, duration, std::forward< RangeConnectHandler >( handler ) );
}

template < typename Protocol, typename Timer, typename Iterator, typename Duration, typename RangeConnectHandler >
void async_connect( boost::asio::basic_socket< Protocol > & socket,
                    Timer &                                 timer,
                    Iterator                                begin,
                    Iterator                                end,
                    Duration                                duration,
                    RangeConnectHandler &&                  handler )
{
    return async_connect( socket, timer, begin, end, duration, std::forward< RangeConnectHandler >( handler ) );
}

} // namespace algorithms

using algorithms::connect;
using algorithms::async_connect;

} // namespace network
} // namespace gen_prog

#endif // gen_prog__network__algorithms__connect_hpp
