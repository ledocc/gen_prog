#ifndef gen_prog__utility__version_hpp
#define gen_prog__utility__version_hpp



#include <iostream>

#include <boost/operators.hpp>



namespace gen_prog {
namespace utility {

/// simple_version template with major, minor, patch value.

template < typename T >
class simple_version : boost::totally_ordered< simple_version< T > >
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


    bool operator==( const simple_version & other ) const;
    bool operator<( const simple_version & other ) const;


    value_type get_major() const { return _major; }
    void       set_major( value_type major ) { _major = major; }

    value_type get_minor() const { return _minor; }
    void       set_minor( value_type minor ) { _minor = minor; }

    value_type get_patch() const { return _patch; }
    void       set_patch( value_type patch ) { _patch = patch; }

    void set( value_type major, value_type minor = 0, value_type patch = 0 )
    {
        set_major( major );
        set_minor( minor );
        set_patch( patch );
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
bool simple_version<T>::operator==( const simple_version & other ) const
{
    return ( _major == other._major ) && ( _minor == other._minor ) && ( _patch == other._patch );
}

template < typename T >
bool simple_version<T>::operator<( const simple_version & other ) const
{
    if ( _major != other._major ) { return _major < other._major; }
    if ( _minor != other._minor ) { return _minor < other._minor; }
    if ( _patch != other._patch ) { return _patch < other._patch; }

    return false;
}



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


    os << static_cast< output_type >( version.get_major() );

    if ( os.precision() > 1 ) { os << "." << static_cast< output_type >( version.get_minor() ); }

    if ( os.precision() > 2 ) { os << "." << static_cast< output_type >( version.get_patch() ); }

    return os;
}

} // namespace utility

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

template <typename T>
using simple_version = utility::simple_version<T>;

} // namespace gen_prog

#endif // gen_prog__utility__version_hpp
