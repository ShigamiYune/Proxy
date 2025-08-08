#pragma once
#ifndef PROXY_H
#define PROXY_H

// 8 bit
#define Proxy8(Type, Name, Class, Get, Set, Initial) \
private: struct Class##Type##Name{ \
    class _##Type{ \
        Type data; \
        unsigned char offset; \
        \
        Class* ptr() const { return reinterpret_cast<Class*>( \
            reinterpret_cast<std::uintptr_t>(this) - offset); \
        } \
        \
        friend Class; \
        public: \
        _##Type(const Class* _ptr, const Type& initial) { \
            offset = reinterpret_cast<std::uintptr_t>(this) - \
                reinterpret_cast<std::uintptr_t>(_ptr); \
            data = initial; \
        } \
        \
        inline const Type& get() const { return ptr()->get##Class##Type##Name(); } \
        inline void set(const Type& value) { ptr()->set##Class##Type##Name(value); } \
        \
        Type operator+(const Type& value) const { return get() + value; } \
        Type operator-(const Type& value) const { return get() - value; } \
        Type operator*(const Type& value) const { return get() * value; } \
        Type operator/(const Type& value) const { return get() / value; } \
        Type operator%(const Type& value) const { return get() % value; } \
        \
        _##Type& operator+=(const Type& value) { set(get() + value); return *this; } \
        _##Type& operator-=(const Type& value) { set(get() - value); return *this; } \
        _##Type& operator*=(const Type& value) { set(get() * value); return *this; } \
        _##Type& operator/=(const Type& value) { set(get() / value); return *this; } \
        _##Type& operator%=(const Type& value) { set(get() % value); return *this; } \
        \
        bool operator==(const Type& value) const { return get() == value; } \
        bool operator!=(const Type& value) const { return get() != value; } \
        bool operator<(const Type& value)  const { return get() < value; } \
        bool operator<=(const Type& value) const { return get() <= value; } \
        bool operator>(const Type& value)  const { return get() > value; } \
        bool operator>=(const Type& value) const { return get() >= value; } \
        \
        bool operator!() const { return !static_cast<bool>(get()); } \
        bool operator&&(const Type& value) const { return static_cast<bool>(get()) && static_cast<bool>(value); } \
        bool operator||(const Type& value) const { return static_cast<bool>(get()) || static_cast<bool>(value); } \
        \
        Type operator&(const Type& value) const { return get() & value; } \
        Type operator|(const Type& value) const { return get() | value; } \
        Type operator^(const Type& value) const { return get() ^ value; } \
        Type operator~() const { return ~get(); } \
        \
        _##Type& operator&=(const Type& value) { set(get() & value); return *this; } \
        _##Type& operator|=(const Type& value) { set(get() | value); return *this; } \
        _##Type& operator^=(const Type& value) { set(get() ^ value); return *this; } \
        \
        Type operator<<(int shift) const { return get() << shift; } \
        Type operator>>(int shift) const { return get() >> shift; } \
        _##Type& operator<<=(int shift) { set(get() << shift); return *this; } \
        _##Type& operator>>=(int shift) { set(get() >> shift); return *this; } \
        \
        _##Type& operator++() { set(get() + 1); return *this; } \
        _##Type& operator--() { set(get() - 1); return *this; } \
        \
        operator Type() const { return get(); } \
    }; \
}; \
public: Class##Type##Name::_##Type Name = Class##Type##Name::_##Type(this, Initial); \
private: const Type& get##Class##Type##Name() const Get void set##Class##Type##Name(const Type& value) Set


// 16 bit
#define Proxy16(Type, Name, Class, Get, Set, Initial) \
private: struct Class##Type##Name{ \
    class _##Type{ \
        Type data; \
        unsigned short offset; \
        \
        Class* ptr() const { return reinterpret_cast<Class*>( \
            reinterpret_cast<std::uintptr_t>(this) - offset); \
        } \
        \
        friend Class; \
        public: \
        _##Type(const Class* _ptr, const Type& initial) { \
            offset = reinterpret_cast<std::uintptr_t>(this) - \
                reinterpret_cast<std::uintptr_t>(_ptr); \
            data = initial; \
        } \
        \
        inline const Type& get() const { return ptr()->get##Class##Type##Name(); } \
        inline void set(const Type& value) { ptr()->set##Class##Type##Name(value); } \
        \
        Type operator+(const Type& value) const { return get() + value; } \
        Type operator-(const Type& value) const { return get() - value; } \
        Type operator*(const Type& value) const { return get() * value; } \
        Type operator/(const Type& value) const { return get() / value; } \
        Type operator%(const Type& value) const { return get() % value; } \
        \
        _##Type& operator+=(const Type& value) { set(get() + value); return *this; } \
        _##Type& operator-=(const Type& value) { set(get() - value); return *this; } \
        _##Type& operator*=(const Type& value) { set(get() * value); return *this; } \
        _##Type& operator/=(const Type& value) { set(get() / value); return *this; } \
        _##Type& operator%=(const Type& value) { set(get() % value); return *this; } \
        \
        bool operator==(const Type& value) const { return get() == value; } \
        bool operator!=(const Type& value) const { return get() != value; } \
        bool operator<(const Type& value)  const { return get() < value; } \
        bool operator<=(const Type& value) const { return get() <= value; } \
        bool operator>(const Type& value)  const { return get() > value; } \
        bool operator>=(const Type& value) const { return get() >= value; } \
        \
        bool operator!() const { return !static_cast<bool>(get()); } \
        bool operator&&(const Type& value) const { return static_cast<bool>(get()) && static_cast<bool>(value); } \
        bool operator||(const Type& value) const { return static_cast<bool>(get()) || static_cast<bool>(value); } \
        \
        Type operator&(const Type& value) const { return get() & value; } \
        Type operator|(const Type& value) const { return get() | value; } \
        Type operator^(const Type& value) const { return get() ^ value; } \
        Type operator~() const { return ~get(); } \
        \
        _##Type& operator&=(const Type& value) { set(get() & value); return *this; } \
        _##Type& operator|=(const Type& value) { set(get() | value); return *this; } \
        _##Type& operator^=(const Type& value) { set(get() ^ value); return *this; } \
        \
        Type operator<<(int shift) const { return get() << shift; } \
        Type operator>>(int shift) const { return get() >> shift; } \
        _##Type& operator<<=(int shift) { set(get() << shift); return *this; } \
        _##Type& operator>>=(int shift) { set(get() >> shift); return *this; } \
        \
        _##Type& operator++() { set(get() + 1); return *this; } \
        _##Type& operator--() { set(get() - 1); return *this; } \
        \
        operator Type() const { return get(); } \
    }; \
}; \
public: Class##Type##Name::_##Type Name = Class##Type##Name::_##Type(this, Initial); \
private: const Type& get##Class##Type##Name() const Get void set##Class##Type##Name(const Type& value) Set

// 32 bit
#define Proxy32(Type, Name, Class, Get, Set, Initial) \
private: struct Class##Type##Name{ \
    class _##Type{ \
        Type data; \
        unsigned int offset; \
        \
        Class* ptr() const { return reinterpret_cast<Class*>( \
            reinterpret_cast<std::uintptr_t>(this) - offset); \
        } \
        \
        friend Class; \
        public: \
        _##Type(const Class* _ptr, const Type& initial) { \
            offset = reinterpret_cast<std::uintptr_t>(this) - \
                reinterpret_cast<std::uintptr_t>(_ptr); \
            data = initial; \
        } \
        \
        inline const Type& get() const { return ptr()->get##Class##Type##Name(); } \
        inline void set(const Type& value) { ptr()->set##Class##Type##Name(value); } \
        \
        Type operator+(const Type& value) const { return get() + value; } \
        Type operator-(const Type& value) const { return get() - value; } \
        Type operator*(const Type& value) const { return get() * value; } \
        Type operator/(const Type& value) const { return get() / value; } \
        Type operator%(const Type& value) const { return get() % value; } \
        \
        _##Type& operator+=(const Type& value) { set(get() + value); return *this; } \
        _##Type& operator-=(const Type& value) { set(get() - value); return *this; } \
        _##Type& operator*=(const Type& value) { set(get() * value); return *this; } \
        _##Type& operator/=(const Type& value) { set(get() / value); return *this; } \
        _##Type& operator%=(const Type& value) { set(get() % value); return *this; } \
        \
        bool operator==(const Type& value) const { return get() == value; } \
        bool operator!=(const Type& value) const { return get() != value; } \
        bool operator<(const Type& value)  const { return get() < value; } \
        bool operator<=(const Type& value) const { return get() <= value; } \
        bool operator>(const Type& value)  const { return get() > value; } \
        bool operator>=(const Type& value) const { return get() >= value; } \
        \
        bool operator!() const { return !static_cast<bool>(get()); } \
        bool operator&&(const Type& value) const { return static_cast<bool>(get()) && static_cast<bool>(value); } \
        bool operator||(const Type& value) const { return static_cast<bool>(get()) || static_cast<bool>(value); } \
        \
        Type operator&(const Type& value) const { return get() & value; } \
        Type operator|(const Type& value) const { return get() | value; } \
        Type operator^(const Type& value) const { return get() ^ value; } \
        Type operator~() const { return ~get(); } \
        \
        _##Type& operator&=(const Type& value) { set(get() & value); return *this; } \
        _##Type& operator|=(const Type& value) { set(get() | value); return *this; } \
        _##Type& operator^=(const Type& value) { set(get() ^ value); return *this; } \
        \
        Type operator<<(int shift) const { return get() << shift; } \
        Type operator>>(int shift) const { return get() >> shift; } \
        _##Type& operator<<=(int shift) { set(get() << shift); return *this; } \
        _##Type& operator>>=(int shift) { set(get() >> shift); return *this; } \
        \
        _##Type& operator++() { set(get() + 1); return *this; } \
        _##Type& operator--() { set(get() - 1); return *this; } \
        \
        operator Type() const { return get(); } \
    }; \
}; \
public: Class##Type##Name::_##Type Name = Class##Type##Name::_##Type(this, Initial); \
private: const Type& get##Class##Type##Name() const Get void set##Class##Type##Name(const Type& value) Set

#endif 
