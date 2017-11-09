#ifndef gen_prog__boost__filesystem__hash_h
#define gen_prog__boost__filesystem__hash_h



#include <functional>
#include <string>

#include <boost/filesystem/path.hpp>
#include <boost/functional/hash.hpp>



// custom specialization of std::hash<boost::filesystem::path>
namespace std
{
    template<> struct hash<boost::filesystem::path>
    {
        using argument_type = boost::filesystem::path;
        using result_type   = std::size_t;

        result_type operator()(const argument_type & p) const
        {
            return boost::filesystem::hash_value(p);
        }
    };
}

#endif // gen_prog__boost__filesystem__hash_h
