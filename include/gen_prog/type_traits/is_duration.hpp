#ifndef gen_prog__type_traits__is_duration_hpp
#define gen_prog__type_traits__is_duration_hpp



#include <chrono>
#include <type_traits>



namespace gen_prog {
namespace type_traits {

template < typename Duration >
struct is_duration : std::false_type
{};

template < class Rep, class Period >
struct is_duration< std::chrono::duration< Rep, Period > > : std::true_type
{};

template < typename Duration >
using is_duration_t = typename is_duration<Duration>::type;

#if __cplusplus >= 201703L
template < typename Duration >
inline constexpr bool is_duration_v = is_duration< Duration >::value;
#endif

} // namespace type_traits
} // namespace gen_prog

#endif // gen_prog__type_traits__is_duration_hpp
