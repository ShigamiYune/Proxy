#pragma once
#ifndef PROXY_H
#define PROXY_H

#include <cstddef>
#include <iostream>

template <typename Class, typename Member>
constexpr std::ptrdiff_t offset_of(Member Class::* memberPtr) {
    return reinterpret_cast<std::ptrdiff_t>(
        &(reinterpret_cast<Class const volatile*>(0x1000)->*memberPtr)
    ) - std::ptrdiff_t(0x1000);
}

template <typename ProxyType, typename Class, typename Member>
Class* get_class_ptr_from_proxy(ProxyType* proxy_ptr, Member Class::* memberPtr) {
    auto offset = offset_of(memberPtr);
    return reinterpret_cast<Class*>(
        reinterpret_cast<char*>(proxy_ptr) - offset
    );
}

template <typename ProxyType, typename Class, typename Member>
const Class* get_class_ptr_from_proxy(const ProxyType* proxy_ptr, Member Class::* memberPtr) {
    auto offset = offset_of(memberPtr);
    return reinterpret_cast<const Class*>(
        reinterpret_cast<const char*>(proxy_ptr) - offset
    );
}

template <typename T, typename Derived>
class ProxyOps {
protected:
    T data;                                                                  
public:
    Derived& operator=(const T& value) {
        self().set(value);
        return self();
    }

    T operator+(const T& value) const { return self().get() + value; }
    T operator-(const T& value) const { return self().get() - value; }
    T operator*(const T& value) const { return self().get() * value; }
    T operator/(const T& value) const { return self().get() / value; }
    T operator%(const T& value) const { return self().get() % value; }

    Derived& operator+=(const T& value) { self().set(self().get() + value); return self(); }
    Derived& operator-=(const T& value) { self().set(self().get() - value); return self(); }
    Derived& operator*=(const T& value) { self().set(self().get() * value); return self(); }
    Derived& operator/=(const T& value) { self().set(self().get() / value); return self(); }
    Derived& operator%=(const T& value) { self().set(self().get() % value); return self(); }

    bool operator==(const T& value) const { return self().get() == value; }
    bool operator!=(const T& value) const { return self().get() != value; }
    bool operator<(const T& value)  const { return self().get() < value; }
    bool operator<=(const T& value) const { return self().get() <= value; }
    bool operator>(const T& value)  const { return self().get() > value; }
    bool operator>=(const T& value) const { return self().get() >= value; }

    bool operator!() const { return !static_cast<bool>(self().get()); }
    bool operator&&(const T& value) const { return static_cast<bool>(self().get()) && static_cast<bool>(value); }
    bool operator||(const T& value) const { return static_cast<bool>(self().get()) || static_cast<bool>(value); }

    T operator&(const T& value) const { return self().get() & value; }
    T operator|(const T& value) const { return self().get() | value; }
    T operator^(const T& value) const { return self().get() ^ value; }
    T operator~() const { return ~self().get(); }

    Derived& operator&=(const T& value) { self().set(self().get() & value); return self(); }
    Derived& operator|=(const T& value) { self().set(self().get() | value); return self(); }
    Derived& operator^=(const T& value) { self().set(self().get() ^ value); return self(); }

    T operator<<(int shift) const { return self().get() << shift; }
    T operator>>(int shift) const { return self().get() >> shift; }
    Derived& operator<<=(int shift) { self().set(self().get() << shift); return self(); }
    Derived& operator>>=(int shift) { self().set(self().get() >> shift); return self(); }

    Derived& operator++() { self().set(self().get() + 1); return self(); }
    Derived& operator--() { self().set(self().get() - 1); return self(); }

    T operator++(int) {
        T old = self().get();
        self().set(old + 1);
        return old;
    }
    T operator--(int) {
        T old = self().get();
        self().set(old - 1);
        return old;
    }

    operator T() { return self().get(); }

    friend std::ostream& operator<<(std::ostream& os, const ProxyOps& p) {
        return os << p.get();
    }

    T& get_data() { return data; }
    const T get_data() const { return data; }
    void set_data(const T& value) { data = value; }

protected:
    inline Derived& self() { return static_cast<Derived&>(*this); }
    inline const Derived& self() const { return static_cast<const Derived&>(*this); }
};


#define DGET(NAME) {return NAME.get_data();}
#define DSET(NAME) {NAME.set_data(value);}


#define Proxy(TYPE, NAME, CLASS, GET, SET, INITIAL)                                                                 \
    struct TYPE##_##NAME##CLASS : public ProxyOps<TYPE, TYPE##_##NAME##CLASS> {                                     \
        TYPE##_##NAME##CLASS(const TYPE& value) { data = value;}                                                    \
        CLASS* get_class_ptr() {return get_class_ptr_from_proxy(this, &CLASS::NAME);}                               \
        const CLASS* get_class_ptr() const {return get_class_ptr_from_proxy(this, &CLASS::NAME);}                   \
        TYPE operator()() { return get_class_ptr()->get##NAME##CLASS(); }                                           \
        TYPE* operator->() { return &get_class_ptr()->get##NAME##CLASS(); }                                         \
        TYPE get() { return get_class_ptr()->get##NAME##CLASS(); }                                                  \
        void set(const TYPE& value) { get_class_ptr()->set##NAME##CLASS(value); }                                   \
    } NAME = TYPE##_##NAME##CLASS(INITIAL);                                                                         \
    private: TYPE& get##NAME##CLASS() GET void set##NAME##CLASS(TYPE value) SET

#endif 
