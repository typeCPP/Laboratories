#include "phonebook.hpp"

usanov::PhoneBook::iterator usanov::PhoneBook::begin()
{
  return records.begin();
}

usanov::PhoneBook::iterator usanov::PhoneBook::end()
{
  return records.end();
}

void usanov::PhoneBook::add(const PhoneBook::record_t &record)
{
  records.push_back(record);
}

usanov::PhoneBook::iterator usanov::PhoneBook::insertBefore(PhoneBook::iterator iter, const PhoneBook::record_t &record)
{
  return records.insert(iter,record);
}

usanov::PhoneBook::iterator usanov::PhoneBook::insertAfter(PhoneBook::iterator iter, const PhoneBook::record_t &record)
{
  auto temp = iter;
  temp++;
  return records.insert(temp, record);
}

usanov::PhoneBook::iterator usanov::PhoneBook::remove(PhoneBook::iterator iter)
{
  return records.erase(iter);
}

bool usanov::PhoneBook::isEmpty() const
{
  return records.empty();
}

usanov::PhoneBook::const_iterator usanov::PhoneBook::cbegin() const
{
  return records.cbegin();
}

usanov::PhoneBook::const_iterator usanov::PhoneBook::cend() const
{
  return records.cend();
}
