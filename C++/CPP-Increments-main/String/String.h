#ifndef _STRING_
#define _STRING_
#include <ostream>

class String
{
public:
  String();
  String(const char *str);
  String(const String &rhs);
  String(String &&rhs) noexcept;
  ~String();

public:
  char &operator[](const size_t index);
  friend std::ostream &operator<<(std::ostream &os, const String &rhs);
  String &operator=(const String &rhs);
  String &operator=(String &&oth) noexcept;
  String operator+(const String &rhs);
  size_t size();
  size_t strlen(const char *rhs);
  void insert(const size_t index, const char ch);

private:
  char *p;
  size_t m_size;
};

#endif //_STRING_