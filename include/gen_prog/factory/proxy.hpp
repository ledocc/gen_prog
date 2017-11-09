#ifndef GEN_PROG__FACTORY__PROXY_HPP_
#define GEN_PROG__FACTORY__PROXY_HPP_



#include <string>
#include <unordered_map>

#include <boost/functional/factory.hpp>
#include <boost/noncopyable.hpp>



namespace gen_prog
{
namespace factory
{

namespace detail {

template <typename T>
using factory_generator = boost::factory<T>;

} // namespace detail

template <typename ManagerT, typename ValueT, template <typename> class FactoryGeneratorT = detail::factory_generator >
class proxy : public boost::noncopyable
{
public:
    using manager_type = ManagerT;
    using value_type   = ValueT;

    template <typename T>
    using factory_generator = FactoryGeneratorT<T>;

    using factory_type = factory_generator<value_type>;
    using id_type      = typename manager_type::id_type;

    proxy(const id_type & id) : _id(id)
    { manager_type::instance().add( _id, factory_type() ); }
    ~proxy()
    { manager_type::instance().remove( _id ); }

private:
    id_type _id;
};

} // namespace factory
} // namespace gen_prog

namespace gp = gen_prog;

#endif // ** GEN_PROG__FACTORY__PROXY_HPP_ ** //
// End of file
