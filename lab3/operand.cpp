#include "operand.hpp"

Operand::Operand(char op):
operation(op)
{
  if(op == '^') priority = 6;
  if(op == '*') priority = 5;
  if(op == '/') priority = 4;
  if(op == '+') priority = 3;
  if(op == '-') priority = 2;
  if(op == '(') priority = 1;
  if(op == ')') priority = 1;
}

char Operand::getOperation()
{
  return operation;
}

int Operand::getPriority()
{
  return priority;
}
