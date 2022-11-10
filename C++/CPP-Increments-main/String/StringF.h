#include "String.h"
String::String() : p{nullptr}, m_size{0} //ctor
{
}

String::String(const char *str) //ctor whit parametrs
{
    m_size = strlen(str);
    p = new char[m_size + 1];
    for (size_t i = 0; i < m_size; ++i)
    {
        p[i] = str[i];
    }
    p[m_size] = '\0';
}

String::String(const String &rhs) //copy ctor
{
    if (this->p != nullptr)
    {
        delete[] p;
    }
    m_size = strlen(rhs.p);
    p = new char[m_size + 1];
    for (size_t i = 0; i < m_size; ++i)
    {
        p[i] = rhs.p[i];
    }
    p[m_size] = '\0';
}

String::String(String &&rhs) noexcept //move ctor
{
    m_size = rhs.m_size;
    p = rhs.p;
    rhs.m_size = 0;
    rhs.p = nullptr;
}

String::~String() //dtor
{
    delete[] p;
}

// Operators <<, [], =, +,

std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    for (int i = 0; i < rhs.m_size; ++i)
    {
        os << rhs.p[i];
    }
    return os;
}

char &String::operator[](const size_t index) //operator []
{
    return p[index];
}

String &String::operator=(const String &rhs) //assignment (operaator =)
{
    if (this == &rhs)
    {
        return *this;
    }

    if (this->p != nullptr)
    {
        delete[] p;
    }

    m_size = strlen(rhs.p);
    p = new char[m_size + 1];
    for (size_t i = 0; i < m_size; ++i)
    {
        p[i] = rhs.p[i];
    }
    p[m_size] = '\0';

    return *this;
}

String &String::operator=(String &&oth) noexcept //move assignment (operator=)
{
    m_size = oth.m_size;
    p = oth.p;
    oth.m_size = 0;
    oth.p = nullptr;

    return *this;
}

String String::operator+(const String &rhs) // Operator +
{
    String res;
    res.m_size = m_size + rhs.m_size;
    res.p = new char[res.m_size + 1];
    int i = 0;
    for (; i < m_size; ++i)
    {
        res.p[i] = p[i];
    }
    for (int j = 0; j < rhs.m_size; ++j, ++i)
    {
        res.p[i] = rhs.p[j];
    }
    res.p[res.m_size] = '\0';

    return res;
}

size_t String::size() // Size
{
    return m_size;
}

size_t String::strlen(const char *rhs)
{
    size_t lenght = 0;
    while (rhs[lenght] != '\0')
    {
        ++lenght;
    }

    return lenght;
}

// void String::insert(size_t index, char ch)
// {
//     char *tmp = new char[m_size + 1];
//     for (size_t i = 0; i < m_size + 1; ++i)
//     {
//         if (i == index)
//         {
//             tmp.p[i] = ch;

//             ++i;
//         }
//     }
// }
