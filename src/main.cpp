#include "allocator.h"
#include <vector>
#include <map>

/**

- создание экземпляра своего контейнера для хранения значений типа int
- заполнение 10 элементами от 0 до 9
- создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
ограниченным 10 элементами
- заполнение 10 элементами от 0 до 9
- вывод на экран всех значений, хранящихся в контейнере
 */

int main()
{
    /// создание экземпляра std::map<int, int>
    std::map<int, int> m;
    /// заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    for (int i = 0; i < 10; ++i) {
        m.insert(std::pair<int, int>(i, factorial(i)));
    }

    /// это надо???
    for(const auto& elem : m) {
        std::cout << elem.first << ": " << elem.second << "  ";
    }
    std::cout << std::endl;

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

//    auto v = std::vector<int, my_allocator<int>>{};
//    // v.reserve(5);
//    for (int i = 0; i < 6; ++i) {
//        std::cout << "vector size = " << v.size() << std::endl;
//        v.emplace_back(i);
//        std::cout << std::endl;
//    }
//
//    auto m = std::map<
//        int,
//        float,
//        std::less<int>,
//        my_allocator<
//            std::pair<
//                const int, float
//            >
//        >
//    >{};
//
//    for (int i = 0; i < 1; ++i) {
//        m[i] = static_cast<float>(i);
//    }

    return 0;
}