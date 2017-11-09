#ifndef gen_prog__percent__exception_hpp
#define gen_prog__percent__exception_hpp



#include <exception>
#include <string>



namespace gp {
namespace percent {

class invalid_percent_value_exception : public std::exception
{
public:
    invalid_percent_value_exception(unsigned char value): _value(value)
    {
        std::stringstream ss;
        ss << " gp::percent : invalid percent value : " << _value;
    }

    virtual const char * what() const override { return _message.c_str(); }

private:
    unsigned char _value;
    std::string _message;
};

} // namespace percent
} // namespace gp

#endif // gen_prog__percent__exception_hpp
