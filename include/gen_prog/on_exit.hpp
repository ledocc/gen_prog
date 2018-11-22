#ifndef gen_prog__on_exit_hpp
#define gen_prog__on_exit_hpp

#warning "gen_prog/on_exit.hpp" is deprecated, use "gen_prog/utility/on_scope_exit.hpp" instead.

#include <gen_prog/utility/on_scope_exit.hpp>



namespace gen_prog
{

template <class CallableT>
using on_exit_operation = on_scope_exit_operation<CallableT>;

//--------------------------------------------------------------------------------------------------------------------//

template <typename CallableT>
[[deprecated]] on_exit_operation<CallableT> on_exit(const CallableT & call)
{
    return call;
}

} // namespace gen_prog

#endif // gen_prog__on_exit_hpp
