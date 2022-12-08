#pragma once

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>


template <typename T>
typename std::enable_if_t<std::is_integral<T>::value> print_ip(T v) {
    for (size_t i = sizeof(T); i > 0; --i) {
        std::cout << ((v >> ((i - 1) * 8)) & 0xFF) << ((i > 1) ? "." : "\n");
    }
}

template<typename T>
typename std::enable_if_t<std::is_convertible_v<const char*, T>> print_ip(T v) {
    std::cout << v << std::endl;
}

template<typename T>
struct is_container : std::false_type {};

template<typename... Arg>
struct is_container<std::vector<Arg...>>: std::true_type {};

template<typename... Arg>
struct is_container<std::list<Arg...>>: std::true_type {};

template<typename T>
typename std::enable_if_t<is_container<T>::value>  print_ip(T v) {
    for (const auto &i : v) {
        std::cout << i << ((i != v.back()) ? "." : "\n");
    }
}

//
//template<typename T>
//struct is_tuple_with_identical_types : std::false_type {};
//
//template<typename... Args>
//is_tuple_with_identical_types<