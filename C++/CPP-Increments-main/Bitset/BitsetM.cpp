#include <iostream>
#include "Bitset.h"

int main()
{

    Bitset<55> b(5);
    std::cout << b << std::endl;
    // b.set(54);
    std::cout<<b<<std::endl;
    // std::cout<<b.to_ulong()<<std::endl;
    // std::cout<<b.to_ullong()<<std::endl;

    // b<<=1;
    // std::cout <<  b << std::endl;
}