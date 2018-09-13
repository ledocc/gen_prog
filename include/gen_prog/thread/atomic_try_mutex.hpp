#ifndef gen_prog__thread__atomic_try_mutex_hpp
#define gen_prog__thread__atomic_try_mutex_hpp



#include <atomic>



namespace gen_prog {
namespace thread {

class atomic_try_mutex
{
public:
    bool try_lock() { return std::atomic_flag_test_and_set_explicit( &_flag, std::memory_order_acquire ) == false; }
    void unlock() { std::atomic_flag_clear_explicit( &_flag, std::memory_order_release ); }


private:
    std::atomic_flag _flag = ATOMIC_FLAG_INIT;
};

} // namespace thread
} // namespace gen_prog

#endif // gen_prog__thread__atomic_try_mutex_hpp
