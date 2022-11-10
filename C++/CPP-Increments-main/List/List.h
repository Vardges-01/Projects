#include <iostream>
#include <iterator>
#include <initializer_list>
// using namespace std;

template <typename T>
class forward_list
{
public:
    forward_list();
    forward_list(forward_list<T> &lhs);
    forward_list(const forward_list<T> &lhs);
    forward_list(const std::initializer_list<T> &lhs);
    ~forward_list();
    forward_list<T> &operator=(const forward_list &rhs);
    void push_back(T data);   // Push Back
    void push_front(T value); // Push Front
    void remove(T key);       // Remove
    void pop_front();         // Pop Front
    int max_size();
    void reserve()
    {
        Node *cur = head;
        Node *prev = nullptr;
        Node *next = nullptr;

        while (cur != nullptr)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;
    }

    bool result;
    void rec(Node *first, Node *second)
    {
        if (first == nullptr)
        {
            return;
        }
        rec(first->next, second);

        if (first->data != second->data)
        {
            result = false;
            return;
        }
        result = true;
        second = second->next;
    }
    bool isListPalindrome(ListNode<int> *l)
    {

        rec(l, l);
        return result;
    }
    bool isPalidrom()
    {
    }
    void emplace_front(const T &value);                // Emplace Front
    void emplace_after(const int pos, const T &value); // Emplace After
    void insert_after(const int pos, const T &value);  // Insert After
    void erase_after(const int pos);                   // Erase After

    void print(); // Print

private:
    // Struct Node
    struct Node
    {
        forward_list<T>::Node *next;
        T data;
    };
    // node *find(int index) const;

    int size;
    forward_list<T>::Node *head;
};

template <typename T>
forward_list<T>::forward_list() : size(0), head(nullptr)
{
}

// Operator =
template <typename T>
forward_list<T> &forward_list<T>::operator=(const forward_list &rhs)
{
    int my_size = rhs.size - 1;
    Node *tmp = new Node;
    head = tmp;
    Node *tmp1 = new Node;
    tmp1 = rhs.head;
    tmp->data = tmp1->data;
    while (my_size)
    {
        tmp1 = tmp1->next;
        Node *res = new Node;
        tmp->next = res;
        res->data = tmp1->data;
        tmp = tmp->next;
        --my_size;
    }
    tmp->next = nullptr;
    // delete tmp->next;

    return *this;
}

// Constructor Copy
template <typename T>
forward_list<T>::forward_list(const forward_list<T> &lhs)
{
    head = new Node;
    head->data = lhs.head->data;

    Node *newPtr = head;
    for (Node *origPtr = lhs.head->next;
         origPtr != nullptr;
         origPtr = origPtr->next)
    {
        newPtr->next = new Node;
        newPtr = newPtr->next;
        newPtr->data = origPtr->data;
    }
    newPtr->next = nullptr;
}

// Initializer List
template <typename T>
forward_list<T>::forward_list(const std::initializer_list<T> &lhs) : size(0), head(nullptr)
{
    Node *tmp = new Node;
    Node *tmp1 = tmp;
    size = lhs.size();
    typename std::initializer_list<T>::iterator it;
    for (it = lhs.begin(); it < lhs.end() - 1; ++it)
    {
        tmp->data = *it;
        tmp->next = new Node;
        tmp = tmp->next;
        // tmp->next = nullptr;
    };
    tmp->data = *it;
    tmp->next = nullptr;
    head = tmp1;
}

template <typename T>
forward_list<T>::forward_list(forward_list<T> &lhs)
{
    this->head = lhs.head;
    this->size = lhs.size;
}

template <typename T>
forward_list<T>::~forward_list()
{
    Node *tmp;
    while (size)
    {
        // tmp = head;
        // head = head->next;
        // delete tmp;
        pop_front();
    }
}

// Find
// template <typename T>
// forward_list<T>::node *forward_list<T>::find(int index) const
// {
//     if ((index < 1) || (index > size))
//     {
//         return NULL;
//     }
//     else
//     {
//         node *tmp = head;
//         for (int i = 1; i < index; ++i)
//         {
//             tmp = tmp->next;
//         }
//         return tmp;
//     }
// }

// Push Back
template <typename T>
void forward_list<T>::push_back(T value)
{
    forward_list<T>::Node *tmpdata = new forward_list<T>::Node;
    tmpdata->data = value;
    tmpdata->next = nullptr;

    if (head == nullptr)
    {
        head = tmpdata;
        ++size;
        return;
    }
    forward_list<T>::Node *tmp = new forward_list<T>::Node;
    tmp = head;
    while (tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    tmp->next = tmpdata;
    size++;
}

// Push Front
template <typename T>
void forward_list<T>::push_front(T value)
{
    forward_list<T>::Node *tmpdata = new forward_list<T>::Node;
    tmpdata->data = value;
    tmpdata->next = head;
    head = tmpdata;
    ++size;
}

// Pop Front
template <typename T>
void forward_list<T>::pop_front()
{
    Node *tmp = head;
    head = head->next;
    delete tmp;
    --size;
}

// Remove
template <typename T>
void forward_list<T>::remove(T key)
{
    Node *tmp = head;
    if (tmp == nullptr)
    {
        return;
    }
    while (tmp->next != nullptr)
    {
        if (tmp->data == key)
        {
            tmp = tmp->next;
            head = tmp;
            continue;
        }
        if (tmp->next->data == key)
        {
            tmp->next = tmp->next->next;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    if (tmp->data == key)
    {
        tmp = tmp->next;
        head = tmp;
    }
}

//insert after
template <typename T>
void forward_list<T>::insert_after(const int pos, const T &value)
{
    if (pos > size)
        throw "Not found Position ";

    forward_list<T>::Node *tmpdata = new forward_list<T>::Node;
    tmpdata->data = value;

    forward_list<T>::Node *tmp = new forward_list<T>::Node;
    tmp = head;
    for (int i = 0; i < pos; ++i)
    {
        tmp = tmp->next;
    }
    tmpdata->next = tmp->next;
    tmp->next = tmpdata;
    ++size;
}

// Emplace After
template <typename T>
void forward_list<T>::emplace_after(const int pos, const T &value)
{
    if (pos > size)
        throw "Not found Position ";

    forward_list<T>::Node *tmpdata = new forward_list<T>::Node;
    tmpdata->data = value;

    forward_list<T>::Node *tmp = new forward_list<T>::Node;
    tmp = head;
    for (int i = 0; i < pos; ++i)
    {
        tmp = tmp->next;
    }
    tmpdata->next = tmp->next;
    tmp->next = tmpdata;
    ++size;
}

// Emplace After
template <typename T>
void forward_list<T>::emplace_front(const T &value)
{
    forward_list<T>::Node *tmpdata = new forward_list<T>::Node;
    tmpdata->data = value;
    tmpdata->next = head;
    if (head == nullptr)
    {
        ++size;
        head = tmpdata;
        return;
    }
    head = tmpdata;

    ++size;
}

// Erase After
template <typename T>
void forward_list<T>::erase_after(const int pos)
{
    if (pos >= size - 1)
        throw "Not found Position ";

    forward_list<T>::Node *tmp = new forward_list<T>::Node;
    tmp = head;
    for (int i = 0; i < pos; ++i)
    {
        tmp = tmp->next;
    }
    Node *tmp1 = tmp->next->next;
    delete tmp->next;
    tmp->next = tmp1;
    --size;
}

// Max Size
template <typename T>
int forward_list<T>::max_size()
{
    return (size_t(-1) / sizeof(T)) / 2;
}

// Print
template <typename T>
void forward_list<T>::print()
{
    Node *tmp = head;
    while (tmp)
    {
        std::cout << tmp->data << std::endl;
        tmp = tmp->next;
    }
}