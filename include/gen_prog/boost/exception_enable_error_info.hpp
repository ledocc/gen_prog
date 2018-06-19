#ifndef gen_prog__boost__exception_enable_error_info_hpp
#define gen_prog__boost__exception_enable_error_info_hpp



#include <boost/exception/enable_error_info.hpp>



namespace boost
{
    template<typename T>
    using boost_exception_enable_error_info_t = typename boost::exception_detail::enable_error_info_return_type< T >::type;
}

#endif // ** gen_prog__boost__exception_enable_error_info_hpp ** //
