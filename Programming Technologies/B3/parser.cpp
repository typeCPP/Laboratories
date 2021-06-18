#include "parser.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <functional>

Command parseTypeOfCommand(const std::string &command)
{
  std::istringstream commandStream(command);
  std::string typeOfCommand;
  commandStream >> typeOfCommand;
  const std::map<std::string, std::function<Command(std::istringstream &)>> commands
    {
      {"add",    &detail::parseCommandAdd},
      {"store",  &detail::parseCommandStore},
      {"insert", &detail::parseCommandInsert},
      {"delete", &detail::parseCommandDelete},
      {"show",   &detail::parseCommandShow},
      {"move",   &detail::parseCommandMove}
    };
  const auto iter = commands.find(typeOfCommand);
  if (iter == commands.end())
  {
    return &printInvalidCommand;
  }
  return iter->second(commandStream);
}

Command detail::parseCommandAdd(std::istringstream &stream)
{
  std::string name, number;
  if (!parseNumber(stream, number))
  {
    return &printInvalidCommand;
  }
  if (!parseName(stream, name))
  {
    return &printInvalidCommand;
  }
  if (isTrash(stream))
  {
    return &printInvalidCommand;
  }
  usanov::PhoneBook::record_t recordToAdd{number, name};
  return std::bind(&usanov::BookmarkInterface::addRecord, std::placeholders::_1, recordToAdd);
}

Command detail::parseCommandStore(std::istringstream &stream)
{
  std::string mark;
  std::string newMark;
  if (stream.eof())
  {
    return &printInvalidCommand;
  }
  stream >> mark;
  if (stream.eof())
  {
    return &printInvalidCommand;
  }
  stream >> newMark;
  if (detail::isTrash(stream))
  {
    return &printInvalidCommand;
  }
  return std::bind(&usanov::BookmarkInterface::storeMark, std::placeholders::_1, mark, newMark, std::placeholders::_2);

}

Command detail::parseCommandInsert(std::istringstream &stream)
{
  std::string placeToInsert;
  stream >> placeToInsert;
  if (placeToInsert.empty())
  {
    return &printInvalidCommand;
  }
  std::string markName;
  stream >> markName;
  if (markName.empty())
  {
    return &printInvalidCommand;
  }
  std::string name, number;
  if (!parseNumber(stream, number))
  {
    return &printInvalidCommand;
  }
  if (!parseName(stream, name))
  {
    return &printInvalidCommand;
  }
  if (isTrash(stream))
  {
    return &printInvalidCommand;
  }
  usanov::PhoneBook::record_t recordToAdd{number, name};
  if (placeToInsert == "before")
  {
    return std::bind(&usanov::BookmarkInterface::insertBeforeMark, std::placeholders::_1, markName, recordToAdd,
        std::placeholders::_2);
  }
  else if (placeToInsert == "after")
  {
    return std::bind(&usanov::BookmarkInterface::insertAfterMark, std::placeholders::_1, markName, recordToAdd,
        std::placeholders::_2);
  }
  else
  {
    return &printInvalidCommand;
  }
}

Command detail::parseCommandDelete(std::istringstream &stream)
{
  std::string markName;
  stream >> markName;
  if (markName.empty())
  {
    return &printInvalidCommand;
  }
  if (isTrash(stream))
  {
    return &printInvalidCommand;
  }
  return std::bind(&usanov::BookmarkInterface::deleteRecordOnMark, std::placeholders::_1, markName,
      std::placeholders::_2);
}

Command detail::parseCommandShow(std::istringstream &stream)
{
  std::string markName;
  stream >> markName;
  if (markName.empty())
  {
    return &printInvalidCommand;
  }
  if (isTrash(stream))
  {
    return &printInvalidCommand;
  }
  return std::bind(&usanov::BookmarkInterface::showMark, std::placeholders::_1, markName, std::placeholders::_2);
}

Command detail::parseCommandMove(std::istringstream &stream)
{
  std::string markName;
  stream >> markName;
  if (markName.empty())
  {
    return &printInvalidCommand;
  }
  std::string steps;
  stream >> steps;
  if (isTrash(stream))
  {
    return &printInvalidCommand;
  }
  if(steps.empty())
  {
    return &printInvalidStep;
  }
  if (steps == "first")
  {
    return std::bind(&usanov::BookmarkInterface::moveMarkOnPos, std::placeholders::_1, markName,
        usanov::BookmarkInterface::MovePos::first, std::placeholders::_2);
  }
  else if (steps == "last")
  {
    return std::bind(&usanov::BookmarkInterface::moveMarkOnPos, std::placeholders::_1, markName,
                     usanov::BookmarkInterface::MovePos::last, std::placeholders::_2);
  }
  else
  {
    std::istringstream stepsStream(steps);
    int numberOfSteps = 0;
    stepsStream >> numberOfSteps;
    if(!stepsStream.eof())
    {
      return &printInvalidStep;
    }
    return std::bind(&usanov::BookmarkInterface::moveMarkOnSteps, std::placeholders::_1, markName, numberOfSteps,
        std::placeholders::_2);
  }
}

bool detail::parseNumber(std::istringstream &stream, std::string &numberToWrite)
{
  std::string tempNumber;
  stream >> tempNumber;
  for (size_t i = 0; i < tempNumber.size(); i++)
  {
    if (!isdigit(tempNumber[i]))
    {
      return false;
    }
  }
  numberToWrite = tempNumber;
  return true;
}

bool detail::parseName(std::istringstream &stream, std::string &nameToWrite)
{
  stream >> std::ws;
  char currentSymbol = stream.peek();
  char previousSymbol = currentSymbol;
  bool isEnded = false;
  if (currentSymbol != '\"')
  {
    return false;
  }
  std::string tempName;
  while ((stream.peek() != EOF) && (stream.peek() != '\n'))
  {
    stream.get();
    currentSymbol = stream.peek();
    if ((currentSymbol == '\\') && (previousSymbol != '\\'))
    {
      previousSymbol = currentSymbol;
      continue;
    }
    if ((currentSymbol == '\"') && (previousSymbol != '\\'))
    {
      stream.get();
      isEnded = true;
      break;
    }
    tempName.push_back(currentSymbol);
    previousSymbol = currentSymbol;
  }
  if (!isEnded)
  {
    return false;
  }
  nameToWrite = tempName;
  return true;
}

bool detail::isTrash(std::istringstream &stream)
{
  std::string streamString;
  stream >> streamString;
  return (!streamString.empty());
}

void printInvalidCommand(usanov::BookmarkInterface &, std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void printInvalidStep(usanov::BookmarkInterface &, std::ostream &out)
{
  out << "<INVALID STEP>\n";
}
