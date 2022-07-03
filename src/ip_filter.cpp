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
    if (vip.size() != 4) {
        throw std::runtime_error("Wrong ip size: '" + str_ip + "'");
    }

    try {
        std::array<int, 4> ip = {
            std::stoi(vip[0]),
            std::stoi(vip[1]),
            std::stoi(vip[2]),
            std::stoi(vip[3])
        };
        return ip;
    }
    catch (const std::invalid_argument &e) {
        throw std::invalid_argument(
            "Invalid argument for stoi function in ip " + str_ip);
    }
}


void parse_ip(std::istream &is, std::ostream &out)
{
    std::vector<std::array<int, 4>> ip_pool;
    for (std::string line; std::getline(is, line);) {
        auto v = split(line, '\t').at(0);
        ip_pool.push_back(parse4byte_ip_from_str(v));
    }

    std::sort(ip_pool.begin(), ip_pool.end(), std::greater<>());
    /// reverse lexicographically sort
    for (const auto &v: ip_pool) {
        out << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3] << std::endl;
    }

    /// filter by first byte and output
    for (const auto &v: ip_pool) {
        if (pattern_matches(0, v, 1)) {
            out << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3]
                << std::endl;
        }
    }

    /// filter by first and second bytes and output
    for (const auto &v: ip_pool) {
        if (pattern_matches(0, v, 46, 70)) {
            out << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3]
                << std::endl;
        }
    }

    /// filter by any byte and output
    for (const auto &v: ip_pool) {
        if (std::any_of(v.begin(), v.end(), [](int v) { return v == 46; })) {
            out << v[0] << '.' << v[1] << '.' << v[2] << '.' << v[3]
                << std::endl;
        }
    }
}
