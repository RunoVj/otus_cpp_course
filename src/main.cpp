#include "ip_filter.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    try {
        parse_ip(std::cin);
    }

    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}