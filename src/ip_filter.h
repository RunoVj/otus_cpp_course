#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>

/**
 * ("",  '.') -> [""]
 * ("11", '.') -> ["11"]
 * ("..", '.') -> ["", "", ""]
 * ("11.", '.') -> ["11", ""]
 * (".11", '.') -> ["", "11"]
 * ("11.22", '.') -> ["11", "22"]
 */
std::vector<std::string> split(const std::string &str, char d);


/// ("11.22.33.44") -> [11, 22, 33, 44]
std::array<int, 4> parse4byte_ip_from_str(const std::string &str_ip);


template<typename... Args>
bool pattern_matches([[maybe_unused]] int bias,
                     [[maybe_unused]] const std::array<int, 4> &ip)
{
    return false;
}


template<typename T, typename... Args>
bool pattern_matches(int bias, const std::array<int, 4> &ip, T t, Args... args) {
    if (ip[bias] != t) {
        return false;
    }
    else if (sizeof...(args) == 0) {
        return true;
    }
    else {
        return pattern_matches(++bias, ip, args...);
    }
}


/// main function for ip parser
void parse_ip(std::istream &is);

