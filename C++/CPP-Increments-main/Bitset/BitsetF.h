#include <iostream>
#include <vector>
#include <string>

template <size_t BS>
class Bitset
{
private:
    int bitcount;
    long forbits;
    size_t true_bit_count;
    int arr_size;
    int *arr;

public:
    Bitset();      // Default constructor
    Bitset(int N); // Constructor with Parameter

    size_t size() const;
    size_t count();

    Bitset<BS> &set();                              // Function Set
    Bitset<BS> &set(size_t pos, bool value = true); // Function Set with parameter
    Bitset<BS> &flip();                             // Function Flip
    Bitset<BS> &flip(size_t pos);                   // Function Flip with parameter

    unsigned long to_ulong() const;       // To Ulong (long)
    unsigned long long to_ullong() const; // To Ullong (long long)

    Bitset<BS> operator<<(size_t pos) const; // Operator <<
    Bitset<BS> operator<<=(size_t pos);      // Operator <<
    Bitset<BS> operator>>(size_t pos) const; // Operator >>
    Bitset<BS> operator>>=(size_t pos);      // Operator >>

    Bitset<BS> &operator&=(const Bitset<BS> &other); // Operator &=
    Bitset<BS> &operator|=(const Bitset<BS> &other); // Operator |=
    Bitset<BS> &operator^=(const Bitset<BS> &other); // Operator ^=
    // Bitset<BS> operator~() const;                    // Operator ~

    Bitset<BS> operator&(const Bitset<BS> &rhs); // Operator &
    Bitset<BS> operator|(const Bitset<BS> &rhs); // Operator |
    Bitset<BS> operator^(const Bitset<BS> &rhs); // Operator^

    friend std::ostream &operator<<(std::ostream &ostr, Bitset<BS> &srq)
    {
        size_t tmp_true_count = 0;
        int esim = srq.bitcount;
        int ix = srq.bitcount % 32;

        for (int j = srq.arr_size - 1; j >= 0; --j)
        {
            if (j == srq.arr_size - 1 && esim < 32)
            {
                for (int i = esim - 1; i >= 0; --i)
                {
                    if (srq.arr[j] & (1 << i))
                    {
                        ostr << true;
                        ++srq.true_bit_count;
                    }
                    else
                    {
                        ostr << false;
                    }
                }
            }
            if (j == 0 && esim >=
                              32)
            {
                for (int i = 31; i >= 0; --i)
                {
                    if (srq.arr[j] & (1 << i))
                    {
                        ostr << true;
                        ++srq.true_bit_count;
                    }
                    else
                    {
                        std::cout << false;
                    }
                }
            }
            else if (esim >= 32)
            {
                for (ix -= 1; ix >= 0; --ix)
                {
                    if (srq.arr[j] & (1 << ix))
                    {
                        ostr << true;
                        ++srq.true_bit_count;
                    }
                    else
                    {
                        ostr << false;
                    }
                }
                ix = 32;
            }
        }
        return ostr;
    }

    ~Bitset();
};

template <size_t BS>
Bitset<BS>::Bitset() : bitcount(BS), forbits(0), arr_size{(BS / 32) + 1}, arr{new int[arr_size]{0}}, true_bit_count(0)
{
}

// Constructor with parameter
template <size_t BS>
Bitset<BS>::Bitset(int N) : bitcount(BS), forbits(N), arr_size{(BS / 32) + 1}, arr{new int[arr_size]{0}}, true_bit_count(0)
{
    if (N < 0)
    {
        arr[0] = N;
        for (int i = 1; i < arr_size; i++)
        {
            // this->arr[i] = 0;
            this->arr[i] = ~this->arr[i];
        }
    }
    else
    {
        arr[0] = N;
    }
}

// Bit count
template <size_t BS>
size_t Bitset<BS>::size() const
{
    return bitcount;
}

// True bit count
template <size_t BS>
size_t Bitset<BS>::count()
{
    return true_bit_count;
}

// Function Set
template <size_t BS>
Bitset<BS> &Bitset<BS>::set()
{
    for (int i = 0; i < arr_size; i++)
    {
        this->arr[i] = 0;
        this->arr[i] = ~this->arr[i];
    }

    return *this;
}

// Function Set with parameter
template <size_t BS>
Bitset<BS> &Bitset<BS>::set(size_t pos, bool value)
{
    if (pos >= BS)
    {
        std::cout << "what():  bitset - position (which is " << pos << ") >= _Nb (which is " << BS << ")" << std::endl;
        exit(0);
    }
    if (pos > 31)
    {
        int index = pos / 32;
        int n = pos % 32;
        if (value == true)
        {
            arr[index] |= (1 << n);
        }
        if (value == false)
        {
            arr[index] &= ~(1 << n);
        }
    }
    else
    {
        int n = pos;
        if (value == true)
        {
            arr[0] |= (1 << n);
        }
        if (value == false)
        {
            arr[0] &= ~(1 << n);
        }
    }
}

// Function Flip
template <size_t BS>
Bitset<BS> &Bitset<BS>::flip()
{
    for (int i = 0; i < arr_size; i++)
    {
        this->arr[i] = ~arr[i];
    }

    return *this;
}

// Function Flip with parameter
template <size_t BS>
Bitset<BS> &Bitset<BS>::flip(size_t pos)
{
    if (pos > 31)
    {
        int index = pos / 32;
        int n = pos % 32;
        arr[index] ^= (1 << n);
    }
    else
    {
        arr[0] ^= (1 << pos);
    }
    return *this;
}

// To Ullong (long)
template <size_t BS>
unsigned long Bitset<BS>::to_ulong() const
{
    if (BS >= 32)
    {
        std::cout << "ERROR....." << std::endl;
        exit(0);
    }
    if (bitcount > 32)
    {
        std::cout << "Overflow_error.." << std::endl;
        exit(0);
    }
    else
    {
        unsigned long num = arr[0];
        return num;
    }
}

// To Ullong (long long)
template <size_t BS>
unsigned long long Bitset<BS>::to_ullong() const
{
    unsigned long long num = arr[1];
    num <<= 32;
    unsigned long num1 = arr[0];
    num ^= num1;
    return num;
}

// Operators

// Operator <<
// template <size_t BS>
// Bitset<BS> Bitset<BS>::operator<<(std::size_t pos) const
// {

//     return this->forbits << pos;
// }

// // Operator >>
// template <size_t BS>
// Bitset<BS> Bitset<BS>::operator>>(std::size_t pos) const
// {
//     return this->forbits >> pos;
// }

// // Operator >>=
// template <size_t BS>
// Bitset<BS> Bitset<BS>::operator>>=(std::size_t pos)
// {
//     this->forbits >>= pos;
//     return *this;
// }

// // Operator >>=
// template <size_t BS>
// Bitset<BS> Bitset<BS>::operator<<=(std::size_t pos)
// {
//     this->forbits <<= pos;
//     return *this;
// }

// Operator &=
template <size_t BS>
Bitset<BS> &Bitset<BS>::operator&=(const Bitset<BS> &other)
{
    for (int i = 0; i < arr_size; ++i)
    {
        this->arr[i] &= other.arr[i];
    }
    return *this;
}

// Operator |=
template <size_t BS>
Bitset<BS> &Bitset<BS>::operator|=(const Bitset<BS> &other)
{
    for (int i = 0; i < arr_size; ++i)
    {
        this->arr[i] |= other.arr[i];
    }
    return *this;
}

// Operator ^=
template <size_t BS>
Bitset<BS> &Bitset<BS>::operator^=(const Bitset<BS> &other)
{
    for (int i = 0; i < arr_size; ++i)
    {
        this->arr[i] ^= other.arr[i];
    }
    return *this;
}

//Operator &
template <size_t BS>
Bitset<BS> Bitset<BS>::operator&(const Bitset<BS> &rhs)
{
    Bitset<BS> result(this->forbits);
    for (size_t i = 0; i < this->arr_size; i++)
    {
        result.arr[i] &= rhs.arr[i];
    }

    return result;
}

// Operator |
template <size_t BS>
Bitset<BS> Bitset<BS>::operator|(const Bitset<BS> &rhs)
{
    Bitset<BS> result(this->forbits);
    for (size_t i = 0; i < this->arr_size; i++)
    {
        result.arr[i] |= rhs.arr[i];
    }

    return result;
}

// Operator ^
template <size_t BS>
Bitset<BS> Bitset<BS>::operator^(const Bitset<BS> &rhs)
{
    Bitset<BS> result(this->forbits);
    for (size_t i = 0; i < this->arr_size; i++)
    {
        result.arr[i] ^= rhs.arr[i];
    }

    return result;
}

template <size_t BS>
Bitset<BS>::~Bitset()
{
    delete[] arr;
}
