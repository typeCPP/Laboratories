  #include <iostream>
  #include <cmath>
  #include "operand.hpp"
  #include "stackarray.hpp"

  std::string infixToPostfix(const std::string &originStr);

  std::string eraseAllBrackets(const std::string &originStr);

  int calculateTwoOperands(int operand1, int operand2, char operation);

  int calculatePostfix(const std::string &originStr);

  int main()
  {
    try
    {
      std::string str1 = "(1+2-3)*(4-5*6)/7";
      std::cout << "Original string: " << str1 << " | Postfix-form string: " << infixToPostfix(str1) << std::endl;
      std::string str2 = "5 + 7 + ( 2 * 6 )";
      std::cout << "Original string: " << str2 << " | Postfix-form string: " << infixToPostfix(str2) << std::endl;
      std::string str3 = "( 4 - 2 ) / 7 + 1";
      std::cout << "Original string: " << str3 << " | Postfix-form string: " << infixToPostfix(str3) << std::endl;
      std::string str4 = "( 4 ^ 2 - 2 ^ 2 ) / 3";
      std::cout << "Original string: " << str4 << " | Postfix-form string: " << infixToPostfix(str4) << std::endl;
      std::string str5 = "( 1 + 1 ) / ( 1 - 1 )";
      std::cout << "Original string: " << str5 << " | Postfix-form string: " << infixToPostfix(str5) << std::endl;

      std::cout << "Calculated strings in postfix-form:" << std::endl;
      std::cout << "String 1: " << calculatePostfix(infixToPostfix(str1)) << std::endl;
      std::cout << "String 2: " << calculatePostfix(infixToPostfix(str2)) << std::endl;
      std::cout << "String 3: " << calculatePostfix(infixToPostfix(str3)) << std::endl;
      std::cout << "String 4: " << calculatePostfix(infixToPostfix(str4)) << std::endl;
      std::cout << "String 5: " << calculatePostfix(infixToPostfix(str5)) << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
      std::cerr << std::endl << e.what() << std::endl;
      return 1;
    }
    return 0;
  }

  int calculateTwoOperands(int operand1, int operand2, char operation)
  {
    switch (operation)
    {
      case '+':
        return operand1 + operand2;
      case '-':
        return operand1 - operand2;
      case '*':
        return operand1 * operand2;
      case '/':
        if (operand2 == 0)
        {
          throw std::invalid_argument("Dividing by zero detected");
        }
        return operand1 / operand2;
      case '^':
        return pow(operand1, operand2);
    }
    return 0;
  }

  int calculatePostfix(const std::string &originStr)
  {
    const int ASCII_CODE_FOR_ZERO = 48;
    const int ASCII_CODE_FOR_NINE = 57;
    StackArray<int> stack(originStr.length());
    for (int i = 0; i < originStr.length(); i++)
    {
      if ((int) originStr[i] >= ASCII_CODE_FOR_ZERO && (int) originStr[i] <= ASCII_CODE_FOR_NINE)
      {
        stack.push((int) originStr[i] - ASCII_CODE_FOR_ZERO);
      } else if (originStr[i] == '+' || originStr[i] == '-' || originStr[i] == '*' || originStr[i] == '/' ||
                 originStr[i] == '^')
      {
        int operand1 = stack.pop();
        int operand2 = stack.pop();
        stack.push(calculateTwoOperands(operand2, operand1, originStr[i]));
      }
    }
    return stack.getTop();
  }

  std::string eraseAllBrackets(const std::string &originStr)
  {
    std::string result;
    for (int i = 0; i < originStr.length(); i++)
    {
      if (originStr[i] != '(' && originStr[i] != ')')
      {
        result.push_back(originStr[i]);

      }
    }
    return result;
  }

  std::string infixToPostfix(const std::string &originStr)
  {
    const int ASCII_CODE_FOR_ZERO = 48;
    const int ASCII_CODE_FOR_NINE = 57;

    std::string result = "";
    StackArray<char> stack(originStr.length());
    for (int i = 0; i < originStr.length(); i++)
    {
      if ((int) originStr[i] >= ASCII_CODE_FOR_ZERO && (int) originStr[i] <= ASCII_CODE_FOR_NINE)
      {
        result.push_back(originStr[i]);
        result.push_back(' ');
      } else if (originStr[i] == '+' || originStr[i] == '-' || originStr[i] == '*' || originStr[i] == '/' ||
                 originStr[i] == '^')
      {
        Operand temp(originStr[i]);
        Operand topOperand(stack.getTop());
        if (stack.isEmpty() || stack.getTop() == '(')
        {
          stack.push(originStr[i]);
        } else if (temp.getPriority() > topOperand.getPriority())
        {
          stack.push(originStr[i]);
        } else if (temp.getPriority() <= topOperand.getPriority())
        {
          char counter = stack.getTop();
          while ((counter != '(' || Operand(counter).getPriority() > Operand(stack.getTop()).getPriority()) &&
                 !stack.isEmpty())
          {
            counter = stack.getTop();
            result.push_back(stack.pop());
            result.push_back(' ');
          }
          stack.push(originStr[i]);
        }
      } else if (originStr[i] == '(')
      {
        stack.push(originStr[i]);
      } else if (originStr[i] == ')')
      {
        char counter = stack.getTop();
        while (counter != '(' && !stack.isEmpty())
        {
          counter = stack.getTop();
          result.push_back(stack.pop());
          if (counter != ')' && counter != '(')
            result.push_back(' ');
        }
      }

    }
    while (!stack.isEmpty())
    {
      result.push_back(stack.pop());
      result.push_back(' ');
    }
    result = eraseAllBrackets(result);
    return result;
  }
