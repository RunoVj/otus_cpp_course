#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>


/// @brief ip printer for integer values
/// @details This template function can print integers types in a "ip-like" view.
/// std::is_integral uses to distinguish this function from different types prints
template <typename T>
typename std::enable_if_t<std::is_integral<T>::value> print_ip(T v) {
    for (size_t i = sizeof(T); i > 0; --i) {
        std::cout << ((v >> ((i - 1) * 8)) & 0xFF) << ((i > 1) ? "." : "\n");
    }
}

/// @brief ip printer for string values
/// @details This template function can print string and const char* types
/// in a "ip-like" view.
/// std::is_integral uses to distinguish this function from different types prints
template<typename T>
typename std::enable_if_t<std::is_convertible_v<const char*, T>> print_ip(T v) {
    std::cout << v << std::endl;
}


/// @brief help trait to distinguish std::vector and std::list from other containers
template<typename T>
struct is_container : std::false_type {};

template<typename... Arg>
struct is_container<std::vector<Arg...>>: std::true_type {};

template<typename... Arg>
struct is_container<std::list<Arg...>>: std::true_type {};

/// @brief ip printer for std::list and std::vector types
/// @details This template function can print std::list and std::vector containers
/// in a "ip-like" view.
/// is_container uses to distinguish this function from different types prints
template<typename T>
typename std::enable_if_t<is_container<T>::value>  print_ip(T v) {
    for (const auto &i : v) {
        std::cout << i << ((i != v.back()) ? "." : "\n");
    }
};


/// @brief help trait to identify two things: Is T a tuple and is it tuple with same values
template<typename T, typename... Args>
struct is_tuple_with_identical_types {};

template<typename T>
struct is_tuple_with_identical_types<T> : std::false_type {};

template<typename... Args>
struct is_tuple_with_identical_types<std::tuple<Args...>>: std::true_type {};

template<typename T, typename U, typename... Args>
struct is_tuple_with_identical_types<T, U, Args...> {
  static constexpr bool value = std::is_same_v<T, U> && is_tuple_with_identical_types<U, Args...>::value;
};



/// @brief ip printer for std::tuple types
/// @details This template function can print std::tuple in a "ip-like" view.
/// is_tuple_with_identical_types uses to distinguish this function from different types prints
/// There is '... op pack' construction uses
/// where "op" in our scenario is the comma operator, and pack is the expression containing our
/// tuple in an unexpanded context like:
/// (..., (std::cout << std::get<I>(myTuple))
template<typename T, size_t... I>
typename std::enable_if_t<is_tuple_with_identical_types<T>::value> print_ip(const T& _tup, std::index_sequence<I...>)
{
    (..., (std::cout << (I == 0? "" : ".") << std::get<I>(_tup)));
    std::cout << std::endl;
}

template<typename... T>
void print_ip(const std::tuple<T...>& t)
{
    print_ip(t, std::make_index_sequence<sizeof...(T)>());
}