#ifndef gen_prog__source_location_hpp
#define gen_prog__source_location_hpp



#include <cstdint>
#include <string>

#include <boost/current_function.hpp>



namespace gen_prog {

class source_location
{
public:
    source_location() {}
    source_location(const std::string & function_name,
                    const std::string & file_name,
                    std::uint_least32_t line):
        _function_name(function_name),
        _file_name(file_name),
        _line(line)
    {}


    const std::string & function_name() const { return _function_name; }
    const std::string & file_name() const { return _file_name; }
    std::uint_least32_t  line() const { return _line; }


private:
    std::string _function_name;
    std::string _file_name;
    std::uint_least32_t  _line;
};

} // namespace gen_prog

#define GEN_PROG__CURRENT_SOURCE_LOCATION gen_prog::source_location(BOOST_CURRENT_FUNCTION, __FILE__, __LINE__)

#endif // ** gen_prog__source_location_hpp ** //
