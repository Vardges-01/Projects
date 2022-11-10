#include <iostream>
#include <string>
#include <fstream>
#ifndef ADMIN_H
#define ADMIN_H

class Admin
{
private:
    std::string file_name;
    std::string sub_name;
    std::ofstream fs;
    std::ofstream sub;

public:
    void security();
    void add_questions();
    void a_info();
    void stud_result();
    ~Admin();
};

void Admin::a_info()
{
    std::cout << "\t\t Helo my friend.\n";
    std::cout << "\t\t Info for you.\n"
              << std::endl;
    std::cout << "1.Enter '+' if you want to add a question :" << std::endl;
    std::cout << "2.Or Enter '-' if No :\n"
              << std::endl;
}

void Admin::security()
{
    int pasword;
    std::cout << "Please Enter Admin Password: ";
    std::cin >> pasword;
    if (pasword != 1111)
    {
        std::cout << "Wrong Password..." << std::endl;
        exit(0);
    }
    return;
}

void Admin::add_questions()
{
    char num;
    char hnum = 65;
    std::string question;
    std::string answers;
    std::cout << "Enter Subject name ( Mat / Fiz / Prog )" << std::endl;
    std::cin >> sub_name;
    sub.open(sub_name += ".txt", std::ofstream::app);
    std::cout << "Enter Test name: ";
    std::cin >> file_name;
    fs.open(file_name += ".txt");
    sub << file_name + "\n";
    std::cin.get();
harc:
    // Question

    num = 49;
    std::cout << "Enter question" << std::endl;
    question = "";
    std::getline(std::cin, question);
    question = ": " + question;
    fs << (hnum++) + question + "\n";

    //Answers
answ:
    std::cout << "Enter answer: " << std::endl;
    std::getline(std::cin, answers);
    answers = ") " + answers;
    fs << "\t";
    fs << (num++) + answers + "\n";
    std::cout << "Add a Answer? (+ / -): ";
    std::getline(std::cin, answers);
    if (answers == "+")
    {
        goto answ;
    }
    else if (answers != "-")
    {
        std::cout << "Error...." << std::endl;
        exit(0);
    }

    // Corect Answer

    std::cout << "Enter correct answer: ";
    std::getline(std::cin, answers);
    fs << "W: " << answers + "\n\n";
    std::string harcka;

    // More questions

    std::cout << "Have you any questions? ( yes / no )" << std::endl;
    std::getline(std::cin, harcka);
    if (harcka == "yes")
    {
        goto harc;
    }
    else
    {
        sub.close();
        fs.close();
        exit(0);
    }
}

void Admin::stud_result()
{
    std::ifstream stud_res;
    std::string tok;
    stud_res.open("student_result.txt");
    while (!stud_res.eof())
    {
        std::getline(stud_res, tok);
        std::cout << tok << std::endl;
    }
    return;
}

Admin::~Admin() {}

#endif // ADMIN_H