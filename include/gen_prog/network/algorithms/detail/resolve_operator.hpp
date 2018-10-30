#ifndef gen_prog__network__algorithms__detail__resolve_operator_hpp
#define gen_prog__network__algorithms__detail__resolve_operator_hpp



#include <boost/asio/ts/executor.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/asio/detail/string_view.hpp>

#include <gen_prog/network/algorithms/detail/operation.hpp>



namespace gen_prog {
namespace network {
namespace algorithms {
namespace detail {


template < class Resolver, class Timer >
class resolve_operator : public detail::timeoutable_operation< Timer, resolve_operator< Resolver, Timer > >
{
private:
    using base_class = detail::timeoutable_operation< Timer, resolve_operator< Resolver, Timer > >;


public:
    using io_context_type = boost::asio::io_context;
    using resolver_type   = Resolver;
    using results_type    = typename resolver_type::results_type;
    using handler_type    = std::function< void( const boost::system::error_code &, results_type ) >;


public:
    resolve_operator( Resolver & resolver, Timer & timer )
        : base_class( timer )
        , _resolver( resolver )
    {}

    /// copy Constructor
    resolve_operator( const resolve_operator & other ) = delete;
    /// move Constructor
    resolve_operator( resolve_operator && other ) = default;

    /// Destructor
    ~resolve_operator() = default;

    /// copy operator
    resolve_operator & operator=( const resolve_operator & other ) = delete;
    /// move operator
    resolve_operator & operator=( resolve_operator && other ) = default;


    template < class Duration >
    results_type apply( BOOST_ASIO_STRING_VIEW_PARAM    host,
                        BOOST_ASIO_STRING_VIEW_PARAM    service,
                        Duration                    duration,
                        boost::system::error_code & ec )
    {
        base_class::timer_expires_after( duration );

        return resolve( host, service, ec );
    }

    template < class Duration >
    results_type apply( BOOST_ASIO_STRING_VIEW_PARAM    host,
                        BOOST_ASIO_STRING_VIEW_PARAM    service,
                        Duration                    duration,
                        typename Resolver::flags    resolve_flags,
                        boost::system::error_code & ec )
    {
        base_class::timer_expires_after( duration );

        return resolve( host, service, resolve_flags, ec );
    }

    template < class Duration, typename ResolveHandler >
    void async_apply( BOOST_ASIO_STRING_VIEW_PARAM host,
                      BOOST_ASIO_STRING_VIEW_PARAM service,
                      Duration                 duration,
                      ResolveHandler &&        handler )
    {
        base_class::timer_expires_after( duration );

        async_resolve( host, service, std::forward< ResolveHandler >( handler ) );
    }

    template < class Duration, typename ResolveHandler >
    void async_apply( BOOST_ASIO_STRING_VIEW_PARAM host,
                      BOOST_ASIO_STRING_VIEW_PARAM service,
                      Duration                 duration,
                      typename Resolver::flags resolve_flags,
                      ResolveHandler &&        handler )
    {
        base_class::timer_expires_after( duration );

        async_resolve( host, service, resolve_flags, std::forward< ResolveHandler >( handler ) );
    }


private:
    results_type
    resolve( BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service, boost::system::error_code & errorCode )
    {
        std::promise< void > promise;
        results_type         results;
        async_resolve(
            host,
            service,
            [&promise, &errorCode, &results]( const boost::system::error_code & errorCode_, results_type results_ ) {
                errorCode = errorCode_;
                results   = results_;
                promise.set_value();
            } );

        promise.get_future().get();
        base_class::cancel_timer();

        return results;
    }

    results_type resolve( BOOST_ASIO_STRING_VIEW_PARAM    host,
                          BOOST_ASIO_STRING_VIEW_PARAM    service,
                          typename Resolver::flags    resolve_flags,
                          boost::system::error_code & errorCode )
    {
        std::promise< void > promise;
        results_type         results;
        async_resolve(
            host,
            service,
            resolve_flags,
            [&promise, &errorCode, &results]( const boost::system::error_code & errorCode_, results_type results_ ) {
                errorCode = errorCode_;
                results   = results_;
                promise.set_value();
            } );

        promise.get_future().get();
        base_class::cancel_timer();

        return results;
    }

    template < typename ResolveHandler >
    void async_resolve( BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service, ResolveHandler && handler )
    {
        _resolver.async_resolve(
            host, service, get_handler_that_cancel_timer( std::forward< ResolveHandler >( handler ) ) );
    }

    template < typename ResolveHandler >
    void async_resolve( BOOST_ASIO_STRING_VIEW_PARAM host,
                        BOOST_ASIO_STRING_VIEW_PARAM service,
                        typename Resolver::flags resolve_flags,
                        ResolveHandler &&        handler )
    {
        _resolver.async_resolve(
            host, service, resolve_flags, get_handler_that_cancel_timer( std::forward< ResolveHandler >( handler ) ) );
    }

    template < typename ResolveHandler >
    handler_type get_handler_that_cancel_timer( ResolveHandler && handler )
    {
        return [&timer = base_class::getTimer(), handler = std::move( handler )](
                   const boost::system::error_code & errorCode, results_type results ) mutable {
            timer.cancel();
            handler( errorCode, results );
        };
    }

    friend base_class;
    typename base_class::timer_handler_type get_timer_handler()
    {
        return [&resolver = _resolver]( const std::error_code & errorCode ) {
            if ( errorCode ) { return; }
            resolver.cancel();
        };
    }

private:
    resolver_type & _resolver;
};



template < class Resolver, class Timer >
resolve_operator< Resolver, Timer > make_resolve_operator( Resolver & resolver, Timer & timer )
{
    return resolve_operator< Resolver, Timer >( resolver, timer );
}

} // namespace detail
} // namespace algorithms
} // namespace network
} // namespace gen_prog

#endif // gen_prog__network__algorithms__detail__resolve_operator_hpp
