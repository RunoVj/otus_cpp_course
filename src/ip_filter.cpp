#include "ip_filter.h"

using std::ifstream;


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


std::array<int, 4> parse4byte_ip_from_str(const std::string &str_ip)
{
    auto vip = split(str_ip, '.');
    assert(vip.size() == 4);
    std::array<int, 4> ip = {
        atoi(vip[0].c_str()),
        atoi(vip[1].c_str()),
        atoi(vip[2].c_str()),
        atoi(vip[3].c_str())
    };
    return ip;
}



void parse_ip(std::istream &is)
{
    std::vector<std::array<int, 4>> ip_pool;
    for (std::string line; std::getline(is, line);) {
        auto v = split(line, '\t').at(0);
        ip_pool.push_back(parse4byte_ip_from_str(v));
    }

    std::sort(ip_pool.begin(), ip_pool.end(),  std::greater<>());
    /// reverse lexicographically sort
    for (auto v : ip_pool) {
        std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
    }

    /// filter by first byte and output
    for (auto v : ip_pool) {
        if (pattern_matches(0, v, 1)) {
            std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
        }
    }

    /// filter by first and second bytes and output
    for (auto v : ip_pool) {
        if (pattern_matches(0, v, 46, 70)) {
            std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
        }
    }

    /// filter by any byte and output
    for (auto v : ip_pool) {
        if (std::any_of(v.begin(), v.end(), [](int v) {return v == 46;})) {
            std::cout << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
        }
    }
}
