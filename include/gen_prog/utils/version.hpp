#ifndef gen_prog__utils__version_hpp
#define gen_prog__utils__version_hpp



#include <iostream>



namespace gen_prog {
namespace utils {

/// simple_version template with major, minor, patch value.

template < typename T >
class simple_version
{
public:
    using value_type = T;


public:
    simple_version() = default;
    simple_version( value_type major, value_type minor = 0, value_type patch = 0 )
        : _major( major )
        , _minor( minor )
        , _patch( patch )
    {}


    value_type getMajor() const { return _major; }
    void       setMajor( value_type major ) { _major = major; }

    value_type getMinor() const { return _minor; }
    void       setMinor( value_type minor ) { _minor = minor; }

    value_type getPatch() const { return _patch; }
    void       setPatch( value_type patch ) { _patch = patch; }

    void set( value_type major, value_type minor = 0, value_type patch = 0 )
    {
        setMajor( major );
        setMinor( minor );
        setPatch( patch );
    }


private:
    value_type _major = 0;
    value_type _minor = 0;
    value_type _patch = 0;
};

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

template < typename T >
std::ostream & operator<<( std::ostream & os, const simple_version< T > & version )
{
    using is_char  = std::is_same< T, char >;
    using is_uchar = std::is_same< T, unsigned char >;

    // clang-format off
    using output_type = std::conditional_t< is_char::value,
                                                short,
                                                std::conditional_t< is_uchar::value,
                                                                        unsigned short,
                                                                        T
                                                                  >
                                          >;
    // clang-format on


    os << static_cast< output_type >( version.getMajor() );

    if ( os.precision() > 1 ) { os << "." << static_cast< output_type >( version.getMinor() ); }

    if ( os.precision() > 2 ) { os << "." << static_cast< output_type >( version.getPatch() ); }

    return os;
}

} // namespace utils

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

template <typename T>
using simple_version = utils::simple_version<T>;

} // namespace gen_prog

#endif // gen_prog__utils__version_hpp
