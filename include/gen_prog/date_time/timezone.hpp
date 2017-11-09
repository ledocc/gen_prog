#ifndef gen_prog__date_time__timezone_hpp
#define gen_prog__date_time__timezone_hpp



#include <array>
#include <chrono>
#include <ctime>
#include <string>


namespace gen_prog {
namespace date_time {

class timezone
{
public:
    timezone() = default;
    timezone(char ** tzname_)
    {
        _name[0] = tzname_[0];
        _name[1] = tzname_[1];
    }

    const std::string & std_name() const { return _name[0]; }
    const std::string & dst_name() const { return _name[1]; }
    const std::string & name() const { return dst_name().empty() ? std_name() : dst_name(); }


private:
    std::array<std::string, 2> _name;
    std::chrono::seconds _secondToUTC;
};

timezone get_timezone()
{
    tzset();

    return timezone(::tzname);
}

} // namespace date_time
} // namespace gen_prog

#endif // gen_prog__date_time__timezone_hpp
