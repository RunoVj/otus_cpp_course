#include "ip_filter.h"


int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
    try {
        std::ifstream f{R"(C:\Users\RunoVj\CLionProjects\otus_cpp_course\resource\ip_filter.tsv)"}; // TODO how to make it relative?
        parse_ip(f);
    }

    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}