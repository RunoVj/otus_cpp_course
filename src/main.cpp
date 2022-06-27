#include "allocator.h"
#include <map>
#include "factorial.h"
#include "sequence_queue.h"


int main()
{
    {
        /// создание экземпляра std::map<int, int>
        std::map<int, int> m;
        /// заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        for (int i = 0; i < 10; ++i) {
            m.insert(std::pair<int, int>(i, factorial(i)));
        }

        /// это надо???
        for (const auto& elem : m) {
            std::cout << elem.first << ": " << elem.second << "  ";
        }
        std::cout << std::endl;
    }

    {
        /// создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
        std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 10>> custom_allocator_map;

        /// заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
        for (int i = 0; i < 10; ++i) {
            custom_allocator_map.insert(std::pair<int, int>(i, factorial(i)));
        }
        /// вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
        for(const auto& elem : custom_allocator_map) {
            std::cout << elem.first << ": " << elem.second << "  ";
        }
        std::cout << std::endl;
    }

    {
        /// создание экземпляра своего контейнера для хранения значений типа int
        SequenceQueue<int, MyAllocator<int, 10>> my_queue;

        /// заполнение 10 элементами от 0 до 9
        for (int i = 0; i < 10; ++i) {
            my_queue.push_back(i);
        }

        /// это надо?
        for (int i = 0; i < 10; ++i) {
            std::cout << my_queue.pop_front() << " ";
        }
        std::cout << std::endl;
    }


    /// создание экземпляра своего контейнера для хранения значений типа int
    /// с новым аллокатором,ограниченным 10 элементами
    {
        SequenceQueue<int, MyAllocator<int, 10>> my_queue_with_my_allocator;

        /// заполнение 10 элементами от 0 до 9
        for (int i = 0; i < 10; ++i) {
            my_queue_with_my_allocator.push_back(i);
        }

        /// вывод на экран всех значений, хранящихся в контейнере
        for (int i = 0; i < 10; ++i) {
            std::cout << my_queue_with_my_allocator.pop_front() << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}