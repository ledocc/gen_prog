#ifndef gen_prog__async__operation_guard_hpp
#define gen_prog__async__operation_guard_hpp



#include <atomic>
#include <thread>



namespace gen_prog {
namespace async {

///
/// \brief The operation_guard class is a conveniant class to implement asynchronous operation.
///
/// An operation is a short time task.
///
///
/// operation_guard have a "running" state that define if the task is "work in progress". This the user responsability
/// to keep this state up to date.
///
/// MAIN FEATURE :
/// when operation_guard destructor is call, if the "running" state is true a call to std::terminate,
///
///




class operation_guard
{
public:
    struct set_running_guard
    {
        set_running_guard(operation_guard & op) : _op(op) {}
        ~set_running_guard() { _op.set_running(false); }

    private:
        operation_guard & _op;
    };


public:
    ///
    /// \brief operation_guard create an instance of operation_guard with "running" state to false
    ///
    operation_guard() = default;

    ///
    /// \brief operation_guard create an instance of operation_guard
    /// \param is_running_ set the "running" state
    ///
    inline operation_guard(bool is_running_);

    operation_guard(const operation_guard &) = delete;
    operation_guard(operation_guard &&) = delete;

    ///
    /// \brief ~operation_guard call std::terminate if the "running" state is true
    ///
    inline ~operation_guard();


    operation_guard & operator = (operation_guard &&) = delete;
    operation_guard & operator = (const operation_guard &) = delete;


    ///
    /// \brief is_running check the running status
    /// \return true if this operation is not finish, false otherwise
    ///
    inline bool is_running() const;

    ///
    /// \brief set_running define the runnin state
    /// \param running_
    ///
    inline void set_running(bool running_);


    ///
    /// \brief wait sleep during "time" intervale while this operation is running
    ///
    template<typename Rep, typename Period>
    void wait(const std::chrono::duration<Rep, Period> & time);

    ///
    /// \brief wait_for sleep during "time", if this operation is not finish
    ///  \return is_running() result
    ///
    template<typename Rep, typename Period>
    bool wait_for(const std::chrono::duration<Rep, Period> & time);


private:
    std::atomic_bool _is_running = ATOMIC_VAR_INIT(false);
};

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

operation_guard::operation_guard(bool is_running_)
{;
    _is_running.store(is_running_);
}

//--------------------------------------------------------------------------------------------------------------------//

operation_guard::~operation_guard()
{
    if (is_running()) { std::terminate(); }
}

//--------------------------------------------------------------------------------------------------------------------//

bool operation_guard::is_running() const
{
    return _is_running.load();
}

//--------------------------------------------------------------------------------------------------------------------//

void operation_guard::set_running(bool running_)
{
    _is_running.store(running_);
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
void operation_guard::wait(const std::chrono::duration<Rep, Period> & time)
{
    while(is_running()) { std::this_thread::sleep_for(time); }
}

//--------------------------------------------------------------------------------------------------------------------//

template<typename Rep, typename Period>
bool operation_guard::wait_for(const std::chrono::duration<Rep, Period> & time)
{
    if (! is_running()) { return false; }

    std::this_thread::sleep_for(time);
    return is_running();
}

} // namespace async
} // namespace gen_prog

#endif // gen_prog__async__operation_guard_hpp
