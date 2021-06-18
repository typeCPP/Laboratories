#ifndef B3_BOOKMARKINTERFACE_HPP
#define B3_BOOKMARKINTERFACE_HPP

#include <map>
#include "phonebook.hpp"

namespace usanov
{
  class BookmarkInterface
  {
  public:
    enum MovePos
    {
      first,
      last
    };
    BookmarkInterface();
    void addRecord(const PhoneBook::record_t &record);
    void storeMark(const std::string &mark, const std::string &newMark, std::ostream &out);
    void insertBeforeMark(const std::string &mark, const PhoneBook::record_t &record, std::ostream &out);
    void insertAfterMark(const std::string &mark, const PhoneBook::record_t &record, std::ostream &out);
    void deleteRecordOnMark(const std::string &mark, std::ostream &out);
    void showMark(const std::string &mark, std::ostream &out) const;
    void moveMarkOnSteps(const std::string &mark, int steps, std::ostream &out);
    void moveMarkOnPos(const std::string &mark, const MovePos &movePos, std::ostream &out);
  private:
    PhoneBook book;
    std::map<std::string, PhoneBook::iterator> marks;
    void moveAllMarks();
  };
}
#endif
