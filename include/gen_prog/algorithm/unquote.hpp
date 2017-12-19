#ifndef gen_prog__algorithm__unquote_hpp
#define gen_prog__algorithm__unquote_hpp



#include <string>

#include <boost/numeric/conversion/cast.hpp>



namespace gen_prog {
namespace algorithm {

inline void unquote(std::string & str)
{
    using difference_type = std::string::iterator::difference_type;

    if ( str.size() <= 2 ) { return; }
    if ( ( str.front() == '"') && ( str.back() == '"') )
    {
        str.erase( str.begin() );
        str.erase( std::next( str.begin(), boost::numeric_cast<difference_type>( str.size() - 1 ) ) );
    }
}

} // namespace algorithm
} // namespace gen_prog

#endif // gen_prog__algorithm__unquote_hpp
