#pragma once

#include <iostream>
#include <malloc.h>
#include <map>


template<typename T, int allocation_step>
struct MyAllocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = MyAllocator<U, allocation_step>;
    };

    MyAllocator() :
        _allocated{0},
        _available{0},
        _p{nullptr}
    {
        _p = std::malloc(allocation_step * sizeof(T));
        if (!_p) {
            throw std::bad_alloc();
        }
        _allocated = _available = allocation_step;
    };

    ~MyAllocator() = default;

    template<typename U>
    MyAllocator(const MyAllocator<U, allocation_step>&) {
    }

    T* allocate(std::size_t n) {
        if (n <= _available) {
            _available -= n;
            return reinterpret_cast<T*>(_p) + _available;
        }
        throw std::bad_alloc();

        /// FIXME how to increase allocated memory??
        /// prev allocated memory steps + one new
//        auto k = _allocated / allocation_step + 1;
//        if (n - _available > allocation_step) { /// allocation step is too small
//            k += (n - _available) / allocation_step;
//        }
//
//        auto new_memory = std::realloc(_p, k * allocation_step * sizeof(T));
//        if (!new_memory) {
//            free(_p);
//            throw std::bad_alloc();
//        }
//        _p = new_memory;
//        _available = k * allocation_step - _allocated - n;
//        _allocated = k * allocation_step;
//        return reinterpret_cast<T*>(_p) + _available;
    }

    void deallocate(T *p, std::size_t n = 0) {
        (void) n;
        (void) p;
        _available += n;
        if (_allocated == _available) {
            std::free(_p);
            std::cout << "Free memory" << std::endl;
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }

private:
    size_t _allocated;
    size_t _available;
    void* _p;
};
