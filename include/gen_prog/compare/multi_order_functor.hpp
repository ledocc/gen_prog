#ifndef gen_prog__compare__multi_order_functor_hpp
#define gen_prog__compare__multi_order_functor_hpp



#include <type_traits>



namespace gen_prog {
namespace compare {


template <class MultiOrderStepT1, class MultiOrderStepT2>
struct multi_order_functor
{
    using multi_order_step_1 = MultiOrderStepT1;
    using multi_order_step_2 = MultiOrderStepT2;

    using value_type = typename multi_order_step_1::value_type;


    static_assert(std::is_same<typename multi_order_step_1::value_type,
                               typename multi_order_step_2::value_type>::value,
                  "use multi_order_step with differente value_type");


    multi_order_functor(const multi_order_step_1 & multiOrderStep1,
                        const multi_order_step_2 & multiOrderStep2) :
        _multiOrderStep1(multiOrderStep1),
        _multiOrderStep2(multiOrderStep2)
    {}

    int operator() (const value_type & lhs, const value_type & rhs)
    {
        bool result = false;

        if (_multiOrderStep1(lhs, rhs, result)) return result;
        if (_multiOrderStep2(lhs, rhs, result)) return result;

        return result;
    }

    multi_order_step_1 _multiOrderStep1;
    multi_order_step_2 _multiOrderStep2;
};


template <class... MultiOrderStep>
multi_order_functor<MultiOrderStep...>
make_multi_order_functor(MultiOrderStep... args)
{
    return multi_order_functor<MultiOrderStep...>(args...);
}

} // namespace compare
} // namespace gen_prog

#endif // gen_prog__compare__multi_order_functor_hpp
