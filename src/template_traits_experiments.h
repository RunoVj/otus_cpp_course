#pragma once

/// base
template<typename T>
struct type_is {
    using type = T;
};

template<bool C, typename T>
struct enable_if : type_is<T> {};

template<typename T>
struct enable_if<false, T> {};

/// remove const
template<typename T>
struct remove_const : type_is<T> {};

template<typename T>
struct remove_const<const T> : type_is<T> {};

template<typename T>
using remove_const_t = typename remove_const<T>::type;


/// remove volatile
template<typename T>
struct remove_volatile : type_is<T> {};

template<typename T>
struct remove_volatile<volatile T> : type_is<T> {};

/// remove const and volatile
template<typename T>
struct remove_cv : type_is<T> {};

template<typename T>
struct remove_cv<volatile T> : type_is<T> {};

template<typename T>
struct remove_cv<const T> : type_is<T> {};

template<typename T>
struct remove_cv<const volatile T> : type_is<T> {};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

/// factorial
template<int P>
struct factorial {
    static constexpr int value = P * factorial<P-1>::value;
};

template<>
struct factorial<0> {
    static constexpr int value = 1;
};

template<int P>
static constexpr int factorial_v = factorial<P>::value;

/// int
template<typename T>
struct is_int {
    static constexpr bool value = false;
};

template<typename T>
static constexpr bool is_int_v = is_int<T>::value;


template<>
struct is_int<int> {
    static constexpr bool value = true;
};


/// abs
template<int V>
struct abs_v {
    static constexpr int value = V > 0 ? V : -V;
};

/// is same
template<typename T1, typename T2>
struct is_same {
    static constexpr int value = false;
};

template<typename T>
struct is_same<T, T>  {
    static constexpr int value = true;
};

/// is null pointer
template<typename T>
struct is_null_pointer : is_same<remove_cv_t<T>, std::nullptr_t>{};

/// condition
template<bool C, typename T, typename U>
struct conditional : type_is<T> {};

template<typename T, typename U>
struct conditional<false, T, U> : type_is<U> {};
