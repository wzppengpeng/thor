#ifndef THOR_IDIOMS_VARIANT_H_
#define THOR_IDIOMS_VARIANT_H_

#include <typeindex>

#include "thor/meta/list/list.h"
#include "thor/meta/traits/function_traits.h"

#include "common.h"

/**
 * the variants class just like union in C
 * USAGE:
 *  typedef TI_NS::Variant<int, double, string, vector<int>> CV;
    CV v1 = vector<int> {1, 3, 5};
    ASSERT_FALSE(v1.Empty());
    ASSERT_TRUE(v1.Is<std::vector<int>>());
    ASSERT_FALSE(v1.Is<string>());
    ASSERT_EQ(v1.Get<vector<int>>()[0], 1);
    v1.Get<vector<int>>().push_back(6);
    ASSERT_EQ(v1.Get<vector<int>>(), (vector<int> {1, 3, 5, 6}));
    v1 = string("temp");
    v1 = 0.01;
    v1 = string("temp");
    ASSERT_EQ(v1.Index(), 2);
    v1.Visit([](int i) { ASSERT_EQ(i, 5); },
             [](string& s) { ASSERT_EQ(s, string("temp")); s = "tmp"; },
             [](double j) { ASSERT_EQ(j, 6.0); } );
    ASSERT_EQ(v1.Get<string>(), "tmp");
 */

TI_NS_BEGIN

namespace details
{

// some help meta functions
// two meta fucntion to get the size and alingment of T
template<typename T>
using ToSize = __int__(sizeof(T));

template<typename T>
using MaxAlignment = __int__(std::alignment_of<T>::value);

// reduce the size list to get the max value in it
template<typename TL, template<typename> class Op>
struct GetMaxValueOfTL {
    using type = __tl_reduce__(__tl_map__(TL, Op), __int__(-1), TM_NS::Max);
};

// to get the max size
template<typename TL>
using GetMaxSize = GetMaxValueOfTL<TL, ToSize>;

// to get the max alingment
template<typename TL>
using GetMaxAlignment = GetMaxValueOfTL<TL, MaxAlignment>;

// the help function to get Type's type_index
template<typename T>
inline std::type_index get_tp_index() { return std::type_index(typeid(T)); }

using TM_NS::TypeElem;

// The placement new help class to construct or destroy the object
template<typename TL> struct VariantHelper;

template<typename Head, typename Tail>
struct VariantHelper<TypeElem<Head, Tail>> {
    static void Destroy(std::type_index id, void* data) {
        if(id == get_tp_index<Head>()) {
            reinterpret_cast<Head*>(data)->~Head();
        } else {
            VariantHelper<Tail>::Destroy(id, data);
        }
    }

    static void Move(std::type_index id, void* old_data, void* new_data) {
        if(id == get_tp_index<Head>()) {
            new (new_data) Head(std::move(*reinterpret_cast<Head*>(old_data)));
        } else {
            VariantHelper<Tail>::Move(id, old_data, new_data);
        }
    }

    static void Copy(std::type_index id, void* old_data, void* new_data) {
        if(id == get_tp_index<Head>()) {
            new (new_data) Head(*reinterpret_cast<Head*>(old_data));
        } else {
            VariantHelper<Tail>::Copy(id, old_data, new_data);
        }
    }
};

// the special
template<> struct VariantHelper<TM_NS::NullType> {
    static void Destroy(std::type_index id, void* data) {}
    static void Move(std::type_index id, void* old_data, void* new_data) {}
    static void Copy(std::type_index id, void* old_data, void* new_data) {}
};

} //details


// the class of variant, input is a TL
template<typename... Types>
class Variant {
    using TypeList = __type_list__(Types...);
    using HelperT = details::VariantHelper<TypeList>;

public:
    // declarations of traits
    constexpr static int data_size = __value__(typename details::GetMaxSize<TypeList>::type);
    constexpr static int align_size = __value__(typename details::GetMaxAlignment<TypeList>::type);
    using StoreType = typename std::aligned_storage<data_size, align_size>::type; // the memory

public:
    template<int I>
    using TypeOfIndex = __tl_type_at_by_val__(TypeList, I);

    // the default constrctor
    Variant(void) : tp_index_(typeid(void)), index_(-1) {}

    // deconstructor
    ~Variant() { HelperT::Destroy(tp_index_, &data_); }

    // move constrcution
    Variant(Variant<Types...>&& other) : tp_index_(other.tp_index_), index_(other.index_) {
        HelperT::Move(tp_index_, &other.data_, &data_);
    }

    // move operator= assign
    Variant<Types...>& operator= (Variant<Types...>&& other) {
        tp_index_ = other.tp_index_;
        index_ = other.index_;
        HelperT::Move(tp_index_, &other.data_, &data_);
        return *this;
    }

    // copy construction
    Variant(const Variant<Types...>& other) : tp_index_(other.tp_index_), index_(other.index_) {
        HelperT::Copy(tp_index_, const_cast<StoreType*>(&other.data_), &data_);
    }

    // copy opeartor= assign
    Variant<Types...>& operator= (const Variant<Types...>& other) {
        tp_index_ = other.tp_index_;
        index_ = other.index_;
        HelperT::Copy(tp_index_, const_cast<StoreType*>(&other.data_), &data_);
        return *this;
    }

    // the basic constructor by any value
    template
    <
        class T,
        class = typename std::enable_if
        <
            __value__(__tl_is_included__(TypeList, typename std::remove_reference<T>::type))
        >::type
    >
    Variant(T&& value) : tp_index_(typeid(void)), index_(-1) {
        HelperT::Destroy(tp_index_, &data_);
        using NowType = typename std::remove_reference<T>::type;
        new (&data_) NowType(std::forward<T>(value)); //placement new
        tp_index_ = details::get_tp_index<NowType>();
        index_ = __value__(__tl_index_of__(TypeList, NowType));
    }

    // check if now data type is T
    template<typename T>
    inline bool Is() const { return tp_index_ == details::get_tp_index<T>(); }

    // check if the variant is empty
    inline bool Empty() const { return tp_index_ == details::get_tp_index<void>(); }

    // get the type index of now
    inline std::type_index TypeIndex() const { return tp_index_; }

    // get the index of type in typelist
    inline int Index() const { return index_; }

    // the most frequent Get interface
    template<typename T>
    T& Get() {
        if(!Is<T>()) {
            throw std::bad_cast();
        }
        return *(T*) (&data_);
    }

    // compare functuion of other objects
    inline bool operator== (const Variant& other) const {
        return tp_index_ == other.tp_index_;
    }

    inline bool operator< (const Variant& other) const {
        return tp_index_ < other.tp_index_;
    }

    inline bool operator> (const Variant& other) const {
        return tp_index_ > other.tp_index_;
    }

    // the visit interface
    // receive a list of function objects, then late-fetch the calling
    // which is faster and convenient to add operations to data been stored
    template<typename F>
    void Visit(F&& f) {
        using ParamT = typename std::decay<__fun_args_type__(F, 0)>::type;
        if(Is<ParamT>()) {
            f(Get<ParamT>());
        }
    }

    template<typename F, typename... Rest>
    void Visit(F&& f, Rest&&... rest) {
        using ParamT = typename std::decay<__fun_args_type__(F, 0)>::type;
        if(Is<ParamT>()) {
            Visit(std::forward<F>(f));
        } else {
            Visit(std::forward<Rest>(rest)...);
        }
    }

private:
    // the data memory
    StoreType data_;
    // the type index
    std::type_index tp_index_;
    // the index of type now in the type list
    int index_;
};

TI_NS_END

#endif /*THOR_IDIOMS_VARIANT_H_*/