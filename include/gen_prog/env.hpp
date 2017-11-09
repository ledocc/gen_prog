#ifndef gen_prog__env_hpp
#define gen_prog__env_hpp



#include <stdlib.h>

#include <exception>
#include <string>

#include <boost/exception/all.hpp>
#include <boost/lexical_cast.hpp>


namespace gen_prog {
namespace env {

namespace exceptions {
class Exception : public std::exception
{
public:
    Exception() = default;
    virtual ~Exception() = default;


    virtual const char* what() const throw() { return _message.c_str(); }


protected:
    const std::string & getMessage() const { return _message; }
    void setMessage(const std::string & message) { _message = message; }


private:
    std::string _message;
};


class InvalidParameter : public Exception
{
public:
    InvalidParameter(const char * paramName, const char * raison)
    {
        std::stringstream ss;
        ss << "Invalid parameter : \"" << paramName << "\" "<<raison<<".";
        setMessage(ss.str());
    }
};

class VariableNotDefined : public Exception
{
public:
    VariableNotDefined(const char * name)
    {
        std::stringstream ss;
        ss << "Environment variable \"" << name << "\" not defined.";
        setMessage(ss.str());
    }
};

} // namespace exceptions


namespace detail {

template <typename OutputT>
struct StringToArithmeticConvert
{
    static OutputT apply(const char * value)
    {
        return boost::lexical_cast<OutputT>(value);
    }
};
struct StringPassThrough
{
    static std::string apply(const char * value)
    {
        return value;
    }
};
struct ErrorConvert
{
};


template <typename OutputT>
struct convert_dispatcher
{
    using type = std::conditional_t< std::is_arithmetic<OutputT>::value,
                                     StringToArithmeticConvert<OutputT>,
                                     std::conditional_t< std::is_same<OutputT, std::string>::value,
                                                         StringPassThrough,
                                                         ErrorConvert
                                                       >
                                   >;
};


} // namespace detail



template <typename T>
T get(const char * name)
{
    if (nullptr == name)
    {
        BOOST_THROW_EXCEPTION(exceptions::InvalidParameter("name", "should not be null"));
    }

    const char * valueStr = getenv(name);

    if (nullptr == valueStr)
    {
        BOOST_THROW_EXCEPTION(exceptions::VariableNotDefined(name));
    }

    using ConvertOperator = typename detail::convert_dispatcher<T>::type;

    return ConvertOperator::apply(valueStr);
}

template <typename T>
T get_or_default(const char * name, const T & defaultValue)
{
    try
    {
        return get<T>(name);
    }
    catch(exceptions::VariableNotDefined &)
    {
    }
    catch(boost::bad_lexical_cast &)
    {
    }

    return defaultValue;
}

inline bool exists(const char * name)
{
    if (nullptr == name)
    {
        BOOST_THROW_EXCEPTION(exceptions::InvalidParameter("name", "should not be null"));
    }

    return (nullptr != getenv(name));
}

} // namespace env
} // namespace gen_prog

#endif // gen_prog__env_hpp

