#ifndef gen_prog__on_exit_hpp
#define gen_prog__on_exit_hpp



namespace gen_prog {

template <typename CallableT>
class on_scope_exit_operation
{
    using this_type = on_scope_exit_operation<CallableT>;


public:
    on_scope_exit_operation() = default;
    on_scope_exit_operation(const CallableT & call) : _call(call) {}

    on_scope_exit_operation(const this_type & other) = delete;
    on_scope_exit_operation(this_type && other) : _call(std::move(other._call)) { other._toCall = false; }

    ~on_scope_exit_operation() { _call(); }


    this_type operator = (const this_type & other) = delete;
    this_type & operator = (this_type && other)
    {
        _call = std::move(other._call);
        other._toCall = false;
        _toCall = true;
        return *this;
    }


private:
    bool _toCall = true;
    CallableT _call;
};

template <class CallableT>
using on_exit_operation = on_scope_exit_operation<CallableT>;


//--------------------------------------------------------------------------------------------------------------------//


template <typename CallableT>
[[deprecated]] on_scope_exit_operation<CallableT> on_exit(const CallableT & call)
{
    return call;
}

//--------------------------------------------------------------------------------------------------------------------//

template <typename CallableT>
on_scope_exit_operation<CallableT> on_scope_exit(const CallableT & call)
{
    return call;
}

} // namespace gen_prog

#endif // gen_prog__on_exit_hpp
