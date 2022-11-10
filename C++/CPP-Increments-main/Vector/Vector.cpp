#include <iostream>
#include "Vector.h"

int main()
{
    Vector<char> h;
    Vector<std::string> v;
    h.push_back('a');
    h.push_back('b');
    h.push_back('c');
    h.push_back('d');
    v.push_back("ba");
    v.push_back("as");
    v.push_back("fa");
    v.push_back("de");

    v = h;
    // h.push_back(5);
    // //h.insert(1, 25);
    // // h.pop_back();
    // // h.pop_front();
    // h.erase(2);
    std::cout << std::boolalpha << h.empty() << std::endl;
    //h.print();
    std::cout<<std::endl;
    v.print();
    // std::cout << h << std::endl;
    system("pause");
}