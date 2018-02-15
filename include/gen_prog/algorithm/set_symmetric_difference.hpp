#ifndef gen_prog__algorithm__set_symmetric_difference_hpp
#define gen_prog__algorithm__set_symmetric_difference_hpp



#include <algorithm>
#include <functional>
#include <utility>



namespace gen_prog {
namespace algorithm {

template<class InputIt1,  class InputIt2,
         class OutputIt1, class OutputIt2,
         class Compare1 = std::less<typename InputIt1::value_type>,
         class Compare2 = std::less<typename InputIt2::value_type> >
std::pair<OutputIt1, OutputIt2>
set_symmetric_difference( InputIt1 first1,    InputIt1 last1,
                          InputIt2 first2,    InputIt2 last2,
                          OutputIt1 d1_first, OutputIt2 d2_first,
                          Compare1 comp1 = Compare1(),
                          Compare2 comp2 = Compare2())
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

#endif // gen_prog__algorithm__set_symmetric_difference_hpp
