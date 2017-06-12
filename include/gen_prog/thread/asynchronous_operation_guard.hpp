#ifndef gen_prog__asynchronous_operation_guard_hpp
#define gen_prog__asynchronous_operation_guard_hpp



#include <atomic>
#include <exception>
#include <thread>
#include <stdexcept>



namespace gen_prog {
namespace thread {



///
/// \brief The asynchronous_operation_guard class is a conveniant class to implement asynchronous operation.
///
/// When you implement a class that run asynchronous operation, and you want to wait the end of the operation
/// to delete an instance of this class, asynchronous_operation_guard provide methods to do this.
/// And like the std::thread, asynchronous_operation_guard call std::terminate if it is delete if the operation
/// is still running.
///
/// asynchronous_operation_guard only store state (is_enable, is_running) of the async operation. This is your
/// responsability to maintaine this state up to date.
///
/// asynchronous_operation_guard allow you to wait the end of an operation, optionnaly with a timeout.
///
class asynchronous_operation_guard
{
public:
    ///
    /// \brief asynchronous_operation_guard create this class with "is_enable" to true and "is_running" to false
    ///
    inline asynchronous_operation_guard();

    ///
    /// \brief asynchronous_operation_guard create this class
    /// \param is_enable set the is_enable state
    /// \param is_running set the is_running state
    ///
    inline asynchronous_operation_guard(bool enabled, bool running);

    asynchronous_operation_guard(const asynchronous_operation_guard &) = delete;
    asynchronous_operation_guard(asynchronous_operation_guard &&) = delete;

    ///
    /// \brief ~asynchronous_operation_guard call std::terminate if the async operation is still running
    ///
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
    /// \brief is_enable check the enable status
    /// \return true if enable, false otherwise
    ///
    inline bool is_enable() const;
    [[deprecated]] inline bool enabled() const;

    ///
    /// \brief disable check the enable status
    /// \return true if not enable, false otherwise
    ///
    inline bool is_disable() const;



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
    /// \brief is_running check if this has begin, and not yet end
    /// \return true if running, false otherwise
    ///
    [[deprecated]] inline bool running() const;
    inline bool is_running() const;


    ///
    /// \brief wait_end sleep during "time" intervale while this is running
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
    std::atomic_bool _is_enabled;
    std::atomic_bool _is_running;
};



//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

asynchronous_operation_guard::asynchronous_operation_guard()
{
    _is_enabled.store(true);
    _is_running.store(false);
}

//--------------------------------------------------------------------------------------------------------------------//

asynchronous_operation_guard::asynchronous_operation_guard(bool enabled, bool running)
{
    _is_enabled.store(enabled);
    _is_running.store(running);
}

//--------------------------------------------------------------------------------------------------------------------//

asynchronous_operation_guard::~asynchronous_operation_guard()
{
    if (is_running())
    {
        std::terminate();
    }
}

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::enable() { _is_enabled.store(true); }

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::disable()   { _is_enabled.store(false); }

//--------------------------------------------------------------------------------------------------------------------//

bool asynchronous_operation_guard::enabled() const { return _is_enabled.load(); }
bool asynchronous_operation_guard::is_enable() const { return _is_enabled.load(); }
bool asynchronous_operation_guard::is_disable() const { return ! _is_enabled.load(); }

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::begin()
{
    throw_if_not_enable();
    _is_running.store(true);
}

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::end()   { _is_running.store(false); }

//--------------------------------------------------------------------------------------------------------------------//

bool asynchronous_operation_guard::is_running() const { return _is_running.load(); }

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
void asynchronous_operation_guard::wait_end(const std::chrono::duration<Rep, Period> & time)
{
    while(is_running()) { std::this_thread::sleep_for(time); }
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
bool asynchronous_operation_guard::wait(const std::chrono::duration<Rep, Period> & time)
{
    if (! is_running()) { return false; }

    std::this_thread::sleep_for(time);
    return is_running();
}

//--------------------------------------------------------------------------------------------------------------------//

void asynchronous_operation_guard::throw_if_not_enable() const
{
    if ( ! is_enable() )
    {
        throw std::runtime_error("async operation is disable.");
    }
}

} // namespace thread
} // namespace gen_prog

#endif // gen_prog__asynchronous_operation_guard_hpp
