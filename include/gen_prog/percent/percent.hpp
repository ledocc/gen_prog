#ifndef gen_prog__percent__percent_hpp
#define gen_prog__percent__percent_hpp


#include <gen_prog/percent/exception.hpp>


namespace gp {
namespace percent {

///
/// \brief The percent class represent a percentage value.
/// The value have to be between 0 and 100 otherwise a exception
///
struct percent
{
    percent() {}
    percent(unsigned char value) { set(value); }

    void set(unsigned char value)
    {
        throwIfNotBetweenZeroAndHundred(value);
        _value = value;
    }

    percent & operator = (unsigned char value) { set(value); return *this; }


protected:
    void throwIfNotBetweenZeroAndHundred(unsigned char value)
    { if (value > 100) { throw invalid_percent_value_exception(value); } }


private:
    unsigned char _value = 0;
};

} // namespace percent
} // namespace gp

#endif // gen_prog__percent__percent_hpp
