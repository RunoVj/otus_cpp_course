#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>

using std::cerr;
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;



// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));
    return r;
}


// ("11.22.33.44") -> [11, 22, 33, 44]
std::array<int, 4> parse_ip(const std::string &str_ip)
{
    auto vip = split(str_ip, '.');
    std::array<int, 4> ip = {
        atoi(vip[0].c_str()),
        atoi(vip[1].c_str()),
        atoi(vip[2].c_str()),
        atoi(vip[3].c_str())
    };
    return ip;
}


bool pattern_matches(const std::array<int, 4> &ip,  int bias)
{
    return false;
}

template<typename T, typename... Args>
bool pattern_matches(const std::array<int, 4> &ip, int bias, T t, Args... args) {
    if (ip[bias] != t) {
        return false;
    }
    else if (sizeof...(args) == 0) {
        return true;
    }
    else {
        return pattern_matches(ip, ++bias, args...);
    }
}


int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::array<int, 4>> ip_pool;
        std::fstream f{R"(C:\Users\RunoVj\CLionProjects\otus_cpp_course\resource\ip_filter.tsv)"}; // TODO how to make it relative?
        for (std::string line; std::getline(f, line);) {
            auto v = split(line, '\t').at(0);
            ip_pool.push_back(parse_ip(v));
        }

        std::sort(ip_pool.begin(), ip_pool.end(),  std::greater<>());
        // reverse lexicographically sort
//        for (auto v : ip_pool) {
//            std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
//        }


        // filter by first byte and output
        // ip = filter(1)
        for (auto v : ip_pool) {
            if (pattern_matches(v, 0, 1)) {
                std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
            }
        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        for (auto v : ip_pool) {
            if (pattern_matches(v, 0, 46, 70)) {
                std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
            }
        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // filter by any byte and output
        // ip = filter_any(46)
        for (auto v : ip_pool) {
            if (std::any_of(v.begin(), v.end(), [](int v) {return v == 46;})) {
                std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
            }
        }


        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }

    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
