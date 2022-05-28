#include <iostream>
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
        _available_memory{0},
        _memory_p{nullptr}
    {
        _memory_p = reinterpret_cast<T *>(std::malloc(allocation_step * sizeof(T)));
        if (!_memory_p) {
            throw std::bad_alloc();
        }
        _available_memory = allocation_step;
    };

    ~MyAllocator() = default;

    template<typename U>
    MyAllocator(const MyAllocator<U, allocation_step>&) {
    }

    T *allocate(std::size_t n) {
        if (n <= _available_memory) {
            _available_memory -= n;
            return _memory_p + _available_memory;
        }
        throw std::bad_alloc();
    }

    void deallocate(T *p, std::size_t n) {
        (void) n;
        (void) p;
        _available_memory += n;
        if (_available_memory == allocation_step) {
            std::free(_memory_p);
            std::cout << "Free memory";
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
    size_t _available_memory;
    T* _memory_p;
};
