#ifndef LAB3_OPERAND_HPP
#define LAB3_OPERAND_HPP

class Operand
{
public:
  Operand(char op);

  char getOperation();

  int getPriority();

private:
  char operation;
  int priority;
};

#endif
