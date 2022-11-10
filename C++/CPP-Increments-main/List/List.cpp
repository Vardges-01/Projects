#include "List.h"

int main()
{
    try
    {
        forward_list<int> b;
        b.push_back(1);
        b.push_back(2);
        b.push_back(2);
        b.push_back(3);
        b.print();
        

        system("pause");
    }
    catch (const char *msg)
    {
        std::cerr << msg << '\n';
    }
}