#ifndef gen_prog__asynchronous_operation_guard_hpp
#define gen_prog__asynchronous_operation_guard_hpp



#include <atomic>
#include <exception>
#include <thread>
#include <stdexcept>



namespace gen_prog {
namespace thread {


class asynchronous_operation_guard
{
public:
    inline asynchronous_operation_guard();
    inline asynchronous_operation_guard(bool enabled, bool running);

    asynchronous_operation_guard(const asynchronous_operation_guard &) = delete;
    asynchronous_operation_guard(asynchronous_operation_guard &&) = delete;

    inline ~asynchronous_operation_guard();


    asynchronous_operation_guard & operator = (asynchronous_operation_guard &&) = delete;
    asynchronous_operation_guard & operator = (const asynchronous_operation_guard &) = delete;


    ///
    /// \brief enable allow async operation to running
    inline void enable();
    ///
    /// \brief disable disallow async operation to running
    ///
    inline void disable();

    ///
    /// \brief enabled check the enable status
    /// \return true if enable, false otherwise
    ///
    inline bool enabled() const;



    ///
    /// \brief begin the async operation
    /// \throw std::runtime_error if disable
    ///
    inline void begin();

    ///
    /// \brief end the async operation
    ///
    inline void end();

    ///
    /// \brief running check if this has begin, and not yet end
    /// \return true if running, false otherwise
    ///
    inline bool running() const;


    ///
    /// \brief wait_end sleep during "time" while this is running
    ///
    template<typename Rep, typename Period>
    void wait_end(const std::chrono::duration<Rep, Period> & time);

    ///
    /// \brief wait sleep during "time" if this is running
    ///
    template<typename Rep, typename Period>
    bool wait(const std::chrono::duration<Rep, Period> & time);


private:
    inline void throw_if_not_enable() const;


private:
    std::atomic_bool _enabled;
    std::atomic_bool _running;
};



//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

asynchronous_operation_guard::asynchronous_operation_guard()
{
    _enabled.store(true);
    _running.store(false);
}

//--------------------------------------------------------------------------------------------------------------------//

asynchronous_operation_guard::asynchronous_operation_guard(bool enabled, bool running)
{
    _enabled.store(enabled);
    _running.store(running);
}

//--------------------------------------------------------------------------------------------------------------------//

asynchronous_operation_guard::~asynchronous_operation_guard()
{
    if (running())
    {
        std::terminate();
    }
}

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::enable() { _enabled.store(true); }

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::disable()   { _enabled.store(false); }

//--------------------------------------------------------------------------------------------------------------------//

bool asynchronous_operation_guard::enabled() const { return _enabled.load(); }

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::begin()
{
    throw_if_not_enable();
    _running.store(true);
}

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::end()   { _running.store(false); }

//--------------------------------------------------------------------------------------------------------------------//

bool asynchronous_operation_guard::running() const { return _running.load(); }

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
void asynchronous_operation_guard::wait_end(const std::chrono::duration<Rep, Period> & time)
{
    while(running()) { std::this_thread::sleep_for(time); }
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
bool asynchronous_operation_guard::wait(const std::chrono::duration<Rep, Period> & time)
{
    if (running()) { std::this_thread::sleep_for(time); }
    return running();
}

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::throw_if_not_enable() const
{
    if ( ! enabled() )
    {
        throw std::runtime_error("async operation is disable.");
    }
}

} // namespace thread
} // namespace gen_prog

#endif // gen_prog__asynchronous_operation_guard_hpp
