#include <iostream>
#include <queue>
template <typename T>
class BinarSearch
{
private:
    struct Node
    {
        T m_data;
        Node *left;
        Node *right;
        Node() {}
        Node(T data) : m_data{data}, left{nullptr}, right{nullptr}
        {
        }
    };

    void delete_root(Node *root);

    Node *m_root;

public:
    BinarSearch(/* args */);
    void insert(T data);
    void inorder(Node *root);
    void preorder(Node *root);
    void posorder(Node *root);
    void printLevelOrder(Node *root);

    void print()
    {
        inorder(m_root);
        std::cout << std::endl;
        preorder(m_root);
        std::cout << std::endl;
        posorder(m_root);
        std::cout << std::endl;
        std::cout << std::endl;
        printLevelOrder(m_root);
    }
    ~BinarSearch();
};

template <typename T>
BinarSearch<T>::BinarSearch() : m_root{nullptr}
{
}

template <typename T>
void BinarSearch<T>::insert(T data)
{
    Node *tmp = m_root;
    if (tmp == nullptr)
    {
        tmp = new Node(data);
        m_root = tmp;
        return;
    }
    Node *tmpdata = new Node(data);
    while (tmp != nullptr)
    {
        if (data < tmp->m_data)
        {
            if (!tmp->left)
            {
                tmp->left = tmpdata;
                return;
            }
            tmp = tmp->left;
        }
        else
        {
            if (!tmp->right)
            {
                tmp->right = tmpdata;
                return;
            }
            tmp = tmp->right;
        }
    }
}

template <typename T>
void BinarSearch<T>::printLevelOrder(Node *root)
{
    // Base Case
    if (root == nullptr)
        return;
    std::queue<Node *> p;
    p.push(root);
    while (!p.empty())
    {
        Node *tmp = p.front();
        std::cout << tmp->m_data << " ";
        p.pop();

        if (tmp->left != nullptr)
        {
            p.push(tmp->left);
        }
        if (tmp->right != nullptr)
        {
            p.push(tmp->right);
        }
    }
}

template <typename T>
void BinarSearch<T>::inorder(Node *root)
{
    if (root == nullptr)
        return;

    inorder(root->left);
    std::cout << root->m_data << "->";
    inorder(root->right);
}

template <typename T>
void BinarSearch<T>::preorder(Node *root)
{
    if (root == nullptr)
        return;

    std::cout << root->m_data << "->";
    preorder(root->left);
    preorder(root->right);
}

template <typename T>
void BinarSearch<T>::posorder(Node *root)
{
    if (root == nullptr)
        return;

    posorder(root->left);
    posorder(root->right);
    std::cout << root->m_data << "->";
}

template <typename T>
void BinarSearch<T>::delete_root(Node *root)
{
    if (root == nullptr)
        return;

    delete_root(root->left);
    delete_root(root->right);
    delete root;
    m_root = nullptr;
}

template <typename T>
BinarSearch<T>::~BinarSearch()
{
    delete_root(m_root);
}
