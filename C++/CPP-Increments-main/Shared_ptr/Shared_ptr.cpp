#include <iostream>
#include "Shared_ptr.h"
using namespace spi;

auto del = [](int *tmp)
{
    std::cout << "sadadasda" << std::endl;
};

int main()
{
    shared_ptr<int> a(new int(15));
    shared_ptr<int> b(new int(4), del);

    // std::cout << a.use_count() << std::endl;
    // std::cout << *a << std::endl;
    // std::cout << b.use_count() << std::endl;
    // std::cout << *b << std::endl;
}