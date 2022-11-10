#include "FrankList.h"

int main()
{
    FrankList<int> p{1,8,6,4,7,0};
    FrankList<int>::iterator it=p.begin();
    *it;
    p.insert(it,9);
    std::cout << p;
    p.as_print();
    p.ds_print();
    p.tail_print();
    system("pause");
    return 0;
}