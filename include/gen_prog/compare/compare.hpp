#ifndef gen_prog__compare__compare_hpp
#define gen_prog__compare__compare_hpp

namespace gen_prog {
namespace compare {

template <typename T>
int compare(const T & lhs, const T & rhs)
{
    if      (lhs > rhs)  { return  1; }
    else if (lhs < rhs)  { return -1; }
    else                 { return  0; }
}

} // namespace compare
} // namespace gen_prog

#endif // gen_prog__compare__compare_hpp
