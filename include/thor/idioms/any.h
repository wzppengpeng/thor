#ifndef THOR_IDIOMS_ANY_H_
#define THOR_IDIOMS_ANY_H_

#include <string>
#include <typeindex>

#include "smart_ptr.h"

/**
 * the any object, to store any types
 * USAGE:
 *  Any a(std::vector<int>(10, 5));
    print_vector(a.cast<std::vector<int>>());
    a = 10;
    a = 0.01;
    print(a.cast<double>());
 */


TI_NS_BEGIN

template<template<typename...> class SmartPtr>
class AnyType {
public:
    // the exception for any cast
    struct BadAnyCast : std::bad_cast {
        BadAnyCast(const std::string& reason) :reason_(reason) {}
        BadAnyCast(std::string&& reason) :reason_(std::move(reason)) {}

        virtual const char* what() const noexcept {
            return reason_.c_str();
        }

        std::string reason_;
    };

public:
    // the constrctor by any value
    template<typename T>
    AnyType(T&& value) :
        ptr_(new DerivedType<typename std::decay<T>::type>(std::forward<T>(value))),
        tp_index_(std::type_index(typeid(typename std::decay<T>::type))) {}

    // the default constructor
    AnyType(void) : tp_index_(std::type_index(typeid(void))) {}

    // copy constrctor
    AnyType(const AnyType& other) : ptr_(other.Clone()), tp_index_(other.tp_index_) {}

    // move constructor
    AnyType(AnyType&& other) : ptr_(std::move(other.ptr_)), tp_index_(other.tp_index_) {
        other.tp_index_ = std::type_index(typeid(void));
    }

    // copy operator
    AnyType& operator= (const AnyType& other) {
        if(this != &other) {
            ptr_ = other.Clone();
            tp_index_ = other.tp_index_;
        }
        return *this;
    }

    // move operator
    AnyType& operator= (AnyType&& other) {
        if(this != &other) {
            ptr_ = std::move(other.ptr_);
            tp_index_ = other.tp_index_;
            other.tp_index_ = std::type_index(typeid(void));
        }
        return *this;
    }

    // check if is null of T
    inline bool IsNull() const { return ptr_.get() == nullptr; }

    // check if now type is any T
    template<typename T>
    inline bool Is() const {
        return tp_index_ == std::type_index(typeid(T));
    }

    // cast function, cast to needed when using
    template<typename T>
    const T& cast() const {
        if(!Is<T>()) {
            throw BadAnyCast(std::string("can not cast ") + typeid(T).name() + " to " + tp_index_.name());
        }
        return dynamic_cast<DerivedType<T>*>(ptr_.get())->value_;
    }

    // cast function, no const
    template<typename T>
    T& cast() {
        if(!Is<T>()) {
            throw BadAnyCast(std::string("can not cast ") + typeid(T).name() + " to " + tp_index_.name());
        }
        return dynamic_cast<DerivedType<T>*>(ptr_.get())->value_;
    }

private:
    struct BaseType;
    using BaseTypePtr = SmartPtr<BaseType>;

    struct BaseType {
        virtual ~BaseType() {} // the virtual deconstrtor
        virtual BaseTypePtr Clone() const = 0;
    };

    // the derived of any type
    template<typename T>
    struct DerivedType : BaseType {
        // the construtor
        template<typename U>
        DerivedType(U&& u) : value_(std::forward<U>(u)) {}
        // the clone interface, clone a new object
        virtual BaseTypePtr Clone() const override {
            return BaseTypePtr(new DerivedType<T>(value_));
        }

        T value_;
    };

    // the clone function for copy constructor
    BaseTypePtr Clone() const {
        if(ptr_.get()) {
            return ptr_->Clone();
        }
        return BaseTypePtr(nullptr);
    }

    BaseTypePtr ptr_; // the ptr has the value of any type
    std::type_index tp_index_;

};

// the declare of normal types
using Any = AnyType<UniquePtr>; // use unique ptr to handle the memory

TI_NS_END

#endif /*THOR_IDIOMS_ANY_H_*/