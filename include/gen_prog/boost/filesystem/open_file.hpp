#ifndef gen_prog__filesystem__open_file_hpp
#define gen_prog__filesystem__open_file_hpp



#include <ciso646>

#include <boost/filesystem.hpp>



namespace gen_prog {
namespace filesystem {

namespace detail {

inline void test_perms_file(const boost::filesystem::file_status & fileStatus,
                            boost::filesystem::perms permissions,
                            boost::system::error_code & errorCode)
{
    using namespace boost::filesystem;

    if ( ( fileStatus.permissions() & permissions ) == no_perms )
    {
        errorCode = boost::system::error_code(boost::system::errc::permission_denied,
                                       boost::system::system_category());
    }
}

inline void test_read_file(const boost::filesystem::file_status & fileStatus,
                           boost::system::error_code & errorCode)
{
    using namespace boost::filesystem;

    perms readPermissions =
          owner_read
        | group_read
        | others_read;

    test_perms_file(fileStatus, readPermissions, errorCode);
}

inline void test_write_file(const boost::filesystem::file_status & fileStatus,
                            boost::system::error_code & errorCode)
{
    using namespace boost::filesystem;

    perms writePermissions =
          owner_write
        | group_write
        | others_write;

    test_perms_file(fileStatus, writePermissions, errorCode);
}

} // namespace detail


//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//


inline void test_read_file(const boost::filesystem::path & path, boost::system::error_code & errorCode)
{
    using namespace boost::filesystem;

    file_status fileStatus = status(path, errorCode);
    if ( errorCode ) { return; }

    detail::test_read_file( fileStatus, errorCode );
}

//--------------------------------------------------------------------------------------------------------------------//

inline void test_read_file(const boost::filesystem::path & path)
{
    boost::system::error_code errorCode;
    test_read_file(path, errorCode);
    if ( not errorCode ) { return; }

    BOOST_THROW_EXCEPTION( boost::filesystem::filesystem_error( "test_read_file", path, errorCode ) );
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

inline void test_write_file(const boost::filesystem::path & path,
                            boost::system::error_code & errorCode)
{
    using namespace boost::filesystem;

    file_status fileStatus = status(path);
    if ( errorCode ) { return; }

    detail::test_write_file( fileStatus, errorCode );
}

//--------------------------------------------------------------------------------------------------------------------//

inline void test_write_file(const boost::filesystem::path & path)
{
    boost::system::error_code errorCode;
    test_write_file(path, errorCode);
    if ( not errorCode ) { return; }

    BOOST_THROW_EXCEPTION( boost::filesystem::filesystem_error( "test_write_file", path, errorCode ) );
}

//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

inline void test_open_file(const boost::filesystem::path & path,
                           std::ios_base::openmode mode,
                           boost::system::error_code & errorCode)
{
    using namespace boost::filesystem;

    file_status fileStatus = status(path);
    if ( errorCode ) { return; }

    if ( mode & std::ios_base::in )
    {
        detail::test_read_file( fileStatus, errorCode );
        if ( errorCode ) { return; }
    }

    if ( mode & std::ios_base::out )
    {
        detail::test_write_file( fileStatus, errorCode );
        if ( errorCode ) { return; }
    }
}

//--------------------------------------------------------------------------------------------------------------------//

inline void test_open_file(const boost::filesystem::path & path, std::ios_base::openmode mode)
{
    boost::system::error_code errorCode;
    test_open_file(path, mode, errorCode);
    if ( not errorCode ) { return; }

    BOOST_THROW_EXCEPTION( boost::filesystem::filesystem_error( "test_open_file", path, errorCode ) );
}

} // namespace filesystem
} // namespace gen_prog


#endif // gen_prog__filesystem__open_file_hpp
