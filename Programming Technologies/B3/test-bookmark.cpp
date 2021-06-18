#include <sstream>
#include <iostream>
#include <string>
#include <boost/test/unit_test.hpp>
#include "phonebook.hpp"
#include "bookmarkInterface.hpp"

BOOST_AUTO_TEST_SUITE(testBookmarkIntefrace)

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
  };

  BOOST_FIXTURE_TEST_CASE(testAddMethod, fixture)
  {
    usanov::BookmarkInterface interface;
    interface.addRecord({"123456", "Andrey Usanov"});
    interface.showMark("current", out);
    std::string output = out.str();
    std::string rightOutput = "123456 Andrey Usanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
    interface.addRecord({"111222", "Andrey Ivanov"});
    interface.moveMarkOnSteps("current", 1, out);
    interface.showMark("current", out);
    output = out.str();
    rightOutput += "111222 Andrey Ivanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testStoreMark, fixture)
  {
    usanov::BookmarkInterface interface;
    interface.addRecord({"123456", "Andrey Usanov"});
    interface.addRecord({"111222", "Andrey Ivanov"});
    interface.storeMark("current", "newMark", out);
    interface.showMark("current", out);
    interface.showMark("newMark", out);
    const std::string output = out.str();
    const std::string rightOutput = "123456 Andrey Usanov\n123456 Andrey Usanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testInsertBefore, fixture)
  {
    usanov::BookmarkInterface interface;
    interface.addRecord({"123456", "Andrey Usanov"});
    interface.insertBeforeMark("current", {"111222", "Andrey Ivanov"}, out);
    interface.showMark("current", out);
    interface.moveMarkOnPos("current", usanov::BookmarkInterface::MovePos::first, out);
    interface.showMark("current", out);
    const std::string output = out.str();
    const std::string rightOutput = "123456 Andrey Usanov\n111222 Andrey Ivanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testInsertAfter, fixture)
  {
    usanov::BookmarkInterface interface;
    interface.addRecord({"123456", "Andrey Usanov"});
    interface.insertAfterMark("current", {"111222", "Andrey Ivanov"}, out);
    interface.showMark("current", out);
    interface.moveMarkOnPos("current", usanov::BookmarkInterface::MovePos::last, out);
    interface.showMark("current", out);
    const std::string output = out.str();
    const std::string rightOutput = "123456 Andrey Usanov\n111222 Andrey Ivanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testDelete, fixture)
  {
    usanov::BookmarkInterface interface;
    interface.addRecord({"123456", "Andrey Usanov"});
    interface.deleteRecordOnMark("current", out);
    interface.showMark("current", out);
    const std::string output = out.str();
    const std::string rightOutput = "<EMPTY>\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

  BOOST_FIXTURE_TEST_CASE(testMoving, fixture)
  {
    usanov::BookmarkInterface interface;
    interface.addRecord({"123456", "Andrey Usanov"});
    interface.addRecord({"111222", "Andrey Ivanov"});
    interface.addRecord({"333444", "Ivan Ivanov"});
    interface.showMark("current", out);
    interface.moveMarkOnSteps("current", 1, out);
    interface.showMark("current", out);
    interface.moveMarkOnSteps("current", 1, out);
    interface.showMark("current", out);
    const std::string output = out.str();
    const std::string rightOutput = "123456 Andrey Usanov\n111222 Andrey Ivanov\n333444 Ivan Ivanov\n";
    redirectInputOutput();
    BOOST_CHECK_EQUAL(output, rightOutput);
  }

BOOST_AUTO_TEST_SUITE_END()
