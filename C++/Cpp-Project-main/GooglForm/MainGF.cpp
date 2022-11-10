#include <iostream>
#include <string>
#include "Admin.cpp"
#include "Student.h"

int main()
{
    int action_select;
    int user_select;
    std::cout << "Hello My Friend\n"
              << "Please Choose who you are?\n"
              << "1. Admin\t"
              << "2. Student\n"
              << "Enter number: ";
    std::cin >> user_select;
    if (user_select == 1)
    {
        Admin a;
        a.security();
        std::cout << "Select what to do?\n"
                  << "1) Add a test\t"
                  << "2) See the Students results" << std::endl;
        std::cin >> action_select;
        if (action_select == 1)
        {
            a.a_info();
            a.add_questions();
        }
        if (action_select == 2)
        {
            a.security();
            a.stud_result();
        }
        else
        {
            std::cout << "Wrong number for Action....";
            exit(0);
        }
    }
    if (user_select == 2)
    {
        Student b;
        b.info_stud();
        b.st_test();
        b.stud_result_save();
    }
    else if (user_select != 1 && user_select != 2)
    {
        std::cout << "Wrong number for Urser....";
        exit(0);
    }
    system("pause");
}