#ifndef gen_prog__network__algorithms__resolve_hpp
#define gen_prog__network__algorithms__resolve_hpp



#include <boost/throw_exception.hpp>
#include <boost/utility/string_view.hpp>

#include <gen_prog/network/algorithms/detail/resolve_operator.hpp>



namespace gen_prog {
namespace network {
namespace algorithms {

template < class Resolver, class Timer, class Duration >
typename Resolver::results_type resolve( Resolver &               resolver,
                                         Timer &                  timer,
                                         boost::asio::string_view host,
                                         boost::asio::string_view service,
                                         Duration                 duration )
{
    boost::system::error_code ec;
    auto results = detail::make_resolve_operator( resolver, timer ).apply( host, service, duration, ec );
    if ( ec ) { BOOST_THROW_EXCEPTION( boost::system::system_error( ec, "resolve" ) ); }
    return results;
}

template < class Resolver, class Timer, class Duration >
typename Resolver::results_type resolve( Resolver &                  resolver,
                                         Timer &                     timer,
                                         boost::asio::string_view    host,
                                         boost::asio::string_view    service,
                                         Duration                    duration,
                                         boost::system::error_code & ec )
{
    return detail::make_resolve_operator( resolver, timer ).apply( host, service, duration, ec );
}

template < class Resolver, class Timer, class Duration >
typename Resolver::results_type resolve( Resolver &               resolver,
                                         Timer &                  timer,
                                         boost::asio::string_view host,
                                         boost::asio::string_view service,
                                         Duration                 duration,
                                         typename Resolver::flags resolve_flags )
{
    boost::system::error_code ec;
    auto results = detail::make_resolve_operator( resolver, timer ).apply( host, service, duration, resolve_flags, ec );
    if ( ec ) { BOOST_THROW_EXCEPTION( boost::system::system_error( ec, "resolve" ) ); }
    return results;
}

template < class Resolver, class Timer, class Duration >
typename Resolver::results_type resolve( Resolver &                  resolver,
                                         Timer &                     timer,
                                         boost::asio::string_view    host,
                                         boost::asio::string_view    service,
                                         Duration                    duration,
                                         typename Resolver::flags    resolve_flags,
                                         boost::system::error_code & ec )
{
    return detail::make_resolve_operator( resolver, timer ).apply( host, service, duration, resolve_flags, ec );
}

template < class Resolver, class Timer, class Duration, typename ResolveHandler >
void async_resolve( Resolver &               resolver,
                    Timer &                  timer,
                    boost::asio::string_view host,
                    boost::asio::string_view service,
                    Duration                 duration,
                    ResolveHandler &&        handler )
{
    return detail::make_resolve_operator( resolver, timer )
        .async_apply( host, service, duration, std::forward< ResolveHandler >( handler ) );
}

template < class Resolver, class Timer, class Duration, typename ResolveHandler >
void async_resolve( Resolver &               resolver,
                    Timer &                  timer,
                    boost::asio::string_view host,
                    boost::asio::string_view service,
                    Duration                 duration,
                    typename Resolver::flags resolve_flags,
                    ResolveHandler &&        handler )
{
    return detail::resolve_operator< Resolver, Timer >( resolver, timer )
        .async_apply( host, service, duration, resolve_flags, std::forward< ResolveHandler >( handler ) );
}

} // namespace algorithms

using algorithms::resolve;
using algorithms::async_resolve;

} // namespace network
} // namespace gen_prog

#endif // gen_prog__network__algorithms__resolve_hpp
