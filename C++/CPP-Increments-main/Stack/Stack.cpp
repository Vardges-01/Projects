#include <iostream>
template <typename T>
class Stack
{
private:
    int m_size;
    int max_size;
    int m_cap;
    T *m_arr;

public:
    Stack(); //Default Constructor

    void push(const T &rhs);  // Push
    T pop();                  // Pop
    T top();                  // Top
    bool empty() const;       // Empty
    void reverse(char rhs[]); // Reverse
    Stack<T> &operator=(const Stack<T> &rhs);
    ~Stack();
};

template <typename T>
Stack<T>::Stack() : m_size{0}, m_cap{5}, max_size{10240}, m_arr{new T[m_cap]}
{
}

template <typename T>
void Stack<T>::push(const T &rhs) // Push
{
    if (m_cap == max_size)
    {
        std::cout << "Stack OverFlow......" << std::endl;
        return;
    }
    if (m_size == m_cap)
    {
        m_cap *= 2;
        T *tmp = new T[m_cap];
        for (size_t i = 0; i < m_size; ++i)
        {
            tmp[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = tmp;
    }
    m_arr[m_size++] = rhs;
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &rhs) // Operator =
{
    if (this == &rhs)
    {
        return *this;
    }
    this->m_size = rhs.m_size;
    this->m_cap = rhs.m_cap;
    this->max_size = rhs.max_size;

    this->m_arr = new T[m_cap];
    for (int i = 0; i < m_size; ++i)
    {
        this->m_arr[i] = rhs.m_arr[i];
    }
    return *this;
}


template <typename T>
T Stack<T>::pop() // Pop
{
    if (m_size < 0)
    {
        return 0;
    }
    return m_arr[--m_size];
}

template <typename T>
T Stack<T>::top() // Top
{
    if (m_size != 0)
    {
        return m_arr[m_size - 1];
    }

    return 0;
}

template <typename T>
bool Stack<T>::empty() const // Empty
{
    if (m_size == 0)
    {
        return true;
    }

    return false;
}

template <typename T>
void Stack<T>::reverse(char rhs[]) // Reverse
{
    for (int i = 0; rhs[i] != '\0'; i++)
    {
        push(rhs[i]);
    }

    for (int i = 0; rhs[i] != '\0'; i++)
    {
        rhs[i] = pop();
    }
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] m_arr;
}

int main()
{
    Stack<char> ob;

    char str[] = "barev";
    ob.reverse(str);
    std::cout << str << std::endl;

    return 0;
}