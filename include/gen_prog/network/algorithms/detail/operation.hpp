#ifndef gen_prog__network__timeoutable_operation_h
#define gen_prog__network__timeoutable_operation_h



#include <chrono>

#include <boost/asio/ts/io_context.hpp>
#include <boost/asio/ts/timer.hpp>



namespace gen_prog {
namespace network {
namespace algorithms {
namespace detail {

template < class Timer, typename Derived >
class timeoutable_operation
{
private:
    using timer_handler_type = std::function< void( const boost::system::error_code & errorCode ) >;


public:
    using timer_type = Timer;


private:
    friend Derived;
    timeoutable_operation( timer_type & timer )
        : _timer( timer )
    {}


public:
    /// copy Constructor
    timeoutable_operation( const timeoutable_operation & other ) = delete;
    /// move Constructor
    timeoutable_operation( timeoutable_operation && other ) = default;

    /// Destructor
    ~timeoutable_operation() = default;


    /// copy operator
    timeoutable_operation & operator=( const timeoutable_operation & other ) = delete;
    /// move operator
    timeoutable_operation & operator=( timeoutable_operation && other ) = default;


protected:
    void cancel_timer() { _timer.cancel(); }

    template < typename Duration >
    void timer_expires_after( Duration timeout )
    {
        _timer.expires_after( timeout );
        async_wait_then_cancel();
    }

    void timer_expires_at( const std::chrono::high_resolution_clock::time_point & timeout )
    {
        _timer.expires_at( timeout );
        async_wait_then_cancel();
    }

    timer_type & getTimer() const { return _timer; }


private:
    void async_wait_then_cancel() { _timer.async_wait( static_cast< Derived * >( this )->get_timer_handler() ); }

private:
    timer_type & _timer;
};

} // namespace detail
} // namespace algorithms
} // namespace network
} // namespace gen_prog

#endif // gen_prog__network__timeoutable_operation_h
