#ifndef gen_prog__compare__functor_hpp
#define gen_prog__compare__functor_hpp



#include <boost/mpl/vector.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>



namespace gen_prog {
namespace compare {

template <typename AccessorT >
struct accessor_trait
{
    using accessor_type   = decltype(&AccessorT::operator());
//    static_assert(boost::function_types::function_arity<accessor_type>::value == 0, "require function with only 0 parameter");
//    static_assert(boost::function_types::function_arity<accessor_type>::value == 1, "require function with only one parameter");
    static_assert(boost::function_types::function_arity<accessor_type>::value == 2, "require function with only 2 parameter");

    using parameter_types = typename boost::function_types::parameter_types<accessor_type>;

    using value_type      = typename boost::mpl::at_c<parameter_types, 1>::type;
    using result_type     = typename boost::function_types::result_type<accessor_type>::type;

};

template <typename MemberAccessorT>
struct member_compare_functor
{
    using accessor_type = MemberAccessorT;
    using value_type = typename accessor_trait<accessor_type>::value_type;

    member_compare_functor(const accessor_type & accessor) : _accessor(accessor) {}

    int operator() (const value_type & lhs, const value_type & rhs) const
    {
        return compare(_accessor(lhs), _accessor(rhs));
    }

    accessor_type _accessor;
};

template <typename AccessorT>
member_compare_functor<AccessorT> make_member_compare_functor(const AccessorT & accessor)
{
    return member_compare_functor<AccessorT>(accessor);
}



} // namespace compare
} // namespace gen_prog

#endif // gen_prog__compare__functor_hpp
