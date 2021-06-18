#include <sstream>
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>
#include "phonebook.hpp"
#include "parser.hpp"
#include "bookmarkInterface.hpp"

BOOST_AUTO_TEST_SUITE(testParser)

  const std::string ERROR_INVALID_COMMAND = "<INVALID COMMAND>\n";
  const std::string ERROR_INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";

  struct fixture
  {
    fixture() :
      coutBuf(std::cout.rdbuf(out.rdbuf()))
    {}

    void redirectInputOutput()
    {
      std::cout.rdbuf(coutBuf);
    }

    std::streambuf *coutBuf;
    std::ostringstream out;
    usanov::BookmarkInterface book;
    Command command;
  };

  BOOST_FIXTURE_TEST_CASE(testWrongCommand, fixture)
  {
    command = parseTypeOfCommand("wrongCommand");
    command(book, out);
    std::string output = out.str();
    std::string rightOutput = ERROR_INVALID_COMMAND;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
    command = parseTypeOfCommand("");
    command(book, out);
    output = out.str();
    rightOutput += ERROR_INVALID_COMMAND;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testCommandAdd, fixture)
  {
    command = parseTypeOfCommand("add 123456 \"Andrey Usanov\"");
    command(book, out);
    command = parseTypeOfCommand("show current");
    command(book, out);
    std::string output = out.str();
    std::string rightOutput = "123456 Andrey Usanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
    command = parseTypeOfCommand("add +7918222333 \"AndreyUsanov\"");
    command(book, out);
    output = out.str();
    rightOutput += ERROR_INVALID_COMMAND;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
    command = parseTypeOfCommand("add 7918222333 AndreyUsanov\"");
    command(book, out);
    output = out.str();
    rightOutput += ERROR_INVALID_COMMAND;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testCommandStore, fixture)
  {
    command = parseTypeOfCommand("add 123456 \"Andrey Usanov\"");
    command(book, out);
    command = parseTypeOfCommand("store");
    command(book, out);
    command = parseTypeOfCommand("store notExistingMark newMark");
    command(book, out);
    std::string output = out.str();
    std::string rightOutput = ERROR_INVALID_COMMAND + ERROR_INVALID_BOOKMARK;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
    command = parseTypeOfCommand("add 123456 \"Andrey Usanov\"");
    command(book, out);
    command = parseTypeOfCommand("store current newMark");
    command(book, out);
    command = parseTypeOfCommand("show current");
    command(book, out);
    command = parseTypeOfCommand("show newMark");
    command(book, out);
    output = out.str();
    rightOutput += "123456 Andrey Usanov\n123456 Andrey Usanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testCommandInsert, fixture)
  {
    command = parseTypeOfCommand("insert");
    command(book, out);
    command = parseTypeOfCommand("insert before notExistingMark 111222 \"Andrey\"");
    command(book, out);
    std::string output = out.str();
    std::string rightOutput = ERROR_INVALID_COMMAND + ERROR_INVALID_BOOKMARK;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);

    command = parseTypeOfCommand("add 123456 \"Andrey Usanov\"");
    command(book, out);
    command = parseTypeOfCommand("insert before current 111222 \"Andrey\"");
    command(book, out);
    command = parseTypeOfCommand("insert after current 333444 \"Ivan\"");
    command(book, out);
    book.moveMarkOnPos("current", usanov::BookmarkInterface::MovePos::first, out);
    book.showMark("current", out);
    book.moveMarkOnSteps("current", 1, out);
    book.showMark("current", out);
    book.moveMarkOnSteps("current", 1, out);
    book.showMark("current", out);
    output = out.str();
    rightOutput += "111222 Andrey\n123456 Andrey Usanov\n333444 Ivan\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testCommandDelete, fixture)
  {
    command = parseTypeOfCommand("add 123456 \"Andrey Usanov\"");
    command(book, out);
    command = parseTypeOfCommand("delete");
    command(book, out);
    command = parseTypeOfCommand("delete notExistingMark");
    command(book, out);
    std::string output = out.str();
    std::string rightOutput = ERROR_INVALID_COMMAND + ERROR_INVALID_BOOKMARK;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
    command = parseTypeOfCommand("delete current");
    command(book, out);
    command = parseTypeOfCommand("show current");
    command(book, out);
    output = out.str();
    rightOutput += "<EMPTY>\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testCommandMove, fixture)
  {
    command = parseTypeOfCommand("add 123456 \"Andrey Usanov\"");
    command(book, out);
    command = parseTypeOfCommand("move");
    command(book, out);
    command = parseTypeOfCommand("move notExistingMark first");
    command(book, out);
    std::string output = out.str();
    std::string rightOutput = ERROR_INVALID_COMMAND + ERROR_INVALID_BOOKMARK;
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
    command = parseTypeOfCommand("add 111111 \"Andrey\"");
    command(book, out);
    command = parseTypeOfCommand("move current first");
    command(book, out);
    command = parseTypeOfCommand("show current");
    command(book, out);
    command = parseTypeOfCommand("move current last");
    command(book, out);
    command = parseTypeOfCommand("show current");
    command(book, out);
    command = parseTypeOfCommand("move current -1");
    command(book, out);
    command = parseTypeOfCommand("show current");
    command(book, out);
    output = out.str();
    rightOutput += "123456 Andrey Usanov\n111111 Andrey\n123456 Andrey Usanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_AUTO_TEST_CASE(testSubfunctions)
  {

    const std::string RIGHT_NUMBER = "123456789";
    const std::string WRONG_NUMBER = "+7(919)111-07-18";
    const std::string RIGHT_NAME = "\"Andrey\\\\Usanov\"";
    const std::string WRONG_NAME = "Andrey Usanov";
    std::istringstream RIGHT_NUM_STREAM(RIGHT_NUMBER);
    std::istringstream WRONG_NUM_STREAM(WRONG_NUMBER);
    std::istringstream RIGHT_NAME_STREAM(RIGHT_NAME);
    std::istringstream WRONG_NAME_STREAM(WRONG_NAME);
    std::string temp;
    BOOST_CHECK_EQUAL(detail::parseNumber(RIGHT_NUM_STREAM, temp), true);
    BOOST_CHECK_EQUAL(detail::parseNumber(WRONG_NUM_STREAM, temp), false);
    BOOST_CHECK_EQUAL(detail::parseName(RIGHT_NAME_STREAM, temp), true);
    BOOST_CHECK_EQUAL(detail::parseName(WRONG_NAME_STREAM, temp), false);
  }

BOOST_AUTO_TEST_SUITE_END()
