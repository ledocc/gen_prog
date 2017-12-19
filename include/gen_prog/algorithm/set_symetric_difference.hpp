#ifndef gen_prog__algorithm__set_symetric_difference_hpp
#define gen_prog__algorithm__set_symetric_difference_hpp



#include <algorithm>
#include <functional>
#include <utility>



namespace gen_prog {
namespace algorithm {

template<class InputIt1,  class InputIt2,
         class OutputIt1, class OutputIt2,
         class Compare>
std::pair<OutputIt1, OutputIt2>
set_symetric_difference( InputIt1 first1,    InputIt1 last1,
                         InputIt2 first2,    InputIt2 last2,
                         OutputIt1 d1_first, OutputIt2 d2_first,
                         Compare comp1 = std::less<InputIt1>(),
                         Compare comp2 = std::less<InputIt2>())
{
    while (first1 != last1)
    {
        if (first2 == last2)
        {
            return std::make_pair(std::copy(first1, last1, d1_first),
                                  d2_first);
        }

        if (comp1(*first1, *first2))
        {
            *d1_first++ = *first1++;
        }
        else if (comp2(*first2, *first1))
        {
            *d2_first++ = *first2++;
        }
        else
        {
            ++first1;
            ++first2;
        }
    }

    if (first2 != last2)
    {
        return std::make_pair(d1_first, std::copy(first2, last2, d2_first));
    }

    return std::make_pair(d1_first, d2_first);
}

} // namespace algorithm
} // namespace gen_prog

#endif // gen_prog__algorithm__set_symetric_difference_hpp
