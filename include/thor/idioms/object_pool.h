#ifndef THOR_IDIOMS_OBJECT_POOL_H_
#define THOR_IDIOMS_OBJECT_POOL_H_

#include <list>

#include "smart_ptr.h"

/**
 * the smart ptr wrapped object pool
 */

TI_NS_BEGIN

template
<
    typename Object,
    template<typename...> class ListContainer = std::list,
    template<typename> class SmartPtr = UniquePtr
>
class ObjectPool {
    // declare the type of Object List
    using ObjectList = ListContainer<SmartPtr<Object>>;

public:
    using size_type = typename ObjectList::size_type; // size_t

    // constrctor
    template<typename... Args>
    ObjectPool(size_type un_size, Args&&... args) {
        for(size_type i = 0; i < un_size; ++i) {
            obj_pool_.push_back(SmartPtr<Object>(new Object(std::forward<Args>(args)...)));
        }
    }

    ~ObjectPool() = default;

    inline size_type Size() const { return obj_pool_.size(); }

    inline bool Empty() const { return obj_pool_.empty(); }

    inline void Clear() { obj_pool_.clear(); }

    // get the object if not empty
    SmartPtr<Object> Get() {
        SmartPtr<Object> ptr(nullptr);
        if(!Empty()) {
            ptr = std::move(obj_pool_.front());
            obj_pool_.pop_front();
        }
        return ptr;
    }

    // Create the object if is empty
    template<typename... Args>
    SmartPtr<Object> Create(Args&&... args) {
        if(Empty()) {
            return SmartPtr<Object>(new Object(std::forward<Args>(args)...));
        } else {
            SmartPtr<Object> ptr = std::move(obj_pool_.front());
            obj_pool_.pop_front();
            return ptr;
        }
    }

    // return the object ptr
    void Return(SmartPtr<Object> obj) {
        obj_pool_.push_back(std::move(obj));
    }

private:
    ObjectList obj_pool_ {};

};

TI_NS_END

#endif /*THOR_IDIOMS_OBJECT_POOL_H_*/