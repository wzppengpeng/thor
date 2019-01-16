#ifndef THOR_IDIOMS_OPTIONAL_H_
#define THOR_IDIOMS_OPTIONAL_H_

#include <functional>
#include <stdexcept>

#include "common.h"

/**
 * the optional in C++14, implement by C++11
 *
 * USAGE:
 *  Optional<int> op;
    ASSERT_FALSE(op.IsInit());
    Optional<int> op1 = 1;
    ASSERT_TRUE(op1.IsInit());
    ASSERT_EQ(*op1, 1);

    Optional<string> a("ok");
    Optional<string> b("ok");
    Optional<string> c("not ok");
    ASSERT_TRUE(bool(a));
    ASSERT_LT(c, a);
    c = a;
    ASSERT_EQ(c, a);
    map<Optional<string>, int> mymap; // based on operator <
    mymap.emplace(a, 1);
    ASSERT_TRUE(mymap.count(a) > 0);

    unordered_map<Optional<string>, int> my_umap;
    my_umap.emplace(a, 1);
    ASSERT_TRUE(my_umap.count(a) > 0);
 */

TI_NS_BEGIN

template<typename T>
class Optional {
    using StoreType = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;

public:
    // default constructor
    Optional() = default;

    // construct by left values
    Optional(const T& value) : has_init_(false) {
        Construct(value);
    }

    // constrcut by right value
    Optional(T&& value) : has_init_(false) {
        Construct(std::move(value));
    }

    // deconstrcuctor
    ~Optional() { Destroy(); }

    // copy constrctor
    Optional(const Optional& other) : has_init_(false) {
        Assign(other);
    }

    // move constructor
    Optional(Optional&& other) {
        Assign(std::move(other));
    }

    // operator =
    Optional& operator= (const Optional& other) {
        Assign(other);
        return *this;
    }

    Optional& operator= (Optional&& other) {
        Assign(std::move(other));
        return *this;
    }

    // the emplace functions
    template<typename... Args>
    void Emplace(Args&&... args) {
        Destroy();
        Construct(std::forward<Args>(args)...);
    }

    // some getter functions
    inline bool IsInit() const { return has_init_; }
    explicit inline operator bool() const { return IsInit(); }

    // to get the reference of the object
    inline T& operator*() {
        if (IsInit())
            return *((T*) (&data_));
        else
            throw std::runtime_error("this optional has not been initialized");
    }

    const T& operator*() const {
        if (IsInit())
            return *((T*) (&data_));
        else
            throw std::runtime_error("this optional has not been initialized");
    }

    bool operator == (const Optional<T>& rhs) const {
        return (!bool(*this)) != (!rhs) ? false : (!bool(*this) ? true : (*(*this)) == (*rhs));
    }

    bool operator < (const Optional<T>& rhs) const {
        return !rhs ? false : (!bool(*this) ? true : (*(*this) < (*rhs)));
    }

    inline bool operator != (const Optional<T>& rhs) {
        return !(*this == (rhs));
    }

private:
    // private functions
    template<typename... Args>
    void Construct(Args&&... args) {
        new (&data_) T(std::forward<Args>(args)...);
        has_init_ = true;
    }

    // destroy the type
    void Destroy() {
        if(has_init_) {
            reinterpret_cast<T*>(&data_)->~T();
            has_init_ = false;
        }
    }

    // the operator assign functions
    void Assign(const Optional& other) {
        if(other.IsInit()) {
            CopyFromStore(other.data_);
            has_init_ = true;
        } else {
            Destroy();
        }
    }

    // assign from right
    void Assign(Optional&& other) {
        if(other.IsInit()) {
            MoveFromStore(std::move(other.data_));
            has_init_ = true;
        } else {
            Destroy();
        }
    }

    // two help functions for construct
    void MoveFromStore(StoreType&& other) {
        Destroy();
        new (&data_) T(std::move(*reinterpret_cast<T*>(&other)));
    }

    void CopyFromStore(const StoreType& other) {
        Destroy();
        new (&data_) T(*reinterpret_cast<const T*>(&other));
    }

private:
    // private members
    bool has_init_ = false;
    StoreType data_;
};

TI_NS_END

namespace std {

template<typename T>
struct hash<TI_NS::Optional<T>> {
    using argument_type = TI_NS::Optional<T>;
    using result_type = std::size_t;
    result_type operator()(argument_type const& op) const {
        return std::hash<T>{}(*op);
    }
};

} // open the std namespace

#endif /*THOR_IDIOMS_OPTIONAL_H_*/