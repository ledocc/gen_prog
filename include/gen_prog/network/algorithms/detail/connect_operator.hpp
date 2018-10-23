#ifndef gen_prog__network__algorithms__detail__connect_operator_hpp
#define gen_prog__network__algorithms__detail__connect_operator_hpp



#include <vector>

#include <boost/asio/ts/executor.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/asio/ts/socket.hpp>

#include <gen_prog/network/algorithms/detail/operation.hpp>



namespace gen_prog {
namespace network {
namespace algorithms {
namespace detail {


template < typename Protocol, typename Timer >
class connect_operator : public detail::timeoutable_operation< Timer, connect_operator< Protocol, Timer > >
{
private:
    using base_class = detail::timeoutable_operation< Timer, connect_operator< Protocol, Timer > >;


public:
    using timer_type      = typename base_class::timer_type;
    using io_context_type = boost::asio::io_context;
    using socket_type     = boost::asio::basic_socket< Protocol >;
    using result_type     = typename Protocol::endpoint;
    using handler_type    = std::function< void( const boost::system::error_code &, const result_type & ) >;


public:
    connect_operator( socket_type & socket, timer_type & timer )
        : base_class( timer )
        , _socket( socket )
    {}


public:
    /// copy Constructor
    connect_operator( const connect_operator & other ) = delete;
    /// move Constructor
    connect_operator( connect_operator && other ) = default;

    /// Destructor
    ~connect_operator() = default;

    /// copy operator
    connect_operator & operator=( const connect_operator & other ) = delete;
    /// move operator
    connect_operator & operator=( connect_operator && other ) = delete;


    template < typename EndpointSequence, class Duration >
    result_type apply( const EndpointSequence & endpoints, Duration duration, boost::system::error_code & ec )
    {
        base_class::timer_expires_after( duration );

        return connect( endpoints, ec );
    }

    template < typename Iterator, class Duration >
    result_type apply( Iterator begin, Iterator end, Duration duration, boost::system::error_code & ec )
    {
        base_class::timer_expires_after( duration );

        return connect( begin, end, ec );
    }

    template < typename EndpointSequence, class Duration, typename RangeConnectHandler >
    result_type async_apply( const EndpointSequence & endpoints, Duration duration, RangeConnectHandler && handler )
    {
        base_class::timer_expires_after( duration );

        async_connect( endpoints, std::forward< RangeConnectHandler >( handler ) );
    }

    template < typename Iterator, class Duration, typename RangeConnectHandler >
    result_type async_apply( Iterator begin, Iterator end, Duration duration, RangeConnectHandler && handler )
    {
        base_class::timer_expires_after( duration );

        async_connect( begin, end, std::forward< RangeConnectHandler >( handler ) );
    }


private:
    template < typename EndpointSequence >
    result_type connect( const EndpointSequence & endpoints, boost::system::error_code & errorCode )
    {
        std::promise< void > promise;
        result_type          result;
        async_connect( endpoints,
                       [&promise, &errorCode, &result]( const boost::system::error_code & errorCode_,
                                                        const result_type &               result_ ) {
                           errorCode = errorCode_;
                           if ( not errorCode ) { result = result_; }
                           promise.set_value();
                       } );

        promise.get_future().get();
        base_class::cancel_timer();

        return result;
    }

    template < typename Iterator >
    result_type connect( Iterator begin, Iterator end, boost::system::error_code & errorCode )
    {
        std::promise< void > promise;
        result_type          result;
        async_connect( begin,
                       end,
                       [&promise, &errorCode, &result]( const boost::system::error_code & errorCode_,
                                                        const result_type &               result_ ) {
                           errorCode = errorCode_;
                           if ( not errorCode ) { result = result_; }
                           promise.set_value();
                       } );

        promise.get_future().get();
        base_class::cancel_timer();

        return result;
    }

    template < typename EndpointSequence, typename RangeConnectHandler >
    void async_connect( const EndpointSequence & endpoints, RangeConnectHandler && handler )
    {
        boost::asio::async_connect(
            _socket, endpoints, get_handler_that_cancel_timer( std::forward< RangeConnectHandler >( handler ) ) );
    }

    template < typename Iterator, typename RangeConnectHandler >
    void async_connect( Iterator begin, Iterator end, RangeConnectHandler && handler )
    {
        boost::asio::async_connect(
            _socket, begin, end, get_handler_that_cancel_timer( std::forward< RangeConnectHandler >( handler ) ) );
    }

    template < typename RangeConnectHandler >
    handler_type get_handler_that_cancel_timer( RangeConnectHandler && handler )
    {
        return [&timer = base_class::getTimer(), handler = std::move( handler )](
                   const boost::system::error_code & errorCode, const result_type & result ) mutable {
            timer.cancel();
            handler( errorCode, result );
        };
    }
    friend base_class;
    typename base_class::timer_handler_type get_timer_handler()
    {
        return [&socket = _socket]( const boost::system::error_code & errorCode ) {
            if ( errorCode ) { return; }
            socket.cancel();
        };
    }

private:
    socket_type & _socket;
};



template < typename Protocol, typename Timer >
connect_operator< Protocol, Timer > make_connect_operator( typename boost::asio::basic_socket< Protocol > & socket,
                                                           Timer &                                          timer )
{
    return connect_operator< Protocol, Timer >( socket, timer );
}

} // namespace detail
} // namespace algorithms
} // namespace network
} // namespace gen_prog

#endif // gen_prog__network__algorithms__detail__connect_operator_hpp
