#ifndef gen_prog__async__job_guard_hpp
#define gen_prog__async__job_guard_hpp



#include <atomic>
#include <exception>
#include <thread>

#include <gen_prog/async/operation_guard.hpp>



namespace gen_prog {
namespace async {

///
/// \brief The job_guard class is a conveniant class to implement asynchronous job.
///
/// A job is an long time task that can be enabled/disabled.
///
///
/// operation_guard have a "running" state that define if the task is "work in progress". This the user responsability
/// to keep this state up to date.
///
/// MAIN FEATURE :
/// when operation_guard destructor is call, if the "running" state is true a call to std::terminate,
///

class job_guard : private operation_guard
{
public:
    ///
    /// \brief job_guard create an instance of job_guard with "running" state to false and "enable" state to true.
    ///
    job_guard() = default;

    ///
    /// \brief job_guard create an instance of job_guard
    /// \param is_enable set the enable state
    /// \param is_running set the running state
    ///
    inline job_guard(bool is_enable_, bool is_running_);

    job_guard(const job_guard &) = delete;
    job_guard(job_guard &&) = delete;

    ///
    /// \brief ~job_guard call std::terminate if the async operation is still running
    ///
    ~job_guard() = default;


    job_guard & operator = (job_guard &&) = delete;
    job_guard & operator = (const job_guard &) = delete;


    ///
    /// \brief set_enable define the "enable" status
    /// \param enable status
    ///
    inline void set_enable(bool enable);
    ///
    /// \brief enable allow async operation to running
    ///
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
    ///
    /// \brief disable check the enable status
    /// \return true if not enable, false otherwise
    ///
    inline bool is_disable() const;


    ///
    /// \brief is_running check the running status
    /// \return true if this job is not finish, false otherwise
    ///
    inline bool is_running() const;


    ///
    /// \brief begin the async job
    /// \throw std::runtime_error if is_disable() return true
    ///
    inline void begin();

    ///
    /// \brief end the async job
    ///
    inline void end();



    ///
    /// \brief wait sleep during "time" intervale while this job is running
    ///
    template<typename Rep, typename Period>
    void wait(const std::chrono::duration<Rep, Period> & time);

    ///
    /// \brief wait_for sleep during "time", if this job is not finish
    ///  \return is_running() result
    ///
    template<typename Rep, typename Period>
    bool wait_for(const std::chrono::duration<Rep, Period> & time);


private:
    inline void throw_if_not_enable() const;


private:
    std::atomic_bool _is_enabled = ATOMIC_VAR_INIT(true);
};

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

job_guard::job_guard(bool is_enable_, bool is_running_)
    : operation_guard(is_running_)
{
    set_enable(is_enable_);
}

//--------------------------------------------------------------------------------------------------------------------//

void job_guard::set_enable(bool enable)
{
    _is_enabled.store(enable);
}

//--------------------------------------------------------------------------------------------------------------------//

void job_guard::enable()
{
    set_enable(true);
}

//--------------------------------------------------------------------------------------------------------------------//

void job_guard::disable()
{
    set_enable(false);
}

//--------------------------------------------------------------------------------------------------------------------//

bool job_guard::is_enable() const
{
    return _is_enabled.load();
}

//--------------------------------------------------------------------------------------------------------------------//

bool job_guard::is_disable() const
{
    return ! is_enable();
}

//--------------------------------------------------------------------------------------------------------------------//

void job_guard::begin()
{
    throw_if_not_enable();
    set_running(true);
}

//--------------------------------------------------------------------------------------------------------------------//

void job_guard::end()
{
    set_running(false);
}

//--------------------------------------------------------------------------------------------------------------------//

bool job_guard::is_running() const
{
    return operation_guard::is_running();
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
void job_guard::wait(const std::chrono::duration<Rep, Period> & time)
{
    return operation_guard::wait(time);
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
bool job_guard::wait_for(const std::chrono::duration<Rep, Period> & time)
{
    return operation_guard::wait_for(time);
}

//--------------------------------------------------------------------------------------------------------------------//

void job_guard::throw_if_not_enable() const
{
    if ( is_enable() ) { return; }

    throw std::runtime_error("async job is disable.");
}

} // namespace async
} // namespace gen_prog

#endif // gen_prog__async__job_guard_hpp
