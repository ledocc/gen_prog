#ifndef gen_prog__compare__multi_order_step_hpp
#define gen_prog__compare__multi_order_step_hpp

#include <gen_prog/compare/functor.hpp>



namespace gen_prog {
namespace compare {

template <class OrderOperatorT, class CompareOperatorT >
struct multi_order_step
{
    using order_operator = OrderOperatorT;
    using compare_operator = CompareOperatorT;
    using value_type = typename compare_operator::value_type;

    bool operator() (const value_type & lhs, const value_type & rhs, bool & orderResult)
    {
        int compareResult = _compareOperator(lhs, rhs);
        if (0 == compareResult) return false;

        orderResult = _orderOperator(compareResult, 0);
        return true;
    }

    order_operator _orderOperator;
    compare_operator _compareOperator;
};


template <class OrderOperatorT, class AccessorT >
multi_order_step<OrderOperatorT, member_compare_functor<AccessorT> >
make_multi_order_step(OrderOperatorT orderOperator, AccessorT accessor)
{
    using multi_order_step_type = multi_order_step<OrderOperatorT, member_compare_functor<AccessorT> >;

    return multi_order_step_type{orderOperator, make_member_compare_functor(accessor)};
}

} // namespace compare
} // namespace gen_prog

#endif // gen_prog__compare__multi_order_step_hpp
