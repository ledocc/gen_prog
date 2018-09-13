#define BOOST_TEST_MODULE gen_prog__thread__atomic_try_mutex
#include <boost/test/unit_test.hpp>



#include <gen_prog/thread/atomic_try_mutex.hpp>



namespace gen_prog {
namespace thread {
namespace test {


BOOST_AUTO_TEST_CASE( try_lock )
{
    atomic_try_mutex lock;

    BOOST_TEST( lock.try_lock() );
    BOOST_TEST( lock.try_lock() == false );
}

BOOST_AUTO_TEST_CASE( try_lock__then__unlock )
{
    atomic_try_mutex lock;

    BOOST_TEST( lock.try_lock() );
}

} // namespace test
} // namespace thread
} // namespace gen_prog
