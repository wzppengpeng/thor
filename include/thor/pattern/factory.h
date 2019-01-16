#ifndef THOR_PATTERN_FACTORY_H_
#define THOR_PATTERN_FACTORY_H_

#include <stdexcept>
#include <functional>
#include <string>
#include <vector>
#include <map>

#include "thor/meta/list/list.h"

#include "common.h"
#include "singleton.h"

/**
 * the factory pattern
 * input target type, paramter types
 *
 * USAGE:
 *  TP_NS::Registry<Base, A, std::string, __type_list__(const int&, int)> regis_a("a");
 *
 * // calling...
 *  using Factory = TP_NS::FactoryHolder<Base, std::string, __type_list__(const int&, int)>;
    auto a = Factory::Instance()->CreateUnique("a", 1, 2);
 */

TP_NS_BEGIN

namespace details {

template<typename D, typename TL, typename... Args>
struct CreateByParamList;

template<typename D, typename... Args>
struct CreateByParamList<D, TM_NS::NullType, Args...> {
    static D* Call(Args... args) {
        return new D(std::forward<Args>(args)...);
    }

    using type = std::function<D*(Args...)>;
};

template<typename D, typename Head, typename Tail, typename... Args>
struct CreateByParamList<D, TM_NS::TypeElem<Head, Tail>, Args...>
    : CreateByParamList<D, Tail, Args..., Head> {};

} //details

// the exception handle class
template <typename IdentifierType, typename AbstractProduct>
struct DefaultFactoryError
{
    struct Exception : public std::exception
    {
        const char* what() const noexcept { return "Unknown Type, Not Registered"; }
    };

    static AbstractProduct* OnUnknownType(IdentifierType)
    {
        throw Exception();
    }
};


// the factory template to get the target base pointer
template
<
    typename AbstractProduct, // the base class of interface need to be construct
    typename IdentifierType, // std::string is the basic type
    typename CreatorParmTList = __empty_list__(), // a type list to store the parameters of creator
    template<typename...> class Map = std::map, // the container to save the registered relationship
    template<typename, typename> class FactoryErrorPolicy = DefaultFactoryError
>
class Factory : FactoryErrorPolicy<IdentifierType, AbstractProduct> {
    // some alias of helper
    using FunctorType = typename details::CreateByParamList<AbstractProduct, CreatorParmTList>::type;

public:
    // constructor
    Factory() = default;
    ~Factory() {}

    template<typename D>
    void Register(const IdentifierType& id) {
        static_assert(std::is_base_of<AbstractProduct, D>::value, "the registered type must be derived");
        associations_.emplace(id, &details::CreateByParamList<D, CreatorParmTList>::Call);
    }

    bool UnRegister(const IdentifierType& id) {
        if(associations_.count(id) == 0) {
            return false;
        } else {
            associations_.erase(id);
            return true;
        }
    }

    std::vector<IdentifierType> RegisteredIds() const {
        std::vector<IdentifierType> ids; ids.reserve(associations_.size());
        for(const auto & p : associations_) {
            ids.emplace_back(p.first);
        }
        return ids;
    }

    template<typename... Args>
    AbstractProduct* Create(const IdentifierType& id, Args&&... args) {
        auto it = associations_.find(id);
        if(it != associations_.end()) {
            return it->second(std::forward<Args>(args)...);
        }
        return this->OnUnknownType(id);
    }

    template<typename... Args>
    TI_NS::UniquePtr<AbstractProduct> CreateUnique(const IdentifierType& id, Args&&... args) {
        return TI_NS::UniquePtr<AbstractProduct>(Create(id, std::forward<Args>(args)...));
    }

    template<typename... Args>
    TI_NS::SharedPtr<AbstractProduct> CreateShared(const IdentifierType& id, Args&&... args) {
        return TI_NS::SharedPtr<AbstractProduct>(Create(id, std::forward<Args>(args)...));
    }

private:
    Map<IdentifierType, FunctorType> associations_;
};


// declare the singleton class for use
template
<
    typename AbstractProduct, // the base class of interface need to be construct
    typename IdentifierType, // std::string is the basic type
    typename CreatorParmTList = __empty_list__(), // a type list to store the parameters of creator
    template<typename...> class Map = std::map, // the container to save the registered relationship
    template<typename, typename> class FactoryErrorPolicy = DefaultFactoryError
>
using FactoryHolder = SingletonHolder<Factory<AbstractProduct,
    IdentifierType, CreatorParmTList, Map, FactoryErrorPolicy>>; // use by Instance

// declare the singleton class for use
// define a static object in each dll
template
<
    typename AbstractProduct, // the base class of interface need to be construct
    typename Derived, // the derived class
    typename IdentifierType, // std::string is the basic type
    typename CreatorParmTList = __empty_list__(), // a type list to store the parameters of creator
    template<typename...> class Map = std::map, // the container to save the registered relationship
    template<typename, typename> class FactoryErrorPolicy = DefaultFactoryError
>
struct Registry {
    Registry(const IdentifierType& id) {
        FactoryHolder<AbstractProduct, IdentifierType,
            CreatorParmTList, Map, FactoryErrorPolicy>::Instance()
            ->template Register<Derived>(id); // use template key word to make the complier know it is a template function
    }
};

TP_NS_END

#endif /*THOR_PATTERN_FACTORY_H_*/