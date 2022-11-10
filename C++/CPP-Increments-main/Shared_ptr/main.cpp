#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
int main()
{
    std::vector<int> arr{1, 2, 3, 4, 5};
    for (auto x : arr)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    std::cout << arr.size() << std::endl;
    std::cout << std::endl;

    arr.erase(arr.begin() + 1);
    for (auto x : arr)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    std::cout << arr.size() << std::endl;
}