#ifndef B3_PARSER_HPP
#define B3_PARSER_HPP

#include <iostream>
#include "phonebook.hpp"
#include <functional>
#include "bookmarkInterface.hpp"

using Command = std::function<void(usanov::BookmarkInterface&, std::ostream&)>;

namespace detail
{
  Command parseCommandAdd(std::istringstream &stream);
  Command parseCommandStore(std::istringstream &stream);
  Command parseCommandInsert(std::istringstream &stream);
  Command parseCommandDelete(std::istringstream &stream);
  Command parseCommandShow(std::istringstream &stream);
  Command parseCommandMove(std::istringstream &stream);
  bool parseName(std::istringstream &stream, std::string &nameToWrite);
  bool parseNumber(std::istringstream &stream, std::string &numberToWrite);
  bool isTrash(std::istringstream &stream);
}

Command parseTypeOfCommand(const std::string &command);
void printInvalidCommand(usanov::BookmarkInterface&, std::ostream& out);
void printInvalidStep(usanov::BookmarkInterface&, std::ostream& out);

#endif
