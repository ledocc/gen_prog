#ifndef gen_prog__on_scope_exit_hpp
#define gen_prog__on_scope_exit_hpp



namespace gen_prog {

template <typename CallableT>
class on_scope_exit_operation
{
private:
    using this_type = on_scope_exit_operation<CallableT>;


public:
    on_scope_exit_operation() = default;
    on_scope_exit_operation(const CallableT & call)
        : _valid(true)
        , _call(call)
    {}

    on_scope_exit_operation(const this_type & other) = delete;
    on_scope_exit_operation(this_type && other)
        : on_scope_exit_operation( std::move( other._call ) )
    {
        other._valid = false;
    }

    ~on_scope_exit_operation()
    {
        if ( _valid ) { _call(); }
    }


    this_type operator = (const this_type & other) = delete;
    this_type & operator = (this_type && other)
    {
        _call = std::move( other._call );
        other._valid = false;
        _valid = true;
        return *this;
    }


private:
    bool _valid = false;
    CallableT _call;
};

//--------------------------------------------------------------------------------------------------------------------//

template <typename CallableT>
on_scope_exit_operation<CallableT> on_scope_exit(const CallableT & call)
{
    return call;
}

} // namespace gen_prog

#endif // gen_prog__on_scope_exit_hpp
