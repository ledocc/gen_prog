#ifndef gen_prog__glob_hpp
#define gen_prog__glob_hpp


#include <regex>
#include <string>



namespace gen_prog {

template<typename CharT>
class basic_glob
{
public:
    using string_type = std::basic_string<CharT>;
    using regex_type = std::basic_regex<CharT>;


public:
    basic_glob() = default;
    basic_glob(const string_type & pattern)
    {
        assign(pattern);
    }

    void assign(const string_type & pattern)
    {
        _globForm = pattern;
        _regexForm.assign( glob_to_regex(_globForm) );
    }

    const string_type & pattern() const { return _globForm; }

    bool match(const string_type & value) const
    {
        return std::regex_match(value.begin(), value.end(), _regexForm);
    }


private:
    std::string glob_to_regex(const std::string & val)
    {
        std::string result;

        // change '*' to ".*"
        // change '?' to "."
        // change '.+^$[](){}\\' to "\\"+ the matching char
        regex_type globToRegex("(\\*)|"
                               "(\\?)|"
                               "(\\.|\\+|\\^|\\$|\\[|\\]|\\(|\\)|\\{|\\}|\\\\)");
        const char* format = "(?1.*)(?2.)(?3\\\\$&)";

        std::regex_replace(std::inserter(result, result.end()),
                           val.begin(),
                           val.end(),
                           globToRegex,
                           format);

        result = '^'+result+'$';
        return result;
    }


private:
    string_type _globForm;
    regex_type  _regexForm;
};


using glob = basic_glob<char>;
using wglob = basic_glob<wchar_t>;


} // namespace gen_prog

#endif // gen_prog__glob_hpp
