#include <iostream>
#include <forward_list>
#include <list>
#include <vector>
using namespace std;

void rotate(vector<int> &nums, int k)
{
    vector<int>::iterator it = nums.begin();
    int size = nums.size() - 1;

    for (int i = 0; i < k; ++i)
    {
        it = nums.begin();
        nums.insert(it, nums[size]);
        nums.pop_back();
    }
}

int main()
{
    vector<int> vec{-1,-100,3,99};
    rotate(vec,2);
}
