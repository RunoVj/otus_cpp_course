//
// Created by RunoVj on 2/21/2023.
//
#pragma once

#include <algorithm>
#include <cstdlib>
#include <map>


template<typename T, T initial_value, size_t N = 2>
class Matrix;

template<typename T, T initial_value>
class Matrix<T, initial_value, 1> {
public:
    Matrix() = default;
    size_t size() const
    {
        return _m.size();
    };

    T &operator[](const std::size_t idx)
    {
        if (_m.count(idx)) {
            return _m[idx];
        }
        else {
            return _default;
        }
    }

private:
    T _default = initial_value;
    std::map<size_t, T> _m{};
};

template<typename T, T initial_value, size_t N>
class Matrix {
public:
    constexpr static int Dimension = N - 1;
    Matrix() = default;
    size_t size() const
    {
        size_t sum = 0;
        std::for_each(_m.begin(), _m.end(), [&](const auto &n) {
            sum += n.second.size();
        });
        return sum;
    };

    Matrix<T, initial_value, N - 1> &operator[](const std::size_t idx)
    {
        if (!_m.count(idx)) {
            _m.insert({idx, Matrix<T, initial_value, Dimension>{}});
        }
        return _m[idx];
    }

private:
    T _default = initial_value;
    std::map<size_t, Matrix<T, initial_value, Dimension>> _m;
};
