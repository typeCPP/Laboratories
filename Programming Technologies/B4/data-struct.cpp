#include "data-struct.hpp"
#include "utility.hpp"

const int MAX_KEY_ABS = 5;
const char SEPARATOR = ',';

int readKey(std::istream &input)
{
  int keyToRead;
  input >> skipWs >> keyToRead;
  if ((!input) || (std::abs(keyToRead) > MAX_KEY_ABS))
  {
    input.setstate(std::ios_base::failbit);
    return 0;
  }
  return keyToRead;
}

std::string readString(std::istream &input)
{
  std::string str;
  std::getline(input, str);
  if ((!input) || (str.empty()))
  {
    input.setstate(std::ios::failbit);
    return "";
  }
  return str;
}

bool ComparingDataStructs::operator()(const DataStruct &first, const DataStruct &second) const
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }
  return first.str.size() < second.str.size();
}

std::istream &operator>>(std::istream &input, DataStruct &dataStruct)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  StreamGuard guard(input);
  input >> std::noskipws;
  const int key1 = readKey(input);
  if ((!input) || (input.get() != SEPARATOR))
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  input >> skipWs;
  const int key2 = readKey(input);
  if ((!input) || (input.get() != SEPARATOR))
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  input >> skipWs;
  const std::string str = readString(input);
  if (!input)
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }
  dataStruct.key1 = key1;
  dataStruct.key2 = key2;
  dataStruct.str = str;
  return input;
}

std::ostream &operator<<(std::ostream &output, const DataStruct &dataStruct)
{
  std::ostream::sentry sentry(output);
  if (sentry)
  {
    output << dataStruct.key1 << SEPARATOR << dataStruct.key2 << SEPARATOR << dataStruct.str;
  }
  return output;
}
