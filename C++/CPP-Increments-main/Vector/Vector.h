#include <iostream>
template <typename T>
class Vector
{
private:
    int m_size;
    int m_cap;
    T *m_ptr;

public:
    Vector();
    Vector(Vector<T> &&rhs);              // Move Constructor
    void push_back(const T &rhs);         // Push Back
    void push_front(const T &rhs);        // Push Front
    void pop_back();                      // Pop Back
    void pop_front();                     // Pop Front
    void insert(int index, const T &rhs); // Insert
    void erase(int Index);                // Erase
    void erase(int index, const T &rhs);  // Erase (index / Element)
    int get_size();                       // get size
    int get_cap();                        // get capasity
    T get_ptr(int ix);
    bool empty() const noexcept;
    Vector<T> &operator[](const size_t index);             // Operator []
    const Vector<T> &operator[](const size_t index) const; // Const Operator []
    template <typename E>
    Vector<T> &operator=(Vector<E> &rhs);

    // friend std::ostream &operator<<(std::ostream &os, Vector<T> &rhs);
    void print();
    ~Vector();
};

template <typename T>
Vector<T>::Vector() : m_size(0), m_cap(5), m_ptr(new T[m_cap])
{
}
template <typename T>
Vector<T>::Vector(Vector<T> &&rhs) // Move Constructor
{
    m_size = rhs.m_size;
    m_cap = rhs.m_cap;
    m_ptr = rhs.m_ptr;
    rhs.m_size = 0;
    rhs.m_cap = 0;
    rhs.m_ptr = nullptr;
}
template <typename T>
void Vector<T>::push_back(const T &rhs) // Push Back
{
    if (m_size == m_cap)
    {
        m_cap *= 2;
        T *tmp = new T[m_cap];
        for (size_t i = 0; i < m_size; ++i)
        {
            tmp[i] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = tmp;
    }
    m_ptr[m_size++] = rhs;
}
template <typename T>
void Vector<T>::push_front(const T &rhs) // Push Front
{
    if (m_size == m_cap)
    {
        m_cap *= 2;
        T *tmp = new T[m_cap];
        for (int i = 0; i < m_size; ++i)
        {
            tmp[i + 1] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = tmp;
    }
    else
    {
        for (int i = m_size; i > 0; --i)
        {
            m_ptr[i] = m_ptr[i - 1];
        }
    }
    m_ptr[0] = rhs;
    ++m_size;
}
template <typename T>
void Vector<T>::pop_back() // Pop Back
{
    m_ptr[--m_size] = 0;
}
template <typename T>
void Vector<T>::pop_front() // Pop Front
{
    for (int i = 0; i < m_size - 1; ++i)
    {
        m_ptr[i] = m_ptr[i + 1];
    }
    m_ptr[m_size--] = 0;
    // if (m_size == m_cap / 2 && m_cap != 5)
    // {
    //     m_cap /= 2;
    // }
}
template <typename T>
void Vector<T>::insert(int index, const T &rhs) // Insert
{
    if (m_size == m_cap)
    {
        m_cap *= 2;
        T *tmp = new T[m_cap];
        for (int i = 0; i < m_size + 1; ++i)
        {
            if (i < index)
            {
                tmp[i] = m_ptr[i];
            }
            else
            {

                tmp[i + 1] = m_ptr[i];
            }
        }
        tmp[index] = rhs;
        delete[] m_ptr;
        m_ptr = tmp;
    }
    else
    {
        if (index > m_size || index < 0)
        {
            return;
        }
        if (index == 0)
        {
            push_front(rhs);
            return;
        }
        if (index == m_size - 1)
        {
            push_back(rhs);
            return;
        }
        if (index == m_size)
        {
            m_ptr[index] = rhs;
        }
        if (index < m_size)
        {
            for (int i = m_size; i > 0; --i)
            {
                if (i > index)
                {
                    m_ptr[i] = m_ptr[i - 1];
                }
            }
            m_ptr[index] = rhs;
        }
    }
    ++m_size;
}
template <typename T>
void Vector<T>::erase(int index) // Erase
{
    if (index < 0 || index >= m_size)
    {
        return;
    }
    else if (index == 0)
    {
        pop_front();
    }
    else if (index == m_size - 1)
    {
        pop_back();
    }
    else
    {
        for (int i = index; i < m_size - 1; ++i)
        {
            m_ptr[i] = m_ptr[i + 1];
        }
        --m_size;
    }
}
template <typename T>
void Vector<T>::erase(int index, const T &rhs) // Erase (index / Element)
{
    m_ptr[index] = rhs;
}

// Opertators

template <typename T>
bool Vector<T>::empty() const noexcept
{
    if (m_size == 0)
    {
        return true;
    }

    return false;
}

template <typename T>
template <typename E>
Vector<T> &Vector<T>::operator=(Vector<E> &rhs) // Operator =
{
    if (m_ptr != nullptr)
    {
        delete[] m_ptr;
    }
    this->m_size = rhs.get_size();
    this->m_cap = rhs.get_cap();

    m_ptr = new T[m_cap];
    for (int ix = 0; ix < m_size; ix++)
    {
        this->m_ptr[ix] = rhs.get_ptr(ix);
    }

    return *this;
}

template <typename T>
void Vector<T>::print() // Print
{
    for (int i = 0; i < m_size; ++i)
    {
        std::cout << m_ptr[i] << std::endl;
    }
}

template <typename T>
Vector<T> &Vector<T>::operator[](const size_t index) // Operator []
{
    return m_ptr[index];
}

template <typename T>
int Vector<T>::get_size() // get size
{
    return m_size;
}

template <typename T>
int Vector<T>::get_cap() // get capasity
{
    return m_cap;
}

template <typename T>
T Vector<T>::get_ptr(int ix)
{
    return m_ptr[ix];
}
template <typename T>
const Vector<T> &Vector<T>::operator[](const size_t index) const // Const Operator []
{
    return m_ptr[index];
}
template <typename T>
Vector<T>::~Vector()
{
    delete[] m_ptr;
}