#ifndef THOR_PATTERN_SINGLETON_H_
#define THOR_PATTERN_SINGLETON_H_

#include "common.h"

#include "thor/idioms/smart_ptr.h"
#include "thor/idioms/uncopyable.h"

/**
 * the manager class of singleton! (thread_safe by static local object)
 */

TP_NS_BEGIN

// the creat policy
template<typename T>
struct CreateBase {
    static void Destroy(T* p) {}
};

// create by static local
template<typename T>
struct CreateStatic : public CreateBase<T> {
    template<typename... Args>
    static T* Create(Args&&... args) {
        static T t(std::forward<Args>(args)...);
        return &t;
    }
};

// create using new
template<typename T>
struct CreateUsingNew : public CreateBase<T> {
    template<typename... Args>
    static T* Create(Args&&... args) {
        return new T(std::forward<Args>(args)...);
    }

    static void Destroy(T* p) {
        DELETE_POINTER(p);
    }

};

// create to get the unique_ptr
template<typename T>
struct CreateUnique : public CreateBase<T> {
    template<typename... Args>
    static T* Create(Args&&... args) {
        static TI_NS::UniquePtr<T> t_ptr(new T(std::forward<Args>(args)...));
        return t_ptr.get();
    }
};

// create to get the shared_ptr
template<typename T>
struct CreateShared : public CreateBase<T> {
    template<typename... Args>
    static T* Create(Args&&... args) {
        static TI_NS::SharedPtr<T> t_ptr(new T(std::forward<Args>(args)...));
        return t_ptr.get();
    }
};

// the holder of singleton
template
<
    typename T,
    template<typename> class CreatePolicy = CreateStatic
>
class SingletonHolder : TI_NS::Uncopyable {

public:
    using ObjectType = T;

    template<typename... Args>
    static T* Instance(Args&&... args) {
        return CreatePolicy<T>::Create(std::forward<Args>(args)...);
    }

private:
    SingletonHolder(void);
};

TP_NS_END

#endif /*THOR_PATTERN_SINGLETON_H_*/