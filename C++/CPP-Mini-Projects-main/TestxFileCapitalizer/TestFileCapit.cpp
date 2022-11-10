#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ostream>

int main(int argc, char **argv)
{
    std::fstream fs(argv[1]);
    std::ofstream of;
    std::string str;
    std::vector<std::string> vec;
    char symbol;
    //Kardum enq File

    while (!fs.eof())
    {
        fs.get(symbol);
        if (symbol >= 'A' && symbol <= 'z')
        {
            str.push_back(symbol);
        }
        else
        {
            if (str[0] >= 'a' && str[0] <= 'z')
            {
                str[0] -= 32;
            }
            if (str[str.size() - 1] >= 'a' && str[str.size() - 1] <= 'z')
            {
                str[str.size() - 1] -= 32;
            }
            vec.push_back(str);
            str = "";
        }
        if ((symbol < 'A' || symbol > 'z'))
        {
            str.push_back(symbol);
            vec.push_back(str);
            str = "";
        }
    }

    of.open(argv[1]);
    for (int i = 0; i < vec.size(); i++)
    {
        of << vec[i];
    }
}