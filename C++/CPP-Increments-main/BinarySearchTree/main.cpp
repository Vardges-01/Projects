#include <iostream>
#include "BinST.h"

int main()
{
    BinarSearch<int> a;
    a.insert(25);
    a.insert(15);
    a.insert(10);
    a.insert(4);
    // a.insert(12);
    // a.insert(22);
    // a.insert(18);
    // a.insert(24);
    // a.insert(50);
    // a.insert(35);
    // a.insert(31);
    // a.insert(44);
    // a.insert(70);
    // a.insert(66);
    // a.insert(90);
    a.print();
    a.esim();
    a.print();
}