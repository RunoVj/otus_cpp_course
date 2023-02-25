//
// Created by RunoVj on 2/21/2023.
//
#pragma once

#include <algorithm>
#include <cstdlib>
#include <map>
#include <stdexcept>

template<typename T, T initial_value, size_t N = 2>
class Matrix;

template<typename T, T initial_value>
class ProxyElement;

template<typename T, T initial_value>
class Matrix<T, initial_value, 1> {
public:
    Matrix() = default;
    size_t size() const
    {
        return _m.size();
    };

    ProxyElement<T, initial_value> operator[](const std::size_t idx)
    {
        auto value = initial_value;
        if (_m.count(idx)) {
            value = _m[idx];
        }
        return ProxyElement<T, initial_value>{*this, value, idx};
    }

    void set(T value, size_t key)
    {
        if (value != initial_value) {
            _m.insert_or_assign(key, value);
        }
        else {
            _m.erase(key);
        }
    }

    std::tuple<size_t, T> get_non_default(size_t idx) const
    {
        size_t i = 0;
        for (const auto &[key, value] : _m) {
            if (i == idx) {
                return std::make_tuple(key, T(value));
            }
            else {
                i++;
            }
        }
        throw std::logic_error("no element");
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

    void set(T value, size_t i, size_t j)
    {
        if (value != initial_value) {
            if (!_m.count(i)) {
                _m[i].set(value, j);
            }
        }
        else if (_m.count(i) != 0 && _m[i].size() == 0) {
            _m.erase(i);
        }
    }

    template<typename... Args>
    void set(T value, size_t i, size_t j, Args &&...args)
    {
        if (value != initial_value) {
            if (!_m.count(i)) {
                _m[i].set(value, j, args...);
            }
        }
        else if (_m.count(i) != 0 && _m[i].size() == 0) {
            _m.erase(i);
        }
    }

    decltype(auto) get_non_default(size_t idx) const
    {
        auto i = 0;
        for (const auto &[key, value] : _m) {
            auto cur_size = value.size();
            if (i + cur_size > idx) {
                return std::tuple_cat(std::tuple{key}, value.get_non_default(idx - i));
            }
            else {
                i += cur_size;
            }
        }
        throw std::logic_error{"no elements"};
    }

    struct Iterator {
        using value_type = Matrix;
        using pointer = Matrix *;
        using difference_type = size_t;

        Iterator(Matrix &matrix, size_t idx) :
            _matrix{matrix}, _idx{idx} {}

        void operator++() { _idx++; }
        void operator--() { --_idx; }

        decltype(auto) operator*()
        {
            return _matrix.get_non_default(_idx);
        }

        bool operator==(const Iterator &rhs) { return _idx == rhs._idx; }
        bool operator!=(const Iterator &rhs) { return _idx != rhs._idx; }

    private:
        Matrix<T, initial_value, N> &_matrix;
        size_t _idx;
    };

    Iterator begin() { return Iterator(*this, 0); }
    Iterator end() { return Iterator(*this, size()); }
    Iterator cbegin() const { return Iterator(*this, 0); }
    Iterator cend() const { return Iterator(*this, size()); }

private:
    T _default = initial_value;
    std::map<size_t, Matrix<T, initial_value, Dimension>> _m;
};

template<typename T, T initial_value>
class ProxyElement {
public:
    ProxyElement(Matrix<T, initial_value, 1> &matrix, T value, size_t key) :
        _matrix{matrix}, _value{value}, _key{key} {};

    ProxyElement &operator=(const T &rhs)
    {
        if (rhs != initial_value) {
            _value = rhs;
            _matrix.set(_value, _key);
        }
        return *this;
    };

    friend std::ostream &operator<<(std::ostream &os, const ProxyElement &obj)
    {
        os << obj._value;
        return os;
    }

    bool operator<(const T &rhs) const
    {
        return _value < rhs;
    }

    bool operator>=(const T &rhs) const
    {
        return !(_value < rhs);
    }

    bool operator>(const T &rhs) const
    {
        return _value >= rhs && !(_value > rhs);
    }

    bool operator<=(const T &rhs) const
    {
        return !(_value > rhs);
    }

    bool operator==(const T &rhs) const
    {
        return !(rhs < _value) && !(rhs > _value);
    }

private:
    Matrix<T, initial_value, 1> &_matrix;
    T _value;
    size_t _key;
};
