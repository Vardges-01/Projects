#include <iostream>
#include <initializer_list>

template <typename T>
class FrankList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;
        Node *asc;
        Node *desc;
        Node() : data{0}, next{nullptr}, prev{nullptr}, asc{nullptr}, desc{nullptr} {}
        Node(T &m_data) : data{m_data}, next{nullptr}, prev{nullptr}, asc{nullptr}, desc{nullptr} {}
    };

    Node *m_head;
    Node *m_tail;
    Node *m_asc;
    Node *m_desc;
    int m_size;

    void put_sort(Node *tmp);    // Put Sort
    void delete_sort(Node *tmp); // Delete Sort

public:
    class iterator
    {
    public:
        Node *_M_node;

    public:
        iterator();
        iterator(Node *rhs);
        T &operator*() const // Iterator Operator*
        {
            return _M_node->data;
        }
        iterator operator++() // Operator ++
        {
            _M_node = _M_node->next;
            return *this;
        }
        iterator operator++(T rhs) // Operator ++
        {
            iterator tmp(_M_node);
            _M_node = _M_node->next;
            return tmp;
        }
        iterator operator--() // Operator ++
        {
            _M_node = _M_node->prev;
            return *this;
        }
        iterator operator--(T rhs) // Operator ++
        {
            iterator tmp(_M_node);
            _M_node = _M_node->prev;
            return tmp;
        }
        bool operator==(const iterator &rhs) // Operatr ==
        {
            return this->_M_node == rhs._M_node;
        }
        bool operator!=(const iterator &rhs) // Operator !=
        {
            return this->_M_node != rhs._M_node;
        }
       
        ~iterator();
    };

public:
    FrankList();                                    // Default Constructor
    FrankList(T data);                              // Parametr Constructor
    FrankList(const FrankList<T> &rhs);             //   Copy Constructor
    FrankList(FrankList<T> &&rhs);                  //   Move Constructor
    FrankList(const std::initializer_list<T> &lhs); // Initializer List
    FrankList &operator=(const FrankList<T> &rhs);  //   Copy Constructor

    friend std::ostream &operator<<(std::ostream &os, const FrankList<T> &rhs)
    {
        Node *cur = rhs.m_head;
        while (cur != nullptr)
        {
            os << cur->data << "->";
            cur = cur->next;
        }
        std::cout << "\b\b     " << std::endl;
    }

    Node *begin() // _M_node Head
    {
        return m_head->next;
    }
    Node *end() // _M_node Tail Next
    {
        return m_tail->next;
    }
    Node *before_begin() // Before Begin _M_node
    {
        return m_head;
    }

    void push_front(T data);           //  Push Front
    void push_back(T data);            //  Push Back
    void insert(iterator pos, T data); //  insert
    void erase(const int pos);         //  Erase
    void pop_back();                   //  Pop Back
    void pop_front();                  //  Pop Front

    void as_print();   // Print Asc
    void ds_print();   // Ds Print
    void tail_print(); // Tail Print

    ~FrankList();
};

template <typename T>
FrankList<T>::FrankList() : m_head{nullptr}, m_tail{nullptr}, m_asc{nullptr}, m_desc{nullptr}, m_size{} {}

template <typename T>
FrankList<T>::FrankList(T data) : m_head{nullptr}, m_tail{nullptr}, m_asc{nullptr}, m_desc{nullptr}, m_size{}
{
    m_head = new Node(data);
    m_tail = m_head;
    m_asc = m_head;
    m_desc = m_head;
    ++m_size;
}

// Copy Constructor
template <typename T>
FrankList<T>::FrankList(const FrankList<T> &rhs) : m_head{nullptr}, m_tail{nullptr}, m_asc{nullptr}, m_desc{nullptr}, m_size{}
{
    if (rhs.m_head == nullptr)
    {
        return;
    }
    Node *cur = rhs.m_head;
    while (cur != nullptr)
    {
        push_back(cur->data);
        cur = cur->next;
    }
}

template <typename T>
FrankList<T>::FrankList(const std::initializer_list<T> &lhs) : m_head{nullptr}, m_tail{nullptr}, m_asc{nullptr}, m_desc{nullptr}, m_size{}
{
    typename std::initializer_list<T>::iterator it;
    for (it = lhs.begin(); it < lhs.end() - 1; ++it)
    {
        push_back(*it);
    }
}

// Move Constructor
template <typename T>
FrankList<T>::FrankList(FrankList<T> &&rhs)
{
}

template <typename T>
FrankList<T> &FrankList<T>::operator=(const FrankList<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    if (rhs.m_head == nullptr)
    {
        return *this;
    }
    m_head = new Node;
    m_size = rhs.m_size;
    Node *this_tmp = m_head;
    Node *rhs_tmp = rhs.m_head;
    while (rhs_tmp != nullptr)
    {
        this_tmp->data = rhs_tmp->data;
        if (rhs_tmp->next == nullptr)
        {
            break;
        }
        this_tmp->next = new Node;
        this_tmp->next->prev = this_tmp;
        this_tmp = this_tmp->next;
        rhs_tmp = rhs_tmp->next;
    }
    m_tail = this_tmp;
    m_tail->next = nullptr;
    this_tmp = m_head;
    m_asc = m_head;
    m_desc = m_head;
    while (this_tmp != nullptr)
    {
        put_sort(this_tmp);
        this_tmp = this_tmp->next;
    }
    return *this;
}

// Push Front
template <typename T>
void FrankList<T>::push_front(T data)
{
    if (!m_head)
    {
        m_head = new Node(data);
        m_tail = m_head;
        m_asc = m_head;
        m_desc = m_head;
        ++m_size;
        return;
    }
    Node *tmp = new Node(data);
    put_sort(tmp);
    m_head->prev = tmp;
    tmp->next = m_head;
    m_head = tmp;
    ++m_size;
}

// Push Back
template <typename T>
void FrankList<T>::push_back(T data)
{
    if (!m_head)
    {
        m_head = new Node(data);
        m_tail = m_head;
        m_asc = m_head;
        m_desc = m_head;
        ++m_size;
        return;
    }

    Node *tmpdata = new Node(data);
    put_sort(tmpdata);
    tmpdata->prev = m_tail;
    m_tail->next = tmpdata;
    m_tail = tmpdata;
    ++m_size;
}

// Insert
template <typename T>
void FrankList<T>::insert(iterator pos, T data)
{
    iterator a = pos;
    if (pos == nullptr)
    {
        std::cout << " Out of Range.." << std::endl;
        return;
    }
    if (pos == before_begin())
    {
        push_front(data);
        return;
    }
    if (pos == end())
    {
        push_back(data);
        return;
    }

    Node *tmpdata = new Node(data);
    Node *tmp = pos._M_node;
    put_sort(tmpdata);
    tmpdata->next = tmp;
    tmpdata->prev = tmp->prev;
    tmp->prev = tmpdata;
    tmpdata->prev->next = tmpdata;
}

// Erase
template <typename T>
void FrankList<T>::erase(const int pos) //  Erase
{
    Node *cur = m_head;
    if (pos == 0)
    {
        pop_front();
        return;
    }
    if (pos == m_size - 1)
    {
        pop_back();
        return;
    }

    for (int i = 0; i < pos; ++i)
    {
        cur = cur->next;
    }
    delete_sort(cur);
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
    cur = nullptr;
}

//Pop Back
template <typename T>
void FrankList<T>::pop_back()
{
    if (m_head->next == nullptr)
    {
        delete m_head;
        m_head = nullptr;
        m_asc = nullptr;
        m_desc = nullptr;
        m_tail = nullptr;
        --m_size;
        return;
    }
    delete_sort(m_tail);
    m_tail = m_tail->prev;
    delete m_tail->next;
    m_tail->next = nullptr;
    --m_size;
}

// Pop Front
template <typename T>
void FrankList<T>::pop_front()
{
    if (m_head->next == nullptr)
    {
        delete m_head;
        m_head = nullptr;
        m_asc = nullptr;
        m_desc = nullptr;
        m_tail = nullptr;
        --m_size;
        return;
    }
    delete_sort(m_head);
    m_head = m_head->next;
    delete m_head->prev;
    m_head->prev = nullptr;
    --m_size;
}

// Put Sorted (Helper)
template <typename T>
void FrankList<T>::put_sort(Node *tmp)
{
    Node *cur = m_asc;
    if (tmp->data >= m_desc->data)
    {
        tmp->desc = m_desc;
        m_desc->asc = tmp;
        m_desc = tmp;
        m_desc->asc = nullptr;
        m_asc->desc = nullptr;
        return;
    }
    if (tmp->data < m_asc->data)
    {
        tmp->asc = m_asc;
        m_asc->desc = tmp;
        m_asc = tmp;
        m_asc->desc = nullptr;
        m_desc->asc = nullptr;
        return;
    }

    while (cur->asc != nullptr)
    {
        if (tmp->data < cur->asc->data)
        {

            tmp->asc = cur->asc;
            cur->asc->desc = tmp;
            tmp->desc = cur;
            cur->asc = tmp;

            break;
        }
        cur = cur->asc;
    }
}

// Delete Sort
template <typename T>
void FrankList<T>::delete_sort(Node *tmp)
{
    if (tmp == m_asc)
    {
        m_asc = m_asc->asc;
        delete tmp;
        m_asc->desc = nullptr;
        return;
    }
    if (tmp == m_desc)
    {
        m_desc = m_desc->desc;
        delete tmp;
        m_desc->asc = nullptr;
        return;
    }
    tmp->desc->asc = tmp->asc;
    tmp->asc->desc = tmp->desc;
}

// Print Asc
template <typename T>
void FrankList<T>::as_print()
{

    Node *cur = m_head;
    cur = m_asc;
    while (cur != nullptr)
    {
        std::cout << cur->data << "->";
        cur = cur->asc;
    }
    std::cout << "\b\b     " << std::endl;
}

// Print Desc
template <typename T>
void FrankList<T>::ds_print()
{
    Node *cur = m_desc;
    while (cur != nullptr)
    {
        std::cout << cur->data << "->";
        cur = cur->desc;
    }
    std::cout << "\b\b     " << std::endl;
}

// Print Tail
template <typename T>
void FrankList<T>::tail_print()
{
    Node *cur = m_tail;
    while (cur != nullptr)
    {
        std::cout << cur->data << "->";
        cur = cur->prev;
    }
    std::cout << "\b\b    " << std::endl;
}

// Destructor
template <typename T>
FrankList<T>::~FrankList()
{
    Node *cur = m_head;
    while (cur != nullptr)
    {
        cur = m_head->next;
        delete m_head;
        m_head = cur;
        m_tail = nullptr;
        m_asc = nullptr;
        m_desc = nullptr;
    }
}

// Iterator Default Constructor
template <typename T>
FrankList<T>::iterator::iterator() : _M_node{nullptr} {}

// Iterator  Constructor with Parametr
template <typename T>
FrankList<T>::iterator::iterator(Node *rhs) : _M_node{rhs} {}

// Iterator  Destructor
template <typename T>
FrankList<T>::iterator::~iterator(){

};
