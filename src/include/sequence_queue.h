//
// Created by RunoVj on 5/28/2022.
//
#pragma once
#include "allocator.h"
#include <iostream>


template<typename T, typename Allocator = std::allocator<T>>
class SequenceQueue
{
public:
    SequenceQueue() :
        _size{0},
        _head{nullptr},
        _tail{nullptr}
    {}

    ~SequenceQueue()
    {
        _allocator.deallocate(_tail, _size);
    }

    bool is_empty()
    {
        return _head == nullptr && _tail == nullptr;
    }

    bool is_full()
    {
        if (is_empty()) {
            return true;
        }
        return static_cast<size_t>((_head - _tail)) == _size - 1;
    }

    void push_back(T &obj) {
        if (is_full()) {
            _tail = _allocator.allocate(1);
            ++_size;
            _allocator.construct(_tail, obj);
            if (_head == nullptr) {
                _head = _tail;
            }
        }
        else {
            *(--_tail) = obj;
        }
    }

    T pop_front()
    {
        try {
            if (is_empty()) {
                throw std::range_error("Queue is empty! ");
            }
            auto ret_val = *_head;
            if (_head == _tail) {
                _head = _tail = nullptr;
            }
            --_head;
            return ret_val;
        }
        catch (const char* str)
        {
            std::cout << std::endl << str << std::endl;
        }
        return T{};
    }

    T back()
    {
        if (_tail != nullptr) {
            return *_tail;
        }
        else {
            return T{};
        }
    }

    T front()
    {
        if (_head != nullptr) {
            return *_head;
        }
        else {
            return T{};
        }
    }

private:
    Allocator _allocator;
    size_t _size;
    T* _head;
    T* _tail;
};


