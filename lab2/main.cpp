#include <iostream>
#include "stackarray.hpp"
#include "stacklist.hpp"

bool isBalancedBrackets(std::string originStr, bool isArrayWay = false);

bool balanceByArray(std::string originStr);

bool balanceByList(std::string originStr);

int main()
{
  std::string text01 = "( ) ok ";
  std::cout << text01 << ": " << (isBalancedBrackets(text01, true) ? "right" : "wrong") << std::endl;
  std::string text02 = "( ( [] ) ) ok ";
  std::cout << text02 << ": " << (isBalancedBrackets(text02, true) ? "right" : "wrong") << std::endl;
  std::string text03 = "( ( [{}]([ ]) ) ) OK";
  std::cout << text03 << ": " << (isBalancedBrackets(text03, true) ? "right" : "wrong") << std::endl;
  std::string text04 = "( ( [ { } [ ] ( [ ] ) ] ) ) ) extra right parenthesis ";
  std::cout << text04 << ": " << (isBalancedBrackets(text04) ? "right" : "wrong") << std::endl;
  std::string text05 = "( ( [{ }[ ]([ ])] ) extra left parenthesis ";
  std::cout << text05 << ": " << (isBalancedBrackets(text05) ? "right" : "wrong") << std::endl;
  std::string text06 = "( ( [{ ][ ]([ ])]) ) unpaired bracket ";
  std::cout << text06 << ": " << (isBalancedBrackets(text06) ? "right" : "wrong") << std::endl;
}

bool isBalancedBrackets(std::string originStr, bool isArrayWay)
{
  if (isArrayWay)
  {
    return balanceByArray(originStr);
  } else
  {
    return balanceByList(originStr);
  }
}

bool balanceByArray(std::string originStr)
{
  StackArray<char> stack(originStr.length());

  for (int i = 0; i < (int) originStr.length(); ++i)
  {
    if (originStr[i] == '(' || originStr[i] == '{' || originStr[i] == '[')
    {
      stack.push(originStr[i]);
    } else if (originStr[i] == ')' || originStr[i] == '}' || originStr[i] == ']')
    {
      if
        (
        stack.isEmpty() || ((originStr[i] == ')') ^ (stack.getTop() == '(')) ||
        ((originStr[i] == '}') ^ (stack.getTop() == '{')) || ((originStr[i] == ']') ^ (stack.getTop() == '['))
        )
      {
        return false;
      }

      stack.pop();
    }
  }

  return stack.isEmpty();
}

bool balanceByList(std::string originStr)
{
  StackList<char> stack;

  for (int i = 0; i < (int) originStr.length(); ++i)
  {
    if (originStr[i] == '(' || originStr[i] == '{' || originStr[i] == '[')
    {
      stack.push(originStr[i]);
    } else if (originStr[i] == ')' || originStr[i] == '}' || originStr[i] == ']')
    {
      if
        (
        stack.isEmpty() || ((originStr[i] == ')') ^ (stack.getTop() == '(')) ||
        ((originStr[i] == '}') ^ (stack.getTop() == '{')) || ((originStr[i] == ']') ^ (stack.getTop() == '['))
        )
      {
        return false;
      }

      stack.pop();
    }
  }

  return stack.isEmpty();
}
