#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#ifndef STUDENT_H
#define STUDENT_H

class Student
{
private:
    std::string name;
    std::string subject;
    int evalu;
    int age;
    int answer_count;

public:
    void info_stud();
    void st_test();
    void stud_result_save();
    ~Student();
};

void Student::info_stud()
{
    std::cout << "Pleas enter your name: ";
    std::cin >> name;
    std::cout << "Please enter your age: ";
    std::cin >> age;
    return;
}

void Student::st_test()
{
    evalu = 0;
    int count = 0;
    char answer;
    std::vector<char> answ;
    std::vector<std::string> answ_tf;
    std::ifstream sub_ques;
    std::string yn;
    std::cout << "Helloo dear " << name << std::endl;
    std::cout << "Do you want to start the test? ( Yes / No ): ";
    std::cin >> yn;
    if (yn == "yes")
    {
        std::cout << "Please enter Subject name? ( Mat / Fiz / Prog ): ";
        std::cin >> subject;
        std::string token;
        std::vector<std::string> str;
        srand(time(0));
        std::ifstream fs;
        fs.open(subject + ".txt");
        while (!fs.eof())
        {
            std::getline(fs, token);
            str.push_back(token);
            ++count;
        }
        fs.close();

        sub_ques.open(str[rand() % (count - 1)]);

        std::cout << std::endl;

        while (!sub_ques.eof())
        {
            std::getline(sub_ques, token);
            if (token[0] != 'W')
            {
                std::cout << token << std::endl;
            }
            else
            {
                answ.push_back(token[3]);
            }
        }
        answer_count = answ.size();
        for (int i = 0; i < answer_count; ++i)
        {
            std::cout << "Please answer the question " << i + 1 << ": ";
            std::cin >> answer;
            if (answer == answ[i])
            {
                answ_tf.push_back("true");
                ++evalu;
            }
            else
            {
                answ_tf.push_back("false");
            }
        }
        std::cout << "\nYour test result.\n"
                  << std::endl;
        for (int i = 0; i < answer_count; ++i)
        {
            std::cout << i + 1 << ") " << answ_tf[i] << "\n";
        }
        std::cout << "Result - " << evalu << " / " << answer_count << std::endl;
    }
    sub_ques.close();
}

void Student::stud_result_save()
{
    std::ofstream stud;
    stud.open("student_result.txt", std::ofstream::app);
    stud << "Subject: " << subject << ".\n";
    stud << "Student Name: " << name << ".\n";
    stud << "Student Age: " << age << ".\n";
    stud << "Student Evaluation: " << evalu << " / " << answer_count << ".\n\n";
}

Student::~Student()
{
}

#endif // STUDENT_H