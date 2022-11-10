#include <iostream>
#include <functional>
namespace spi
{
    template <typename T>
    class shared_ptr
    {
    private:
        struct Control_block
        {
            int RC{};
            std::function<void(T *)> deleter;
        };

        T *m_ptr;
        Control_block *m_block;

        // Function
        void delet_obj(T *rhs); // delete Function

    public:
        // Constructors
        shared_ptr();       // Default constructor
        shared_ptr(T *rhs); // Constructor with Parametr
        template <typename T1>
        shared_ptr(T *lhs, T1 del) // Constructor with Parametr And Deleter
        {
            std::cout << del << std::endl;
            m_ptr = lhs;
            m_block = new Control_block;
            m_block->RC++;
            m_block->deleter = del;
            m_block->deleter;
        }
        shared_ptr(const shared_ptr<T> &rhs); // Copy Constructor
        shared_ptr(shared_ptr<T> &&rhs);      // Move Constructor
        ~shared_ptr();                        // Destructor

        // Operator
        shared_ptr &operator=(const shared_ptr<T> &rhs); // Operator Assigne
        shared_ptr &operator=(shared_ptr<T> &&rhs);      // Operator Move Assigne
        T &operator*() const;                            // Operator *
        T *operator->() const;                           // Operator ->

        // Functions
        void reset();
        void reset(T *ptr);  // Reset
        T *get() const;      // Get
        T use_count() const; // Use count
    };
}

/*       Constructors    */
template <typename T>
spi::shared_ptr<T>::shared_ptr(T *rhs)
{
    // std::cout << "Param. constr" << std::endl;
    this->m_ptr = rhs;
    this->m_block = new Control_block;
    this->m_block->RC++;
}

template <typename T>
spi::shared_ptr<T>::shared_ptr() : m_ptr{nullptr}, m_block{nullptr}
{
}

template <typename T>
spi::shared_ptr<T>::shared_ptr(shared_ptr<T> &&rhs) // Move Constructor
{
    this->m_ptr = rhs.m_ptr;
    this->m_block = rhs.m_block;
    rhs.m_ptr = nullptr;
    rhs.m_block = new Control_block;
}

template <typename T>
spi::shared_ptr<T>::shared_ptr(const shared_ptr<T> &rhs) // Copy Constructor
{
    if (rhs->m_ptr)
    {
        this->m_ptr = rhs.m_ptr;
        this->m_block = rhs.m_block;
        this->m_block->RC++;
    }
}

/*       Operators       */
template <typename T>
T &spi::shared_ptr<T>::operator*() const // Operator *
{
    return *(this->m_ptr);
}

template <typename T>
T *spi::shared_ptr<T>::operator->() const // Operator ->
{
    return this->m_ptr;
}

template <typename T>
spi::shared_ptr<T> &spi::shared_ptr<T>::operator=(const shared_ptr<T> &rhs) // Operator Assigne
{
    std::cout << "Oper. = " << std::endl;
    if (this == &rhs)
    {
        return *this;
    }
    if (this->m_ptr != nullptr)
    {
        this->m_block->RC--;
        if (this->m_block->RC == 0)
        {
            delet_obj();
        }
    }
    this->m_ptr = rhs.m_ptr;
    this->m_block = rhs.m_block;
    this->m_block->RC++;
    return *this;
}

template <typename T>
spi::shared_ptr<T> &spi::shared_ptr<T>::operator=(shared_ptr<T> &&rhs) // Operator Move Assigne
{
    if (this == &rhs)
    {
        return *this;
    }
    this->m_ptr = rhs.m_ptr;
    this->m_block = rhs.m_block;
    rhs.m_ptr = nullptr;
    rhs.m_block = nullptr;
    return *this;
}

/*       Functions       */
template <typename T>
void spi::shared_ptr<T>::delet_obj(T *rhs) // Delete Pointer
{
    delete this->m_ptr;
    delete this->m_block;
    this->m_ptr = nullptr;
    this->m_block = nullptr;
}

template <typename T>
T *spi::shared_ptr<T>::get() const // get addres Object
{
    return m_ptr;
}

template <typename T>
T spi::shared_ptr<T>::use_count() const // Using count
{
    return m_block->RC;
}

template <typename T>
void spi::shared_ptr<T>::reset()
{
    m_block->RC = 0;
}

template <typename T>
void spi::shared_ptr<T>::reset(T *rhs)
{
    if (!this->m_ptr)
    {
        this->m_ptr = rhs;
        this->m_block = new Control_block;
        this->m_block->RC++;
        return;
    }
    this->m_block->RC--;
    if (this->m_block->RC == 0)
    {
        delet_obj(this->m_ptr);
    }
    this->m_block = new Control_block;
    this->m_block->RC++;
    this->m_ptr = rhs;
}

/* Destructor */
template <typename T>
spi::shared_ptr<T>::~shared_ptr()
{
    if (this->m_ptr != nullptr)
    {
        m_block->RC--;
        if (m_block->RC == 0)
        {
            // m_block->deleter;
            delete m_ptr;
        }
    }
}
