#include "bookmarkInterface.hpp"
#include <iostream>
#include <string>

const std::string ERROR_EMPTY = "<EMPTY>\n";
const std::string ERROR_INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";

usanov::BookmarkInterface::BookmarkInterface()
{
  marks["current"] = book.begin();
}

void usanov::BookmarkInterface::moveAllMarks()
{
  for (auto i = marks.begin(); i != marks.end(); i++)
  {
    i->second = book.begin();
  }
}

void usanov::BookmarkInterface::addRecord(const PhoneBook::record_t &record)
{
  const bool isBookEmpty = book.isEmpty();
  book.add(record);
  if (isBookEmpty)
  {
    moveAllMarks();
  }
}

void usanov::BookmarkInterface::storeMark(const std::string &mark, const std::string &newMark, std::ostream &out)
{
  const auto markIter = marks.find(mark);
  if (markIter == marks.end())
  {
    out << ERROR_INVALID_BOOKMARK;
  }
  else
  {
    marks[newMark] = markIter->second;
  }
}

void usanov::BookmarkInterface::insertBeforeMark(const std::string &mark,
    const PhoneBook::record_t &record, std::ostream &out)
{
  const bool bookIsEmpty = book.isEmpty();
  const auto markIter = marks.find(mark);
  if (markIter == marks.end())
  {
    out << ERROR_INVALID_BOOKMARK;
  }
  else
  {
    book.insertBefore(markIter->second, record);
    if (bookIsEmpty)
    {
      moveAllMarks();
    }
  }
}

void usanov::BookmarkInterface::insertAfterMark(const std::string &mark,
    const PhoneBook::record_t &record, std::ostream &out)
{
  const bool bookIsEmpty = book.isEmpty();
  const auto markIter = marks.find(mark);
  if (markIter == marks.end())
  {
    out << ERROR_INVALID_BOOKMARK;
  }
  else
  {
    book.insertAfter(markIter->second, record);
    if (bookIsEmpty)
    {
      moveAllMarks();
    }
  }
}

void usanov::BookmarkInterface::deleteRecordOnMark(const std::string &mark, std::ostream &out)
{
  if (book.isEmpty())
  {
    out << ERROR_EMPTY;
    return;
  }
  const auto markIter = marks.find(mark);
  if (markIter == marks.end())
  {
    out << ERROR_INVALID_BOOKMARK;
    return;
  }
  auto iter = marks[mark];
  for (auto bookmarkIter = marks.begin(); bookmarkIter != marks.end(); ++bookmarkIter)
  {
    if (bookmarkIter->second == iter)
    {
      if ((markIter->second != book.begin()) && (std::next(bookmarkIter->second) == book.end()))
      {
        bookmarkIter->second--;
      }
      else
      {
        bookmarkIter->second++;
      }
    }
  }
  book.remove(iter);
}

void usanov::BookmarkInterface::showMark(const std::string &mark, std::ostream &out) const
{
  const auto markIter = marks.find(mark);
  if (markIter == marks.end())
  {
    out << ERROR_INVALID_BOOKMARK;
  }
  else if (book.isEmpty())
  {
    out << ERROR_EMPTY;
  }
  else
  {
    out << markIter->second->number << " " << markIter->second->name << "\n";
  }
}

void usanov::BookmarkInterface::moveMarkOnSteps(const std::string &mark, int steps, std::ostream &out)
{
  if (book.isEmpty())
  {
    out << ERROR_EMPTY;
    return;
  }
  const auto markIter = marks.find(mark);
  if (markIter == marks.end())
  {
    out << ERROR_INVALID_BOOKMARK;
  }
  else if (steps > 0)
  {
    if (std::distance(markIter->second, --book.end()) < steps)
    {
      markIter->second = --book.end();
    }
    else
    {
      markIter->second = std::next(markIter->second, steps);
    }
  }
  else if (steps < 0)
  {
    if ((std::distance(markIter->second, book.begin())) < (steps * -1))
    {
      markIter->second = book.begin();
    }
    else
    {
      markIter->second = std::prev(markIter->second, steps * -1);
    }
  }
}

void usanov::BookmarkInterface::moveMarkOnPos(const std::string &mark, const MovePos &movePos, std::ostream &out)
{
  if (book.isEmpty())
  {
    out << ERROR_EMPTY;
    return;
  }
  const auto markIter = marks.find(mark);
  if (markIter == marks.end())
  {
    out << ERROR_INVALID_BOOKMARK;
  }
  else if (movePos == MovePos::first)
  {
    markIter->second = book.begin();
  }
  else if (movePos == MovePos::last)
  {
    markIter->second = --book.end();
  }
}
