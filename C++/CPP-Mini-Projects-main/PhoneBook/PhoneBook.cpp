#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
class PBook
{
private:
    std::string name;
    std::string lastname;
    std::string phone;
    std::string addres;
    std::ifstream fs;

public:
    PBook();
    void addContact();
    void editContact();
    void deleteContact();
    void seeContacts();
    ~PBook();
};

PBook::PBook()
{
    fs.open("Contacts.txt");
}

void PBook::addContact()
{
    std::ofstream adCon("Contacts.txt", std::ofstream::app);
    std::cout << "Please Enter Name and Last Name: ";
    std::cin >> name >> lastname;
    std::cout << "Enter Phone number: ";
    std::cin >> phone;
    std::cout << "Enter Addres: ";
    std::cin >> addres;
    adCon << "\n| | Name: " + name + " " + lastname + " - Phone: " + phone + " - Addres: " + addres + ";";
    adCon.close();
}
void PBook::editContact()
{
    std::ofstream edit;
    int n = 0;
    std::string str;
    std::vector<std::string> vec;
    while (!fs.eof())
    {
        getline(fs, str);
        vec.push_back(str);
    }
    std::cout << "Please Enter which contact you want to Edit: " << std::endl;
    std::cout<<vec[0]<<std::endl;
    for (int i = 1; i < vec.size(); i++)
    {
        std::cout << i << ") " << vec[i] << std::endl;
    }
    std::cin >> n;
    vec.erase(vec.begin() + n);
    std::cout << "Please enter new contact details" << std::endl;
    std::cout << "Please Enter Name and Last Name: ";
    std::cin >> name >> lastname;
    std::cout << "Enter Phone number: ";
    std::cin >> phone;
    std::cout << "Enter Addres: ";
    std::cin >> addres;
    str = "| | Name: " + name + " " + lastname + " - Phone: " + phone + " - Addres: " + addres + ";";
    vec.insert(vec.begin() + n, str);
    edit.open("Contacts.txt");
    edit << vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        edit << '\n'<< vec[i];
    }
    edit.close();
}
void PBook::deleteContact()
{
    std::ofstream del;

    int n = 0;
    std::string str;
    std::vector<std::string> vec;
    while (!fs.eof())
    {
        getline(fs, str);
        vec.push_back(str);
    }
    std::cout << "Please Enter which contact you want to delete: " << std::endl;
    std::cout << vec[0] << std::endl;
    for (int i = 1; i < vec.size(); i++)
    {
        std::cout << i << ") " << vec[i] << std::endl;
    }
    std::cin >> n;
    // std::cout << vec.size() << std::endl;
    vec.erase(vec.begin() + n);
    // std::cout << vec.size() << std::endl;
    del.open("Contacts.txt");
    del << vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        del << '\n'<< vec[i];
    }
    del.close();
}
void PBook::seeContacts()
{
    std::string str;
    while (!fs.eof())
    {
        getline(fs, str);
        std::cout << str << std::endl;
    }
}
PBook::~PBook()
{
    fs.close();
}

int main()
{
    PBook a;
    int N;
    std::cout << "Hello My Friend" << std::endl;
    std::cout << "What you want to do?\n"
              << "(1) Add New Contact  (2) Edit Contact\n"
              << "(3) Dellete Contact  (4) See Contacts" << std::endl;
    std::cin >> N;
    if (N == 1)
    {
        a.addContact();
    }
    if (N == 2)
    {
        a.editContact();
    }
    if (N == 3)
    {
        a.deleteContact();
    }
    if (N == 4)
    {
        a.seeContacts();
    }
}