#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include <string>
#include <list>

namespace usanov
{
  class PhoneBook
  {
  public:
    struct record_t
    {
      std::string number;
      std::string name;
    };
    using iterator = std::list<record_t>::iterator;
    using const_iterator = std::list<record_t>::const_iterator;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    void add(const record_t &record);
    iterator insertBefore(iterator iter, const record_t &record);
    iterator insertAfter(iterator iter, const record_t &record);
    iterator remove(iterator iter);
    bool isEmpty() const;
  private:
    std::list<record_t> records;
  };
}
#endif
