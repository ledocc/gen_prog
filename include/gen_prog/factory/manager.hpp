#ifndef GEN_PROG__FACTORY__MANAGER_HPP_
#define GEN_PROG__FACTORY__MANAGER_HPP_



#include <unordered_map>

#include <boost/functional/factory.hpp>
#include <boost/function.hpp>



namespace gen_prog {
namespace factory {

template <typename T>
using factory_generator = boost::function<T*()>;

template <typename IdentifierT, typename ValueT, typename PrototypeT = boost::function<ValueT*()> >
class manager
{
public:
    using id_type           = IdentifierT;
    using value_type        = ValueT;
    using factory_prototype = PrototypeT;

    using factory_map       = std::unordered_map<id_type, factory_prototype>;
    using result_type       = typename factory_prototype::result_type;


public:
    bool add(const id_type & id, const factory_prototype & factory)
    {
        return _map.insert(std::make_pair(id, factory)).second;
    }

    void remove(const id_type & id)
    {
        auto it = _map.find(id);
        if (it != _map.end()) _map.erase(it);
    }

    bool has(const id_type & id) const
    {
        return (_map.find(id) != _map.end());
    }

    template <typename... Args>
    result_type create(const id_type & id, Args&&... args) const
    { return get(id)(std::forward<Args>(args)...); }


private:
    factory_prototype get(const id_type & id) const
    {
        auto it = _map.find(id);
        if (it != _map.end()) return it->second;
        else return factory_prototype();
    }


private:
    factory_map _map;
};

}  // namespace factory
}  // namespace gen_prog

namespace gp = gen_prog;

#endif // ** GEN_PROG__FACTORY__MANAGER_HPP_ ** //
// End of file
