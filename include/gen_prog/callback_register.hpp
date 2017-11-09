#ifndef gen_prog__callback_register_hpp
#define gen_prog__callback_register_hpp



#include <functional>
#include <set>
#include <stdexcept>



namespace gen_prog {

///
/// brief The callback_register Class is a convenient class to implement a callback register
///
///
template <class T>
class callback_register
{
public:
    using callback_type  = T;
    using callback_list  = std::set<callback_type>;
    using iterator       = typename callback_list::iterator;
    using const_iterator = typename callback_list::const_iterator;

    using functor_type = std::function<void (const callback_type &)>;


public:
    virtual ~callback_register() = default;


    ///
    /// \brief add add a callback given in parameter to the intern list
    /// \param callback
    ///
    void add(const callback_type & callback);

    ///
    /// \brief remove erase a callback given in parameter and if not found => throw_InvalidParameter
    /// \param callback
    ///
    void remove(const callback_type & callback);

    ///
    /// \brief have ask if callback given is found in the intern list
    /// \param callback
    /// \return
    ///
    bool has(const callback_type & callback) const;


    ///
    /// \brief apply functor with each registered callback in parameter.
    /// \param functor to call with each callback in parameter
    ///
    void apply(const functor_type & functor) const;


private:
    iterator get_callback_iterator_or_throw(const callback_type & callback);
    void throw_null_callback() const;
    void throw_invalid_callback() const;
    void throw_callback_already_exist() const;


protected:
    callback_list _callbacks;
};



//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//



template <class T>
void callback_register<T>::add(const callback_type & callback)
{
    if (callback == nullptr)
    { throw_null_callback(); }

    const auto it = _callbacks.find(callback);
    if (it != _callbacks.end()) { throw_callback_already_exist(); }

    _callbacks.insert(callback);
}

//--------------------------------------------------------------------------------------------------------------------//

template <class T>
void callback_register<T>::remove(const callback_type & callback)
{
    const auto it = this->get_callback_iterator_or_throw(callback);
    _callbacks.erase(it);
}

//--------------------------------------------------------------------------------------------------------------------//

template <class T>
bool callback_register<T>::has(const callback_type & callback) const
{
    const auto it = _callbacks.find(callback);
    return (it != _callbacks.end());
}

//--------------------------------------------------------------------------------------------------------------------//

template <class T>
typename callback_register<T>::iterator
callback_register<T>::get_callback_iterator_or_throw(const callback_type & callback)
{
    const auto it = _callbacks.find(callback);
    if (it == _callbacks.end()) { throw_invalid_callback(); }
    return it;
}

//--------------------------------------------------------------------------------------------------------------------//

template <class T>
void callback_register<T>::throw_null_callback() const
{
    throw std::invalid_argument("null ptr callback");
}

//--------------------------------------------------------------------------------------------------------------------//

template <class T>
void callback_register<T>::throw_invalid_callback() const
{
    throw std::invalid_argument("Unknown callback");
}

//--------------------------------------------------------------------------------------------------------------------//

template <class T>
void callback_register<T>::throw_callback_already_exist() const
{
    throw std::invalid_argument("Callback already exists");
}

//--------------------------------------------------------------------------------------------------------------------//

template <class T>
void callback_register<T>::apply(const functor_type & functor) const
{
    for (auto & callback : _callbacks) { functor(callback); }
}

} // namespace gen_prog

#endif // gen_prog__callback_register_hpp
